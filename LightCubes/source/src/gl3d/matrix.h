

// Matrix - Exposes matrix stack functionality.
// I used an OO design here rather than the modal OpenGL design.
// Also the View matrix is now separate from the Model matrix.

#pragma once
#include "matrixStack.h"



namespace matrix {
    extern matrixStack matProj;
    extern matrixStack matView;
    extern matrixStack matModel;
};
