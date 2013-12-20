

#include "material.h"



// Construct
material :: material( const colour& ambient, const colour& diffuse, const colour& specular, float shine ) {
    this->ambient  = ambient;
    this->diffuse  = diffuse;
    this->specular = specular;
    this->shine    = shine;  
}



material :: material() {
    // Do nothing
}





// Predefined materials
// Source: http://devernay.free.fr/cours/opengl/materials.html
const material material::emerald       = material(   colour( 0.021500f, 0.174500f, 0.021500f ),   colour( 0.075680f, 0.614240f, 0.075680f ),   colour( 0.633000f, 0.727811f, 0.633000f ),    0.600000f * 128.0f   );
const material material::jade          = material(   colour( 0.135000f, 0.222500f, 0.157500f ),   colour( 0.540000f, 0.890000f, 0.630000f ),   colour( 0.316228f, 0.316228f, 0.316228f ),    0.100000f * 128.0f   );
const material material::obsidian      = material(   colour( 0.053750f, 0.050000f, 0.066250f ),   colour( 0.182750f, 0.170000f, 0.225250f ),   colour( 0.332741f, 0.328634f, 0.346435f ),    0.300000f * 128.0f   );
const material material::pearl         = material(   colour( 0.250000f, 0.207250f, 0.207250f ),   colour( 1.000000f, 0.829000f, 0.829000f ),   colour( 0.296648f, 0.296648f, 0.296648f ),    0.088000f * 128.0f   );
const material material::ruby          = material(   colour( 0.174500f, 0.011750f, 0.011750f ),   colour( 0.614240f, 0.041360f, 0.041360f ),   colour( 0.727811f, 0.626959f, 0.626959f ),    0.600000f * 128.0f   );
const material material::turquoise     = material(   colour( 0.100000f, 0.187250f, 0.174500f ),   colour( 0.396000f, 0.741510f, 0.691020f ),   colour( 0.297254f, 0.308290f, 0.306678f ),    0.100000f * 128.0f   );
const material material::brass         = material(   colour( 0.329412f, 0.223529f, 0.027451f ),   colour( 0.780392f, 0.568627f, 0.113725f ),   colour( 0.992157f, 0.941176f, 0.807843f ),    0.217949f * 128.0f   );
const material material::bronze        = material(   colour( 0.212500f, 0.127500f, 0.054000f ),   colour( 0.714000f, 0.428400f, 0.181440f ),   colour( 0.393548f, 0.271906f, 0.166721f ),    0.200000f * 128.0f   );
const material material::chrome        = material(   colour( 0.250000f, 0.250000f, 0.250000f ),   colour( 0.400000f, 0.400000f, 0.400000f ),   colour( 0.774597f, 0.774597f, 0.774597f ),    0.600000f * 128.0f   );
const material material::copper        = material(   colour( 0.191250f, 0.073500f, 0.022500f ),   colour( 0.703800f, 0.270480f, 0.082800f ),   colour( 0.256777f, 0.137622f, 0.086014f ),    0.100000f * 128.0f   );
const material material::gold          = material(   colour( 0.247250f, 0.199500f, 0.074500f ),   colour( 0.751640f, 0.606480f, 0.226480f ),   colour( 0.628281f, 0.555802f, 0.366065f ),    0.400000f * 128.0f   );
const material material::silver        = material(   colour( 0.192250f, 0.192250f, 0.192250f ),   colour( 0.507540f, 0.507540f, 0.507540f ),   colour( 0.508273f, 0.508273f, 0.508273f ),    0.400000f * 128.0f   );
const material material::glass         = material(   colour( 0.120000f, 0.130000f, 0.150000f ),   colour( 0.100000f, 0.200000f, 0.300000f ),   colour( 1.950000f, 1.850000f, 2.000000f ),   32.000000f * 128.0f   );
const material material::plasticBlack  = material(   colour( 0.000000f, 0.000000f, 0.000000f ),   colour( 0.010000f, 0.010000f, 0.010000f ),   colour( 0.500000f, 0.500000f, 0.500000f ),    0.250000f * 128.0f   );
const material material::plasticCyan   = material(   colour( 0.000000f, 0.100000f, 0.060000f ),   colour( 0.000000f, 0.509804f, 0.509804f ),   colour( 0.501961f, 0.501961f, 0.501961f ),    0.250000f * 128.0f   );
const material material::plasticGreen  = material(   colour( 0.000000f, 0.000000f, 0.000000f ),   colour( 0.100000f, 0.350000f, 0.100000f ),   colour( 0.450000f, 0.550000f, 0.450000f ),    0.250000f * 128.0f   );
const material material::plasticRed    = material(   colour( 0.000000f, 0.000000f, 0.000000f ),   colour( 0.500000f, 0.000000f, 0.000000f ),   colour( 0.700000f, 0.600000f, 0.600000f ),    0.250000f * 128.0f   );
const material material::plasticWhite  = material(   colour( 0.000000f, 0.000000f, 0.000000f ),   colour( 0.550000f, 0.550000f, 0.550000f ),   colour( 0.700000f, 0.700000f, 0.700000f ),    0.250000f * 128.0f   );
const material material::plasticYellow = material(   colour( 0.000000f, 0.000000f, 0.000000f ),   colour( 0.500000f, 0.500000f, 0.000000f ),   colour( 0.600000f, 0.600000f, 0.500000f ),    0.250000f * 128.0f   );
const material material::rubberBlack   = material(   colour( 0.020000f, 0.020000f, 0.020000f ),   colour( 0.010000f, 0.010000f, 0.010000f ),   colour( 0.400000f, 0.400000f, 0.400000f ),    0.078125f * 128.0f   );
const material material::rubberCyan    = material(   colour( 0.000000f, 0.050000f, 0.050000f ),   colour( 0.400000f, 0.500000f, 0.500000f ),   colour( 0.040000f, 0.700000f, 0.700000f ),    0.078125f * 128.0f   );
const material material::rubberGreen   = material(   colour( 0.000000f, 0.050000f, 0.000000f ),   colour( 0.400000f, 0.500000f, 0.400000f ),   colour( 0.040000f, 0.700000f, 0.040000f ),    0.078125f * 128.0f   );
const material material::rubberRed     = material(   colour( 0.050000f, 0.000000f, 0.000000f ),   colour( 0.500000f, 0.400000f, 0.400000f ),   colour( 0.700000f, 0.040000f, 0.040000f ),    0.078125f * 128.0f   );
const material material::rubberWhite   = material(   colour( 0.050000f, 0.050000f, 0.050000f ),   colour( 0.500000f, 0.500000f, 0.500000f ),   colour( 0.700000f, 0.700000f, 0.700000f ),    0.078125f * 128.0f   );
const material material::rubberYellow  = material(   colour( 0.050000f, 0.050000f, 0.000000f ),   colour( 0.500000f, 0.500000f, 0.400000f ),   colour( 0.700000f, 0.700000f, 0.040000f ),    0.078125f * 128.0f   );