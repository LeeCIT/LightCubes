

// CGF Project 2: GL 3D
// by Lee Coakley
// November 2012

// Using OpenGL 3.3 Core Profile



#include "main.h"
#include "camera.h"
#include "config.h"
#include "def.h"
#include "draw.h"
#include "entity.h"
#include "entityPlayer.h"
#include "func.h"
#include "core.h"
#include "glCore.h"
#include "glObject.h"
#include "input.h"
#include "light.h"
#include "material.h"
#include "matrix.h"
#include "mat4.h"
#include "menu.h"
#include "pick.h"
#include "random.h"
#include "screen.h"
#include "shapes.h"
#include "vertexStream.h"
#include <cassert>
#include <cmath>
#include <iostream>




////////////////////////////////////////////////////////////////////
// Shapes
/////////////////////////////////////////////////////////////////

gl::vbo* cubeVbo = nullptr;
gl::ibo* cubeIbo = nullptr;
gl::vao* cubeVao = nullptr;

gl::vbo* planeVbo = nullptr;
gl::ibo* planeIbo = nullptr;
gl::vao* planeVao = nullptr;

gl::vbo* trapezoidVbo = nullptr;
gl::ibo* trapezoidIbo = nullptr;
gl::vao* trapezoidVao = nullptr;





////////////////////////////////////////////////////////////////////
// Mesh
/////////////////////////////////////////////////////////////////

meshStream* meshTest;





////////////////////////////////////////////////////////////////////
// Picking
/////////////////////////////////////////////////////////////////

gl::fbo*            pickFbo = nullptr;
pickSys::pickMapper pickMap;
const enum pickEnum: int {
    pickLightDir,
    pickLightPoint,
    pickLightSpot,
    pickLightLine,
    pickEnumSize
};



float lightOnOff[pickEnumSize] = { 1.0f, 1.0f, 1.0f, 1.0f };



void doPicking( int x, int y ) {
    // Draw to FBO, retreive the colour and act upon it.
    glBindFramebuffer( GL_FRAMEBUFFER, *pickFbo );
        drawScene( true );
    glBindFramebuffer( GL_FRAMEBUFFER, 0 );

    // Window coords and GL coords are different
    int ssy  = int(screen::sizeY);
    int posX =  x;
    int posY = -y + ssy;

    // Pick!
    colour col = pickFbo->readTexel( posX, posY );
    int    ind = pickMap.getInd( col );

    std::cout << "Pick: ["
              << posX << ", " 
              << posY << "]: "
              << ind  << "\n";

    if (ind != -1)
        lightOnOff[ind] = (lightOnOff[ind] == 0.0f)  ?  1.0f  :  0.0f;
}









void drawCube() {
    using namespace shapes::cube;

    glBindVertexArray( *cubeVao );
        for (int i=0; i<vertCount; i+=faceVerts) {
            const void* byteOffset = ((GLubyte*) nullptr) + i;
            glDrawRangeElements( GL_TRIANGLE_STRIP, 0, indCount, faceVerts, GL_UNSIGNED_BYTE, byteOffset ); 
        }
    glBindVertexArray( 0 );
}



void drawPlane() {
    using namespace shapes::plane;

    glBindVertexArray( *planeVao );
        glDrawElements( GL_TRIANGLE_STRIP, indCount, GL_UNSIGNED_BYTE, nullptr ); 
    glBindVertexArray( 0 );
}



void drawTrapezoid() {
    using namespace shapes::trapezoid;

    glBindVertexArray( *trapezoidVao );
        for (int i=0; i<vertCount; i+=faceVerts) {
            const void* byteOffset = ((GLubyte*) nullptr) + i;
            glDrawRangeElements( GL_TRIANGLE_STRIP, 0, indCount, faceVerts, GL_UNSIGNED_BYTE, byteOffset ); 
        }
    glBindVertexArray( 0 );
}





