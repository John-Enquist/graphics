#ifndef SCENE_GRAPH_PRINTER_H
#define SCENE_GRAPH_PRINTER_H

#include "scenegraph.h"
#include <string>
#include <sstream>

using namespace std;
using namespace std::tr1;

class SceneGraphPrinter : public SgNodeVisitor 
{
private:
    int indent;
    ostringstream printstream;

public:
    string printGraph(SgNode& node);
    virtual bool visit(SgTransformNode& node);
    virtual bool postVisit(SgTransformNode& node);
    virtual bool visit(SgShapeNode& node);
    virtual bool postVisit(SgShapeNode& node);
};

string printSceneGraph(SgNode& node);

#endif
