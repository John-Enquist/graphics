#include "animator.h"

#include <vector>
#include <memory>
#include <fstream>
#include <list>

#include "sgutils.h"

using namespace std;
using namespace tr1;

void Animator::attachSceneGraph(shared_ptr<SgNode> root) {
    nodes_.clear();
    keyFrames_.clear();
    dumpSgRbtNodes(root, nodes_);
}

void Animator::loadAnimation(const char *filename) {
    ifstream f(filename, ios::binary);
    int numFrames, numRbtsPerFrame;
    f >> numFrames >> numRbtsPerFrame;
    Cvec3 trans;
    Quat rot;
    keyFrames_.clear();
    for (int i = 0; i < numFrames; ++i) {
      keyFrames_.push_back(KeyFrame());
      keyFrames_.back().reserve(numRbtsPerFrame);
      for (int j = 0; j < numRbtsPerFrame; ++j) {
        f >> trans[0] >> trans[1] >> trans[2] >> rot[0] >> rot[1] >> rot[2] >> rot[3];
        keyFrames_.back().push_back(RigTForm(trans, rot));
      }
    }
}

void Animator::saveAnimation(const char *filename) {
    ofstream f(filename, ios::binary);
    int numRbtsPerFrame = nodes_.size();
    f << getNumKeyFrames() << ' ' << numRbtsPerFrame << '\n';
    for (KeyFrames::const_iterator frameIter = keyFrames_.begin(), e = keyFrames_.end(); frameIter != e; ++frameIter) {
      for (int j = 0; j < numRbtsPerFrame; ++j) {
        const RigTForm& rbt = (*frameIter)[j];
        const Cvec3& trans = rbt.getTranslation();
        const Quat& rot = rbt.getRotation();
        f << trans[0] << ' ' << trans[1] << ' ' << trans[2] << ' '
        << rot[0] << ' ' << rot[1] << ' ' << rot[2] << ' ' << rot[3] << '\n';
      }
    }
}

int Animator::getNumKeyFrames() const {
    return keyFrames_.size();
}

int Animator::getNumRbtNodes() const {
    return nodes_.size();
}

// t can be in the range [0, keyFrames_.size()-3]. Fractional amount like 1.5 is allowed.
void Animator::animate(double t) {
    if (t < 0 || t > keyFrames_.size() - 3)
        throw runtime_error("Invalid animation time parameter. Must be in the range [0, numKeyFrames - 3]");

    t += 1; // interpret the key frames to be at t= -1, 0, 1, 2, ...
    const int integralT = int(floor(t));
    const double fraction = t - integralT;

    KeyFrameIter f0 = getNthKeyFrame(integralT), f1 = f0;
    ++f1;
    int n = nodes_.size();
    for(int i = 0; i < n; i++){
        nodes_[i]->setRbt(lerp((*f0)[i], (*f1)[i], fraction));
    }
}

Animator::KeyFrameIter Animator::keyFramesBegin() {
    return keyFrames_.begin();
}

Animator::KeyFrameIter Animator::keyFramesEnd() {
    return keyFrames_.end();
}

Animator::KeyFrameIter Animator::getNthKeyFrame(int n) {
    KeyFrameIter frameIter = keyFrames_.begin();
    advance(frameIter, n);
    return frameIter;
}

void Animator::deleteKeyFrame(KeyFrameIter keyFrameIter) {
    keyFrames_.erase(keyFrameIter);
}

void Animator::pullKeyFrameFromSg(KeyFrameIter keyFrameIter) {
    for (int i = 0, n = nodes_.size(); i < n; ++i) {
        (*keyFrameIter)[i] = nodes_[i]->getRbt();
    }
}

void Animator::pushKeyFrameToSg(KeyFrameIter keyFrameIter) {
    for (int i = 0, n = nodes_.size(); i < n; ++i) {
        nodes_[i]->setRbt((*keyFrameIter)[i]);
    }
}

Animator::KeyFrameIter Animator::insertEmptyKeyFrameAfter(KeyFrameIter beforeFrame) {
    if (beforeFrame != keyFrames_.end())
        ++beforeFrame;

    KeyFrameIter frameIter = keyFrames_.insert(beforeFrame, KeyFrame());
    frameIter->resize(nodes_.size());
    return frameIter;
}