void evStart()
{
    // Initialise keyboard handling functions
    inputSys::core::keyInit();

    
    
    // Picking FBO
    {
        pickFbo = new gl::fbo( (int) screen::sizeX, (int) screen::sizeY, true );
        assert( GL_NO_ERROR == glGetError() );
    }



    // Shape: Plane
    {
        using namespace shapes::plane;

        planeVbo = new gl::vbo( vert, vertCount );
        planeIbo = new gl::ibo( ind,  indCount  );
        planeVao = new gl::vao( *planeVbo, *planeIbo );
    }



    // Shape: Cube
    {
        using namespace shapes::cube;

        cubeVbo = new gl::vbo( vert, vertCount );
        cubeIbo = new gl::ibo( ind,  indCount  );
        cubeVao = new gl::vao( *cubeVbo, *cubeIbo );
    }



    // Shape: Trapezoid
    {
        using namespace shapes::trapezoid;

        trapezoidVbo = new gl::vbo( vert, vertCount );
        trapezoidIbo = new gl::ibo( ind,  indCount  );
        trapezoidVao = new gl::vao( *trapezoidVbo, *trapezoidIbo );
    }



    // Set up keybindings
    {
        using namespace inputSys::bind;
        setBind( moveForward,  'w', false );
        setBind( moveBackward, 's', false );
        setBind( moveRight,    'd', false );
        setBind( moveLeft,     'a', false );
        setBind( moveUp,       'c', false );
        setBind( moveDown,     'x', false );

        setBind( yawPos,   GLUT_KEY_LEFT,  true  );
        setBind( yawNeg,   GLUT_KEY_RIGHT, true  );
        setBind( pitchPos, GLUT_KEY_DOWN,  true  );
        setBind( pitchNeg, GLUT_KEY_UP,    true  );
        setBind( rollPos,  'q',            false );
        setBind( rollNeg,  'e',            false );
        
        setBind( spotConePos,     '.', false ); // >
        setBind( spotConeNeg,     ',', false ); // <
        setBind( spotSoftnessPos, 'n', false );
        setBind( spotSoftnessNeg, 'm', false );

        setBind( zoomMagPos,   '=',  false ); // +
        setBind( zoomMagNeg,   '-',  false ); // -
        setBind( zoomMagReset, '\b', false ); // Backspace

        setBind( toggleWireframe,  'f', false );
        setBind( toggleToonShader, 't', false );

        setBind( quitProgram, 'z', false );
    }


    
    // meshStream test
    {
        const int circles   = 16;
        const int circVerts = 256;
        const int meshVerts = circles * circVerts;
        meshTest = new meshStream( meshVerts );

        for (int c=0; c<circles; c++) {
            float cfrac = float(c) / float(circles-1);

            meshTest->begin( (c%2==0) ? GL_LINE_LOOP : GL_LINES );

                for (int v=0; v<circVerts; v++) {
                    float  frac   = float(v) / float(circVerts-1);
                    float  angle  = (2.0f * def::pi * frac) + (def::pi*cfrac);
                    colour col    = lerp( lerp(colour::yellow,colour::purple,frac), colour::orange, cfrac );
                    float  radius = lerp( 0.25f, 2.0f, cfrac );
                    vec3   pos    = pos = vec3( vec2(sin(angle),cos(angle))*radius, (cfrac-0.5f)*2.0f);
                    meshTest->setColour( col );
                    meshTest->emit( pos );
                }

            meshTest->end();
        }

        meshTest->finalise();
    }



    // Picking setup
    {
        pickMap.add( colour::fuschia, pickLightDir   );
        pickMap.add( colour::red,     pickLightPoint );
        pickMap.add( colour::green,   pickLightSpot  );
        pickMap.add( colour::blue,    pickLightLine  );
    }
}





// Called before program exit.  Any heap-allocated GL objects should be freed here.
void evExit() {
    std::cout << "\n=== Exit ===\n";

    delete planeVao;
    delete planeVbo;
    delete planeIbo;

    delete cubeVao;
    delete cubeVbo;
    delete cubeIbo;

    delete trapezoidVao;
    delete trapezoidVbo;
    delete trapezoidIbo;

    delete pickFbo;
}





// Updates state and tells GLUT to redraw.  Called on a timer.
void evStep( int value )  {
    // Re-call this function again.
    glutTimerFunc( coreSys::stepFrequency, evStep, 0 );



    // Update the raw inputs and high-level controls
    inputSys::core::keyUpdate();
    inputSys::core::ctrlUpdate();



    
    { // Quit
        using namespace inputSys::bind;
        if (bindReleased(quitProgram)) {
            glutExit();
            return;
        }
    }
 


    // Redraw the scene
    glutPostRedisplay();



    // Increment step counter
    coreSys::step++;
}





