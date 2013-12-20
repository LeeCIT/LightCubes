

// Program configuration.
// Never quite got around to using it much.

#pragma once



namespace config
{    
    // Texture sampling defaults
    extern bool  texLinear;        // Enable linear filtering.
    extern bool  texLinearMip;     // Enable linear filtering between mipmaps.
    extern float texAnisoMax;      // Set maximum anisotropic filtering level.
    extern bool  texForceCompress; // Force all textures to be compressed with DXT5.
};