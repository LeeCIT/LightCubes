

#include "shapes.h"



namespace shapes
{
    namespace plane
    {
        const int vertCount = 4;
        const int indCount  = 4;

        const float h = 0.5f;

        const vertex vert[] = {
            vertex( vec3(+h,-h,0),  vec3(0,0,1),  vec2(1,0),  colour::red    ), // Right bottom front
            vertex( vec3(+h,+h,0),  vec3(0,0,1),  vec2(1,1),  colour::green  ), // Right top    front
            vertex( vec3(-h,-h,0),  vec3(0,0,1),  vec2(0,0),  colour::orange ), // Left  bottom front
            vertex( vec3(-h,+h,0),  vec3(0,0,1),  vec2(0,1),  colour::blue   )  // Left  top    front
        };

        const GLubyte ind[] = {
            0,1,2,3
        };
    };


    
    namespace cube
    {
        const int faces     = 6;
        const int faceVerts = 4;
        const int vertCount = faces * faceVerts;
        const int indCount  = vertCount;

        const float h  = 0.5f;
        const float q1 = 0.25f;
        const float q2 = 0.50f;
        const float q3 = 0.75f;
        const float t1 = 1.0f / 3.0f;
        const float t2 = 2.0f / 3.0f;

        const vertex vert[] = {
            // +z
            vertex(  vec3(+h,-h,+h),  vec3(0,0,+1),  vec2(t2,q2), colour::white  ), // Right bottom front
            vertex(  vec3(+h,+h,+h),  vec3(0,0,+1),  vec2(t2,q3), colour::white  ), // Right top    front
            vertex(  vec3(-h,-h,+h),  vec3(0,0,+1),  vec2(t1,q2), colour::white  ), // Left  bottom front
            vertex(  vec3(-h,+h,+h),  vec3(0,0,+1),  vec2(t1,q3), colour::white  ), // Left  top    front    
                                                        
            // -z
            vertex(  vec3(-h,-h,-h),  vec3(0,0,-1),  vec2(t1,q1), colour::white  ), // Left  bottom back
            vertex(  vec3(-h,+h,-h),  vec3(0,0,-1),  vec2(t1, 0), colour::white  ), // Left  top    back
            vertex(  vec3(+h,-h,-h),  vec3(0,0,-1),  vec2(t2,q1), colour::white  ), // Right bottom back
            vertex(  vec3(+h,+h,-h),  vec3(0,0,-1),  vec2(t2, 0), colour::white  ), // Right top    back
            
            // +y
            vertex(  vec3(+h,+h,+h),  vec3(0,+1,0),  vec2(t2,q3), colour::white  ), // Right top front
            vertex(  vec3(+h,+h,-h),  vec3(0,+1,0),  vec2(t2, 1), colour::white  ), // Right top back
            vertex(  vec3(-h,+h,+h),  vec3(0,+1,0),  vec2(t1,q3), colour::white  ), // Left  top front
            vertex(  vec3(-h,+h,-h),  vec3(0,+1,0),  vec2(t1, 1), colour::white  ), // Left  top back
                                                        
            // -y
            vertex(  vec3(+h,-h,-h),  vec3(0,-1,0),  vec2(t2,q1), colour::white  ), // Right bottom back
            vertex(  vec3(+h,-h,+h),  vec3(0,-1,0),  vec2(t2,q2), colour::white  ), // Right bottom front
            vertex(  vec3(-h,-h,-h),  vec3(0,-1,0),  vec2(t1,q1), colour::white  ), // Left  bottom back
            vertex(  vec3(-h,-h,+h),  vec3(0,-1,0),  vec2(t1,q2), colour::white  ), // Left  bottom front
                                                  
            // +x
            vertex(  vec3(+h,-h,+h),  vec3(+1,0,0),  vec2(t2,q2), colour::white  ), // Right bottom front
            vertex(  vec3(+h,-h,-h),  vec3(+1,0,0),  vec2( 1,q2), colour::white  ), // Right bottom back
            vertex(  vec3(+h,+h,+h),  vec3(+1,0,0),  vec2(t2,q3), colour::white  ), // Right top    front
            vertex(  vec3(+h,+h,-h),  vec3(+1,0,0),  vec2( 1,q3), colour::white  ), // Right top    back
                                                        
            // -x
            vertex(  vec3(-h,-h,-h),  vec3(-1,0,0),  vec2( 0,q2), colour::white  ), // Left bottom back
            vertex(  vec3(-h,-h,+h),  vec3(-1,0,0),  vec2(t1,q2), colour::white  ), // Left bottom front
            vertex(  vec3(-h,+h,-h),  vec3(-1,0,0),  vec2( 0,q3), colour::white  ), // Left top    back
            vertex(  vec3(-h,+h,+h),  vec3(-1,0,0),  vec2(t1,q3), colour::white  ), // Left top    front
    
        };