// Draw everything.  This function REALLY needs to be split up... but time is against me.
void drawScene( bool pickMode ) {
    // Clear buffer to a solid colour
    glClearColor( 0, 0, 0, 1 );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );



    // Rendering mode
    if (coreSys::renderWireframe)
         glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    else glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );



    // Enable anti-aliasing
    glEnable( GL_MULTISAMPLE );



    // Hidden surface removal
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_CULL_FACE );
    glCullFace( GL_BACK );
    glFrontFace( GL_CCW );



    // Some animation vars
    const float stepRatio = 0.25f;
    const float timeModX  = float( fmod( coreSys::step*1.00*stepRatio, 360 ) );
    const float timeModY  = float( fmod( coreSys::step*2.00*stepRatio, 360 ) );
    const float timeModZ  = float( fmod( coreSys::step*1.50*stepRatio, 360 ) );


    // Lights
    lightSys::global liGlobal;
        liGlobal.ambient = colour( 0.05f, 0.05f, 0.05f );


    lightSys::directional liDir;
        liDir.vec      = normalise(vec3( -1, -1, -1 ));
        liDir.ambient  = colour( 0.10f, 0.02f, 0.05f ) * vec4(lightOnOff[pickLightDir]);
        liDir.diffuse  = colour( 0.15f, 0.07f, 0.05f ) * vec4(lightOnOff[pickLightDir]);
        liDir.specular = colour( 0.35f, 0.25f, 0.05f ) * vec4(lightOnOff[pickLightDir]);


    lightSys::point liPoint;
        liPoint.pos      = mat4::rotateY(timeModZ) * vec3(256,256,0);
        liPoint.ambient  = colour( 0.6f, 0.5f, 0.4f ) * vec4(lightOnOff[pickLightPoint]);
        liPoint.diffuse  = colour( 0.7f, 0.6f, 0.5f ) * vec4(lightOnOff[pickLightPoint]);
        liPoint.specular = colour( 0.6f, 0.2f, 0.5f ) * vec4(lightOnOff[pickLightPoint]);
        liPoint.decay    = vec3( 0, 0.005f, 0.005f );


    lightSys::spot liSpot;
        liSpot.pos      = vec3(0,256,0);
        liSpot.vec      = mat4::rotateX(timeModX*3) * mat4::rotateY(timeModZ*3) * vec3(0,0,-1);
        liSpot.cone     = 1 - (((45.0f) / 360.0f) * coreSys::spotConeFactor );
        liSpot.softness = 16 * coreSys::spotSoftnessFactor;
        liSpot.ambient  = colour( 0.3f, 0.2f, 0.2f ) * vec4(lightOnOff[pickLightSpot]);
        liSpot.diffuse  = colour( 0.4f, 0.4f, 0.4f ) * vec4(lightOnOff[pickLightSpot]);
        liSpot.specular = colour( 0.9f, 0.7f, 0.6f ) * vec4(lightOnOff[pickLightSpot]);
        liSpot.decay    = vec3( 0, 0.005f, 0.001f );


     lightSys::line liLine;
        liLine.posA     = (mat4::rotateY(timeModX) * vec3(224,0,0)) + (mat4::rotateY(timeModY) * vec3(-128,480,0));
        liLine.posB     = (mat4::rotateY(timeModX) * vec3(224,0,0)) + (mat4::rotateY(timeModY) * vec3(+128,480,0));
        liLine.ambient  = colour( 0.1f, 0.2f, 0.4f ) * vec4(lightOnOff[pickLightLine]);
        liLine.diffuse  = colour( 0.2f, 0.3f, 0.4f ) * vec4(lightOnOff[pickLightLine]);
        liLine.specular = colour( 0.6f, 0.2f, 0.8f ) * vec4(lightOnOff[pickLightLine]);
        liLine.decay    = vec3( 0, 0, 0.05f );


    // Textures
    static gl::texture texTest   ( "cubeTexTest.png" );
    static gl::texture texShine  ( "noise.jpg" );
    static gl::texture texPicture( "test.png" );
    static gl::texture texWhite  ( "white.png" );
    static gl::texture texBlack  ( "black.png" );
    const gl::texture* const texPick = pickFbo->getTexColour();

        GLint tiuIndexColour = 0; // Texture Image Unit binding
        GLint tiuIndexShine  = 1; // ...

        glActiveTexture( GL_TEXTURE0 + tiuIndexColour );
        glBindTexture( GL_TEXTURE_2D, texBlack );

        glActiveTexture( GL_TEXTURE0 + tiuIndexShine );
        glBindTexture( GL_TEXTURE_2D, texShine );

        assert( GL_NO_ERROR == glGetError() );


    // Camera
    static camera cam( vec3(256,256,420),  vec3(0,224,0),  vec3(0,1,0) );
        cam.move ( inputSys::ctrlAxisMove  * 5.0f );
        cam.pitch( inputSys::ctrlAxisPitch * 360.0f * 0.005f * coreSys::zoomMagFactor );
        cam.yaw  ( inputSys::ctrlAxisYaw   * 360.0f * 0.005f * coreSys::zoomMagFactor );
        cam.roll ( inputSys::ctrlAxisRoll  * 360.0f * 0.005f );

        // Spotlight POV
        //cam.lookAt( liSpot.pos, liSpot.pos + liSpot.vec, vec3(0,1,0) );
    

    // Shaders
    static gl::shaderProgram progLight    ( "light" );
    static gl::shaderProgram progLightToon( "light", "lightToon" );
    static gl::shaderProgram progSimple   ( "simple" );
    static gl::shaderProgram progSimpleTex( "simpleTex" );
    static gl::shaderProgram progColour   ( "colour" );
    static gl::shaderProgram progPick     ( "simple", "pick" );
    static gl::shaderProgram progDistort  ( "distort", "simple" );
    


    // Shader to use when drawing main part of the scene
    gl::shaderProgram* progMain = &progLight;


    
    // Toon shader
    if (coreSys::renderToon)
        progMain = &progLightToon;



    // Matrices
    using namespace matrix;
        matProj  = mat4::perspective( screen::fovY*coreSys::zoomMagFactor, screen::aspect, 24.0f, 16384.0f );
        matView  = cam.viewMatrix();
        matModel = mat4::identity();


        // Colours for cartoon shading
        colour toonColour[4] = { 
            colour( 0.12f, 0.01f, 0.23f ),
            colour( 0.50f, 0.11f, 0.21f ),
            colour( 0.95f, 0.60f, 0.28f ),
            colour( 0.98f, 0.92f, 0.97f )
        };


        // Light/Toon/Pick
        glUseProgram( *progMain );
        progMain->setUniform( "toonColour", toonColour, 4 );

        progMain->setUniform( "matProj",  matProj  );
        progMain->setUniform( "matView",  matView  );

        progMain->setUniform( "texColour", tiuIndexColour );
        progMain->setUniform( "texShine",  tiuIndexShine  );

        progMain->setUniform( "globalLightAmbient", liGlobal.ambient );

        progMain->setUniform( "dirLightWorldVec", liDir.vec );
        progMain->setUniform( "dirLightAmbient",  liDir.ambient  );
        progMain->setUniform( "dirLightDiffuse",  liDir.diffuse  );
        progMain->setUniform( "dirLightSpecular", liDir.specular );

        progMain->setUniform( "pointLightWorldPos", liPoint.pos      );
        progMain->setUniform( "pointLightAmbient",  liPoint.ambient  );
        progMain->setUniform( "pointLightDiffuse",  liPoint.diffuse  );
        progMain->setUniform( "pointLightSpecular", liPoint.specular );
        progMain->setUniform( "pointLightDecay",    liPoint.decay    );

        progMain->setUniform( "spotLightWorldPos", liSpot.pos      );
        progMain->setUniform( "spotLightWorldVec", liSpot.vec      );
        progMain->setUniform( "spotLightCone",     liSpot.cone     );
        progMain->setUniform( "spotLightSoftness", liSpot.softness );
        progMain->setUniform( "spotLightAmbient",  liSpot.ambient  );
        progMain->setUniform( "spotLightDiffuse",  liSpot.diffuse  );
        progMain->setUniform( "spotLightSpecular", liSpot.specular );
        progMain->setUniform( "spotLightDecay",    liSpot.decay    );

        progMain->setUniform( "lineLightWorldPosA", liLine.posA     );
        progMain->setUniform( "lineLightWorldPosB", liLine.posB     );
        progMain->setUniform( "lineLightAmbient",   liLine.ambient  );
        progMain->setUniform( "lineLightDiffuse",   liLine.diffuse  );
        progMain->setUniform( "lineLightSpecular",  liLine.specular );
        progMain->setUniform( "lineLightDecay",     liLine.decay    );

        assert( GL_NO_ERROR == glGetError() );
        




        // World ground
        {
            progMain->setMaterial( *getMaterial(mtrMenuObjOutside) );
            matModel.push();
                matModel.translate( 0, -32, 0 );
                matModel.scale( 16384, 16, 16384 );
                progMain->setUniform( "matModel", matModel );
                drawCube();
            matModel.pop();
        }



        // Rough world surface (of cubes...)
        {
            prng::rngFloat rng( 123457 );
            float extent = 8192;
            float size   = 256;

            for (float x=-extent; x<extent; x+=size+rng.random()*size)
            for (float z=-extent; z<extent; z+=size+rng.random()*size) {
                if (distance( vec3(x,0,z), vec3(0)) > 1440) {
                    matModel.push();
                        matModel.translate( x, -size*rng.random(), z );
                        matModel.scale( size*2, size, size*2 );
                        progMain->setUniform( "matModel", matModel );
                        drawCube();
                    matModel.pop();
                }
            }
        }



        
        // Room
        const vec3  roomSize  = vec3(1024,512,1024);
        const float wallDepth = 32;
        const vec3  floorSize = vec3( roomSize.x, wallDepth, roomSize.z );
        const vec3  wallTrans = vec3( roomSize.x/2 + wallDepth/2, roomSize.y/2,             0 );
        const vec3  wallSize  = vec3( wallDepth,                  roomSize.y + wallDepth*3, roomSize.z );
        {
            // Floor (surface centre is 0,0,0)
            progMain->setMaterial( *getMaterial(mtrMenuObjFloor) );
            matModel.push();
                matModel.translate( 0, -wallDepth/2, 0 );
                matModel.scale( floorSize );
                progMain->setUniform( "matModel", matModel );
                drawCube();
            matModel.pop();

            // Ceiling
            progMain->setMaterial( *getMaterial(mtrMenuObjCeiling) );
            matModel.push();
                matModel.translate( 0, roomSize.y + wallDepth, 0 );
                matModel.scale( floorSize );
                progMain->setUniform( "matModel", matModel );
                drawCube();
            matModel.pop();

            // Walls
            progMain->setMaterial( *getMaterial(mtrMenuObjWalls) );
            matModel.push();
                matModel.translate( wallTrans );
                matModel.scale( wallSize );
                progMain->setUniform( "matModel", matModel );
                drawCube();
            matModel.pop();

            matModel.push();
                matModel.rotateY( 90 );
                matModel.translate( wallTrans );
                matModel.scale( wallSize );
                progMain->setUniform( "matModel", matModel );
                drawCube();
            matModel.pop();

            matModel.push();
                matModel.rotateY( 180 );
                matModel.translate( wallTrans );
                matModel.scale( wallSize );
                progMain->setUniform( "matModel", matModel );
                drawCube();
            matModel.pop();
        }



        // Table
        const vec3 tableSize    = vec3( 256, 16, 384 );
        const vec3 tableLegSize = vec3( 32,  96, 32  );
        {
            const vec3  size       = tableSize;
            const vec3  legSize    = tableLegSize;
            const vec3  sizeh      = size / 2.0f;
            const float legOffsetY = -sizeh.y - legSize.y/2;

            progMain->setMaterial( *getMaterial(mtrMenuObjTable) );
            matModel.push();
                
                // Pos
                matModel.translate( 0, legSize.y + sizeh.y, 0 );

                // Table surface
                matModel.push();
                    glActiveTexture( GL_TEXTURE0 + tiuIndexShine );
                    glBindTexture( GL_TEXTURE_2D, texWhite );

                    matModel.scale( size );
                    progMain->setUniform( "matModel", matModel );
                    drawCube();

                    glBindTexture( GL_TEXTURE_2D, texShine );
                matModel.pop();
               

                // Table legs
                matModel.push();
                    matModel.translate( 0, legOffsetY, 0 );

                    matModel.push();
                        matModel.translate( sizeh.x-legSize.x, 0, sizeh.z-legSize.z );
                        matModel.scale( legSize );
                        progMain->setUniform( "matModel", matModel );
                        drawCube();
                    matModel.pop();

                    matModel.push();
                        matModel.translate( -sizeh.x+legSize.x, 0, sizeh.z-legSize.z );
                        matModel.scale( legSize );
                        progMain->setUniform( "matModel", matModel );
                        drawCube();
                    matModel.pop();

                    matModel.push();
                        matModel.translate( sizeh.x-legSize.x, 0, -sizeh.z+legSize.z );
                        matModel.scale( legSize );
                        progMain->setUniform( "matModel", matModel );
                        drawCube();
                    matModel.pop();

                    matModel.push();
                        matModel.translate( -sizeh.x+legSize.x, 0, -sizeh.z+legSize.z );
                        matModel.scale( legSize );
                        progMain->setUniform( "matModel", matModel );
                        drawCube();
                    matModel.pop();
                matModel.pop();

            matModel.pop();
        }


        


        // Picture frame
        {
            const vec3 size = 48.0f;
            progMain->setMaterial( *getMaterial(mtrMenuObjPictureFrame) );
            matModel.push();

                matModel.rotateY(  15 );
                matModel.rotateX( -30 );
                matModel.translate( -tableSize.x/4, tableSize.y + tableLegSize.y + size.y - 4, 0 );
                matModel.scale( size );

                matModel.push();

                    // Stand
                    matModel.push();
                        matModel.translate( 0, 0, -0.35f );
                        matModel.rotateX( 330 );                        
                        matModel.scale( 0.5f, 0.15f, 0.65f );
                        progMain->setUniform( "matModel", matModel );
                        drawCube();
                    matModel.pop();

                    // Back
                    matModel.scale( 1, 1, 0.15f );
                    progMain->setUniform( "matModel", matModel );
                    drawCube();                    

                    // Picture
                    glActiveTexture( GL_TEXTURE0 + tiuIndexColour );
                    glBindTexture( GL_TEXTURE_2D, texPicture );
                    glActiveTexture( GL_TEXTURE0 + tiuIndexShine );
                    glBindTexture( GL_TEXTURE_2D, texWhite);
                        
                        matModel.push();
                            matModel.translate( 0, 0, 0.8f );
                            matModel.scale( 0.75f, 0.75f, 1 );
                            progMain->setUniform( "matModel", matModel );
                            progMain->setMaterial( material::glass );
                            drawPlane();
                            progMain->setMaterial( *getMaterial(mtrMenuObjPictureFrame) );
                        matModel.pop();
                        
                    glActiveTexture( GL_TEXTURE0 + tiuIndexColour );
                    glBindTexture( GL_TEXTURE_2D, texBlack);
                    glActiveTexture( GL_TEXTURE0 + tiuIndexShine );
                    glBindTexture( GL_TEXTURE_2D, texShine);
                    
                    // Frame
                    matModel.push();
                        matModel.translate( 0.45f, 0, 0.5f );
                        matModel.scale( 0.1f, 1, 1 );
                        progMain->setUniform( "matModel", matModel );
                        drawCube();
                    matModel.pop();
                    
                    matModel.push();
                        matModel.translate( -0.45f, 0, 0.5f );
                        matModel.scale( 0.1f, 1, 1 );
                        progMain->setUniform( "matModel", matModel );
                        drawCube();
                    matModel.pop();
                    
                    matModel.push();
                        matModel.translate( 0, 0.45f, 0.5f );
                        matModel.scale( 1, 0.1f, 1 );
                        progMain->setUniform( "matModel", matModel );
                        drawCube();
                    matModel.pop();
                    
                    matModel.push();
                        matModel.translate( 0, -0.45f, 0.5f );
                        matModel.scale( 1, 0.1f, 1 );
                        progMain->setUniform( "matModel", matModel );
                        drawCube();
                    matModel.pop();

                matModel.pop();

            matModel.pop();
        }




        // Picture frame 2 - has FBO texture
        {
            const vec3 size = 48.0f;
            progMain->setMaterial( *getMaterial(mtrMenuObjPictureFrame) );
            matModel.push();

                matModel.translate( -tableSize.x/4, tableSize.y + tableLegSize.y + size.y/2.5f, 0 );
                matModel.translate( 0, 0, -128 );
                matModel.rotateY(  15 + 180 );
                matModel.rotateX( -15 );
                matModel.scale( size.x, size.y*0.75f, size.z*0.75f );

                matModel.push();

                    // Stand
                    matModel.push();
                        matModel.translate( 0, 0, -0.35f );
                        matModel.rotateX( 330 );                        
                        matModel.scale( 0.5f, 0.15f, 0.65f );
                        progMain->setUniform( "matModel", matModel );
                        drawCube();
                    matModel.pop();

                    // Back
                    matModel.scale( 1, 1, 0.15f );
                    progMain->setUniform( "matModel", matModel );
                    drawCube();                    

                    // Picture
                    glActiveTexture( GL_TEXTURE0 + tiuIndexColour );
                    glBindTexture( GL_TEXTURE_2D, *texPick );
                    glActiveTexture( GL_TEXTURE0 + tiuIndexShine );
                    glBindTexture( GL_TEXTURE_2D, texWhite);
                        
                        matModel.push();
                            matModel.translate( 0, 0, 0.8f );
                            matModel.scale( 0.75f, 0.75f, 1 );
                            progMain->setUniform( "matModel", matModel );
                            progMain->setMaterial( material::glass );
                            drawPlane();
                            progMain->setMaterial( *getMaterial(mtrMenuObjPictureFrame) );
                        matModel.pop();
                        
                    glActiveTexture( GL_TEXTURE0 + tiuIndexColour );
                    glBindTexture( GL_TEXTURE_2D, texBlack);
                    glActiveTexture( GL_TEXTURE0 + tiuIndexShine );
                    glBindTexture( GL_TEXTURE_2D, texShine);
                    
                    // Frame
                    matModel.push();
                        matModel.translate( 0.45f, 0, 0.5f );
                        matModel.scale( 0.1f, 1, 1 );
                        progMain->setUniform( "matModel", matModel );
                        drawCube();
                    matModel.pop();
                    
                    matModel.push();
                        matModel.translate( -0.45f, 0, 0.5f );
                        matModel.scale( 0.1f, 1, 1 );
                        progMain->setUniform( "matModel", matModel );
                        drawCube();
                    matModel.pop();
                    
                    matModel.push();
                        matModel.translate( 0, 0.45f, 0.5f );
                        matModel.scale( 1, 0.1f, 1 );
                        progMain->setUniform( "matModel", matModel );
                        drawCube();
                    matModel.pop();
                    
                    matModel.push();
                        matModel.translate( 0, -0.45f, 0.5f );
                        matModel.scale( 1, 0.1f, 1 );
                        progMain->setUniform( "matModel", matModel );
                        drawCube();
                    matModel.pop();

                matModel.pop();

            matModel.pop();
        }



        glUseProgram( 0 );

        



        // Lights (solid colour)
        {
            gl::shaderProgram* progLightModels = &progColour;

            

            // Override shader when in dedicated picking mode
            if (pickMode)
                progLightModels = &progPick;

            matModel.push();

                glUseProgram( *progLightModels );
                progLightModels->setUniform( "matProj",  matProj  );
                progLightModels->setUniform( "matView",  matView  );
                progLightModels->setUniform( "matModel", matModel );

                // Directional light
                matModel.push();
                    matModel.translate( cam.pos + (-liDir.vec * 4096.0f) );
                    matModel.scale( 256.0f );
                    progLightModels->setUniform( "pickColour", pickMap.getCol(pickLightDir) );
                    progLightModels->setUniform( "diffuse", lerp(liDir.diffuse+liDir.ambient, colour::white, 0.5f) );
                    progLightModels->setUniform( "matModel", matModel );
                    drawCube();
                matModel.pop();

                // Point light
                matModel.push();
                    matModel.translate( liPoint.pos );
                    matModel.scale( 16.0f );
                    progLightModels->setUniform( "pickColour", pickMap.getCol(pickLightPoint) );
                    progLightModels->setUniform( "diffuse", lerp(liPoint.diffuse+liPoint.ambient, colour::white, 0.5f) );
                    progLightModels->setUniform( "matModel", matModel );
                    drawCube();
                matModel.pop();

                // Spotlight
                matModel.push();
                    matModel.translate( liSpot.pos );
                    matModel.orient( liSpot.vec );
                    matModel.scale( 32.0f );
                    progLightModels->setUniform( "pickColour", pickMap.getCol(pickLightSpot) );
                    progLightModels->setUniform( "diffuse", lerp(liSpot.diffuse+liSpot.ambient, colour::white, 0.5f) );
                    progLightModels->setUniform( "matModel", matModel );
                    drawTrapezoid();
                    matModel.translate(0,0,0.35f);
                    matModel.scale( 0.5f );
                    progLightModels->setUniform( "diffuse", colour::white );
                    progLightModels->setUniform( "matModel", matModel );
                    drawCube();
                matModel.pop();

                // Line light
                matModel.push();
                    vec3  liLineDelta = liLine.posA - liLine.posB;
                    float liLineLen   = length( liLineDelta );
                    matModel.translate( lerp( liLine.posA, liLine.posB, 0.5f) );
                    matModel.orient( liLineDelta );
                    matModel.scale( 16.0f, 16.0f, liLineLen );
                    progLightModels->setUniform( "pickColour", pickMap.getCol(pickLightLine) );
                    progLightModels->setUniform( "diffuse", lerp(liLine.diffuse+liLine.ambient, colour::white, 0.5f) );
                    progLightModels->setUniform( "matModel", matModel );
                    drawCube();
                matModel.pop();

                glUseProgram( 0 );
                assert( GL_NO_ERROR == glGetError() );

            matModel.pop();
        }

        assert( GL_NO_ERROR == glGetError() );





        // vertexStream test - draws a spiral thing
        const int vertCount = 2048;
        static vertexStream vs( vertCount );
            
        glUseProgram( progSimple );
        progSimple.setUniform( "matProj", matProj );
        progSimple.setUniform( "matView", matView );

        matModel.push();

            matModel.identity();
            matModel.translate( tableSize.x/3, tableSize.y + tableLegSize.y, tableSize.y/3 );
            progSimple.setUniform( "matModel", matModel );

            vs.begin( GL_LINE_STRIP );
                for (int i=0; i<vertCount; i++)
                {
                    float twists = 10;
                    float height = 64;
                    float frac   = float(i) / float(vertCount-1);
                    float radius = 32 * frac;
                    float angle  = float(coreSys::step*4) + lerp(0,twists*360,frac);
                    float rads   = degToRad( angle );
                    float ypos   = height * sqr(frac);
                    vec3  v      = vec3( sin(rads)*radius, ypos, cos(rads)*radius );
                    vs.setColour( lerp( colour::red, colour::white, frac ) );                    
                    vs.emit( v );
                }
            vs.end();

            // And a floating lit cube for good measure.
            glUseProgram( *progMain );
            matModel.push();
                float hover = 6.0f * sin(float(coreSys::step/64.0f));
                matModel.translate( 0, 64+hover, 0 );
                matModel.rotateX( coreSys::step * 0.10f );
                matModel.rotateY( coreSys::step * 0.25f );
                matModel.rotateZ( coreSys::step * 0.45f );
                matModel.scale(24);

                progMain->setUniform( "matModel", matModel );
                drawCube();
            matModel.pop();

        matModel.pop();



        // meshStream and distortion shader
        glUseProgram( progDistort );
        progDistort.setUniform( "matProj", matProj );
        progDistort.setUniform( "matView", matView );
        progDistort.setUniform( "distortionLevel", sineSync(coreSys::step,1080)*2.0f );

        matModel.push();
            matModel.translate( 32, 1280, 0 );
            matModel.rotateX( coreSys::step * 0.10f );
            matModel.rotateY( coreSys::step * 0.25f );
            matModel.rotateZ( coreSys::step * 0.75f );
            matModel.scale(72.0f);
            progDistort.setUniform( "matModel", matModel );
            meshTest->draw();
        matModel.pop();



        // Disable shaders
        glUseProgram( 0 );



        // Disable hidden surface removal
        glDisable( GL_CULL_FACE );
        glDisable( GL_DEPTH_TEST );

        assert( GL_NO_ERROR == glGetError() );
}





