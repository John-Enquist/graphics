#include "scenegraph_printer.h"

#include <stdexcept>
#include <string>

#include "scenegraph.h"

using namespace std;
using namespace std::tr1;

static string addSpaces(int n)
{
    ostringstream toReturn;
    for (int i = 0; i < n; i++) {
        toReturn << "   ";
    }
    return toReturn.str();
}

static string printCvec3(Cvec3 vec)
{
    ostringstream toReturn;
    toReturn << "[";

    for (int i = 0; i < 3; i++) {
        toReturn << vec[i];
        if (i < 2) {
            toReturn << ", ";
        }
    }
    toReturn << "]";
    
    return toReturn.str();
}

static string printQuat(Quat q)
{
    ostringstream toReturn;
    toReturn << "[";
    
    for (int i = 0; i < 4; i++) {
        toReturn << q[i];
        if (i < 3) {
            toReturn << ", ";
        }
    }
    toReturn << "]";
    
    return toReturn.str();
}

static string printMatrix(Matrix4 m, int indent)
{
    ostringstream toReturn;
    
    toReturn << "\n" << addSpaces(indent);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            toReturn << m(i,j) << " ";
        }
        toReturn << "\n" << addSpaces(indent);
    }
    toReturn << "\n";
    
    return toReturn.str();
}

static string printRbt(RigTForm tform)
{
    ostringstream toReturn;
    
    toReturn << "translate: " << printCvec3(tform.getTranslation()) << " ";
    toReturn << "rotate: " << printQuat(tform.getRotation());
    
    return toReturn.str();
}

string SceneGraphPrinter::printGraph(SgNode& node)
{
    printstream.str("");
    printstream.clear();
    indent = 0;
    node.accept(*this);
    return printstream.str();
}

bool SceneGraphPrinter::visit(SgTransformNode& node) {
    printstream << addSpaces(indent)
                << "Trans: " << printRbt(node.getRbt());
    
    int numChildren = node.getNumChildren();
    if (numChildren == 1) {
        printstream << " (1 child)\n";
    } else if (numChildren == 0) {
        printstream << " (no children)\n";
    } else {
        printstream << " (" << node.getNumChildren() << " children)\n";
    }
    
    indent++;
    return true;
}

bool SceneGraphPrinter::postVisit(SgTransformNode& node) {
    indent--;
    return true;
}

bool SceneGraphPrinter::visit(SgShapeNode& node) {
    printstream << addSpaces(indent) 
                << "Shape: " << printMatrix(node.getAffineMatrix(), indent);
    return true;
}

bool SceneGraphPrinter::postVisit(SgShapeNode& node) {
    return true;
}

string printSceneGraph(SgNode& node) {
    SceneGraphPrinter printer;
    return printer.printGraph(node);
}