        const GLubyte ind[] =  {
             0, 1, 2, 3, // +z
             4, 5, 6, 7, // -z
             8, 9,10,11, // +y
            12,13,14,15, // -y
            16,17,18,19, // +x
            20,21,22,23  // -x
        };
    };



    namespace trapezoid {
        // TODO: Normals are totally wrong for angular faces.
        //       Just a matter of doing the cross products...
        const int faces     = 6;
        const int faceVerts = 4;
        const int vertCount = faces * faceVerts;
        const int indCount  = vertCount;

        const float q  = 0.25f;
        const float h  = 0.50f;
        const float q1 = 0.25f;
        const float q2 = 0.50f;
        const float q3 = 0.75f;
        const float t1 = 1.0f / 3.0f;
        const float t2 = 2.0f / 3.0f;

        const vertex vert[] = 
        {
            // +z
            vertex(  vec3(+h,-h,+h),  vec3(0,0,+1),  vec2(t2,q2), colour::white  ), // Right bottom front
            vertex(  vec3(+h,+h,+h),  vec3(0,0,+1),  vec2(t2,q3), colour::white  ), // Right top    front
            vertex(  vec3(-h,-h,+h),  vec3(0,0,+1),  vec2(t1,q2), colour::white  ), // Left  bottom front
            vertex(  vec3(-h,+h,+h),  vec3(0,0,+1),  vec2(t1,q3), colour::white  ), // Left  top    front    
            
            // -z
            vertex(  vec3(-q,-q,-h),  vec3(0,0,-1),  vec2(t1,q1), colour::white  ), // Left  bottom back
            vertex(  vec3(-q,+q,-h),  vec3(0,0,-1),  vec2(t1, 0), colour::white  ), // Left  top    back
            vertex(  vec3(+q,-q,-h),  vec3(0,0,-1),  vec2(t2,q1), colour::white  ), // Right bottom back
            vertex(  vec3(+q,+q,-h),  vec3(0,0,-1),  vec2(t2, 0), colour::white  ), // Right top    back
            
            // +y
            vertex(  vec3(+h,+h,+h),  vec3(0,+1,0),  vec2(t2,q3), colour::white  ), // Right top front
            vertex(  vec3(+q,+q,-h),  vec3(0,+1,0),  vec2(t2, 1), colour::white  ), // Right top back
            vertex(  vec3(-h,+h,+h),  vec3(0,+1,0),  vec2(t1,q3), colour::white  ), // Left  top front
            vertex(  vec3(-q,+q,-h),  vec3(0,+1,0),  vec2(t1, 1), colour::white  ), // Left  top back
                                                        
            // -y
            vertex(  vec3(+q,-q,-h),  vec3(0,-1,0),  vec2(t2,q1), colour::white  ), // Right bottom back
            vertex(  vec3(+h,-h,+h),  vec3(0,-1,0),  vec2(t2,q2), colour::white  ), // Right bottom front
            vertex(  vec3(-q,-q,-h),  vec3(0,-1,0),  vec2(t1,q1), colour::white  ), // Left  bottom back
            vertex(  vec3(-h,-h,+h),  vec3(0,-1,0),  vec2(t1,q2), colour::white  ), // Left  bottom front
                                                  
            // +x
            vertex(  vec3(+h,-h,+h),  vec3(+1,0,0),  vec2(t2,q2), colour::white  ), // Right bottom front
            vertex(  vec3(+q,-q,-h),  vec3(+1,0,0),  vec2( 1,q2), colour::white  ), // Right bottom back
            vertex(  vec3(+h,+h,+h),  vec3(+1,0,0),  vec2(t2,q3), colour::white  ), // Right top    front
            vertex(  vec3(+q,+q,-h),  vec3(+1,0,0),  vec2( 1,q3), colour::white  ), // Right top    back
                                                        
            // -x
            vertex(  vec3(-q,-q,-h),  vec3(-1,0,0),  vec2( 0,q2), colour::white  ), // Left bottom back
            vertex(  vec3(-h,-h,+h),  vec3(-1,0,0),  vec2(t1,q2), colour::white  ), // Left bottom front
            vertex(  vec3(-q,+q,-h),  vec3(-1,0,0),  vec2( 0,q3), colour::white  ), // Left top    back
            vertex(  vec3(-h,+h,+h),  vec3(-1,0,0),  vec2(t1,q3), colour::white  ), // Left top    front
    
        };

        const GLubyte ind[] = {
             0, 1, 2, 3, // +z
             4, 5, 6, 7, // -z
             8, 9,10,11, // +y
            12,13,14,15, // -y
            16,17,18,19, // +x
            20,21,22,23  // -x
        };
    };
};