

// Scene graph
// Performs depth-first traversal to draw a scene hierarchically.
// TODO

#pragma once
#include "material.h"
#include "matrix.h"
#include "shader.h"
#include <vector>



namespace sceneGraphSys
{
    using std::vector;
    using gl::shaderProgram;


    struct sceneNode
    {
        vector<sceneNode*> childNodes; // Nodes to be drawn relative to this one.
        material*  mtrPtr;             // Material to use. (if nullptr, it's inherited)
        void (drawFunc)();             // Draw function to call.
        
        sceneNode( sceneNode* parentNode, material* mtrPtr, void(drawFunc)() );
       ~sceneNode();
    };



    class sceneGraph
    {
      private:
        vector<sceneNode*> nodes;


      public:
        sceneNode* addNode();
        void       drawNodes();
    };
};