void evDraw() {
    // Draw everything
    drawScene( false );



	// Display the buffer drawn upon, then swap to the other one.
    glutSwapBuffers();
}





// Called whenever the window is resized.
void evReshape( int newSizeX, int newSizeY ) {
    // Update screen
    setViewportAspectCorrect( newSizeX, newSizeY );

    // New FBO needed
    delete pickFbo; // Get rid of old one
    pickFbo = new gl::fbo( newSizeX, newSizeY, true );
}





// Key press
void evKeyboardDown( unsigned char key, int x, int y ) {
    inputSys::core::keyStateEv[ key ] = true;
}





// Key release
void evKeyboardUp( unsigned char key, int x, int y ) {
    inputSys::core::keyStateEv[ key ] = false;
}




// Key press (special)
void evKeyboardSpecialDown( int key, int x, int y ) {
    using namespace inputSys::core;
    keyStateEv[ key + keySpecialOffset ] = true;
}





// Key release (special)
void evKeyboardSpecialUp( int key, int x, int y ) {
    using namespace inputSys::core;
    keyStateEv[ key + keySpecialOffset ] = false;
}




// Mouse
void evMouse( int button, int state, int x, int y ) {
    if (button == GLUT_LEFT_BUTTON
    &&  state  == GLUT_DOWN)
        doPicking( x, y );
}





