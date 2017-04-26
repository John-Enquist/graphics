#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <vector>
#include <memory>
#include <list>

#include "scenegraph.h"
#include "rigtform.h"

using namespace std;
using namespace tr1;



class Animator {
public:
    typedef vector<shared_ptr<SgRbtNode> > SgRbtNodes;
    typedef vector<RigTForm> KeyFrame;
    typedef list<KeyFrame> KeyFrames;
    typedef KeyFrames::iterator KeyFrameIter;

private:
    SgRbtNodes nodes_;
    KeyFrames keyFrames_;

public:
    // set up animator to use the scene graph rooted at root
    void attachSceneGraph(shared_ptr<SgNode> root);

    // load keyframes from file
    void loadAnimation(const char *filename);

    // save keyframes to file
    void saveAnimation(const char *filename);

    // get # of keyframes in the animation
    int getNumKeyFrames() const;

    // get # of RBT nodes in each keyframe
    int getNumRbtNodes() const;


    // For a given time t, set the RBT nodes of the nodes
    // in the scene graph based on appropriate interpolation
    // between RBTs in the keyframes.
    // 
    // t can be in the range [0, getNumKeyFrames().size()-3].
    // Fractional amounts like 1.5 are allowed.
    void animate(double t);

    // get iterator to first keyframe
    Animator::KeyFrameIter keyFramesBegin();

    // get iterator to end of keyframes
    Animator::KeyFrameIter keyFramesEnd();

    // get iterator to nth keyframe
    Animator::KeyFrameIter getNthKeyFrame(int n);

    // remove a keyframe
    void deleteKeyFrame(KeyFrameIter keyFrameIter);

    // update a keyframe from the nodes' current RBT values
    void pullKeyFrameFromSg(KeyFrameIter keyFrameIter);

    // set nodes' RBTs based on the given keyframe
    void pushKeyFrameToSg(KeyFrameIter keyFrameIter);

    // insert a new keyframe
    Animator::KeyFrameIter insertEmptyKeyFrameAfter(KeyFrameIter beforeFrame);
};

#endif
