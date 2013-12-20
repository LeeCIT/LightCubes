

// Material - Determines interaction with light sources.

#pragma once
#include "colour.h"



class material
{
  public:
    colour ambient;
    colour diffuse;
    colour specular;
    float  shine;


  public:
    material( const colour& ambient, const colour& diffuse, const colour& specular, float shine );
    material();



  public:  // Predefined materials
    static const material emerald;
    static const material jade;
    static const material obsidian;
    static const material pearl;
    static const material ruby;
    static const material turquoise;
    static const material brass;
    static const material bronze;
    static const material chrome;
    static const material copper;
    static const material gold;
    static const material silver;
    static const material glass;
    static const material plasticBlack;
    static const material plasticCyan;
    static const material plasticGreen;
    static const material plasticRed;
    static const material plasticWhite;
    static const material plasticYellow;
    static const material rubberBlack;
    static const material rubberCyan;
    static const material rubberGreen;
    static const material rubberRed;
    static const material rubberWhite;
    static const material rubberYellow;
};