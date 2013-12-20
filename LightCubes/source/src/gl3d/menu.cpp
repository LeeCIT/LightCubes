


#include "menu.h"
#include "glCore.h"
#include "material.h"
#include <string>


namespace menuSys
{
    //const int mtrMenuObjCount = 6;
    //const int mtrMenuMtrCount = 25;



    mtrMenuObjLink mtrMenuObjLinks[mtrMenuObjCount] = {
        { "Table        ", mtrMenuObjTable,        &material::pearl        },
        { "Picture Frame", mtrMenuObjPictureFrame, &material::pearl        },
        { "Floor        ", mtrMenuObjFloor,        &material::obsidian     },
        { "Ceiling      ", mtrMenuObjCeiling,      &material::pearl        },
        { "Walls        ", mtrMenuObjWalls,        &material::pearl        },
        { "Outside      ", mtrMenuObjOutside,      &material::plasticWhite }
    };



    mtrMenuMtrLink mtrMenuMtrLinks[mtrMenuMtrCount] =  {
        { &material::emerald      , "emerald      " },
        { &material::jade         , "jade         " },
        { &material::obsidian     , "obsidian     " },
        { &material::pearl        , "pearl        " },
        { &material::ruby         , "ruby         " },
        { &material::turquoise    , "turquoise    " },
        { &material::brass        , "brass        " },
        { &material::bronze       , "bronze       " },
        { &material::chrome       , "chrome       " },
        { &material::copper       , "copper       " },
        { &material::gold         , "gold         " },
        { &material::silver       , "silver       " },
        { &material::glass        , "glass        " },
        { &material::plasticBlack , "plasticBlack " },
        { &material::plasticCyan  , "plasticCyan  " },
        { &material::plasticGreen , "plasticGreen " },
        { &material::plasticRed   , "plasticRed   " },
        { &material::plasticWhite , "plasticWhite " },
        { &material::plasticYellow, "plasticYellow" },
        { &material::rubberBlack  , "rubberBlack  " },
        { &material::rubberCyan   , "rubberCyan   " },
        { &material::rubberGreen  , "rubberGreen  " },
        { &material::rubberRed    , "rubberRed    " },
        { &material::rubberWhite  , "rubberWhite  " },
        { &material::rubberYellow , "rubberYellow " }
    };



    void doMenuMaterialChange( int callbackData ) {
        // Unpack data and change the pointer.
        int objIndex = (callbackData >> 16) & 0x0000FFFF;
        int mtrIndex = (callbackData >>  0) & 0x0000FFFF;

        mtrMenuObjLinks[objIndex].mtrPtr = mtrMenuMtrLinks[mtrIndex].mtrPtr;
    };



    void mtrMenuCreate()
    {
        int subMenuHandles[6];
        int mainMenuHandle;

        for (int obj=0; obj<6; obj++) {
            subMenuHandles[obj] = glutCreateMenu( doMenuMaterialChange );

            for (int mtr=0; mtr<25; mtr++) {
                int packedData = (obj << 16) | mtr; // Pack as two 16-bit ints
                glutAddMenuEntry( mtrMenuMtrLinks[mtr].mtrName.c_str(), packedData );
            }
        }


        mainMenuHandle = glutCreateMenu( doMenuMaterialChange );

        for (int obj=0; obj<6; obj++)
            glutAddSubMenu( mtrMenuObjLinks[obj].objName.c_str(), subMenuHandles[obj] );

        glutAttachMenu( GLUT_RIGHT_BUTTON );
    }
};





const material* getMaterial( mtrMenuObjects obj ) {
    return menuSys::mtrMenuObjLinks[obj].mtrPtr;
}