int main( int argc, char* argv[] )
{   
    // GLUT
    {
        // Init
        glutInit( &argc, argv );
        glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE );

        // Create OpenGL 3.3 Core context
        glutInitContextVersion( 3, 3 );
        glutInitContextProfile( GLUT_CORE_PROFILE );

        // Create window
        screen::init( 960, 600 );
        glutInitWindowSize( int(screen::sizeX), int(screen::sizeY) ); 
	    glutCreateWindow( "Lee Coakley - GL 3D" );

        // Setup menus
        menuSys::mtrMenuCreate();

        // Glut has a fullscreen mode, but it's not too usable.
        // According to the docs it's supposed to default to a usable resolution, but it doesn't.
        // Compounding this, the functions to decide whether a display mode works are also broken.
        //glutGameModeString( "1920x1200:32@60" );
        //glutEnterGameMode();
        //glutSetCursor(GLUT_CURSOR_NONE);
    }
    


    // GLEW
    {
        // Need to enable glewExperimental to avoid a known bug in GLEW.
        // See: http://www.opengl.org/wiki/Extension_Loading_Library#GLEW
        glewExperimental = true;

        // Init
        if (GLEW_OK != glewInit() ) { std::cerr << "GLEW init failed!\n";     }
        if (!GLEW_VERSION_3_3)      { std::cerr << "GL 3.3 Core not supported!\n"; }

        // Just to be sure.  This won't be exposed if something went wrong.
        assert( GLEW_ARB_framebuffer_object );

        // GLUT's implementation flaw causes an error to be thrown.
        // Need to catch it here so it won't trigger asserts in my rendering code.
        glGetError(); 
    }
    
    


    // GLUT callbacks
    {
        // Send only keypress/release signals.
        // Much easier to make nice controls this way.
        glutIgnoreKeyRepeat( true );


        // Set GLUT callbacks
        glutKeyboardFunc  ( evKeyboardDown        ); // Key press
        glutKeyboardUpFunc( evKeyboardUp          ); // Key release
        glutSpecialFunc   ( evKeyboardSpecialDown );
        glutSpecialUpFunc ( evKeyboardSpecialUp   );
        glutMouseFunc     ( evMouse );

        glutTimerFunc  ( coreSys::stepFrequency, evStep, 0 );
	    glutDisplayFunc( evDraw );
        glutReshapeFunc( evReshape );
        glutCloseFunc  ( evExit );
    }


    // Init my stuff
    evStart();


    // Enter GLUT main loop
	glutMainLoop();
    

    // Done
    return EXIT_SUCCESS;
}


