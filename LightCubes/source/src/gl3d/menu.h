

// FreeGLUT Menus

#pragma once
#include "glCore.h"
#include "material.h"
#include <string>



namespace menuSys
{
    struct mtrMenuObjLink {
        std::string     objName;
        int             objIndex;
        const material* mtrPtr;
    };



    struct mtrMenuMtrLink {
        const material* mtrPtr;
        std::string     mtrName;
    };


    const int mtrMenuObjCount = 6;
    const int mtrMenuMtrCount = 25;
    extern mtrMenuObjLink mtrMenuObjLinks[ mtrMenuObjCount ];
    extern mtrMenuMtrLink mtrMenuMtrLinks[ mtrMenuMtrCount ];

    void doMenuMaterialChange( int callbackData );
    void mtrMenuCreate();
};



const enum mtrMenuObjects {
    mtrMenuObjTable,         
    mtrMenuObjPictureFrame,  
    mtrMenuObjFloor,         
    mtrMenuObjCeiling,       
    mtrMenuObjWalls,         
    mtrMenuObjOutside,
};



const material* getMaterial( mtrMenuObjects obj );