

// Colour
// Can be used directly with OpenGL 3fv and 4fv functions.
// It's really just a special type of vec4.

#pragma once



// Forward declare
    class vec4;



class colour
{
  public:
    float r,g,b,a;
 

  public:
    operator const float* () const;
    operator float*       () const;
    operator const float* ();
    operator float*       ();

    const colour& operator += (  const colour& b  );
    const colour& operator -= (  const colour& b  );
    const colour& operator *= (  const colour& b  );
    const colour& operator /= (  const colour& b  );

    colour( float r, float g, float b, float a=1.0f );
    colour( const vec4& v );
    colour();



  public: // Predefined colours
    static const colour white;
    static const colour gray;
    static const colour black;
    static const colour red;
    static const colour green;
    static const colour blue;
    static const colour lime;
    static const colour orange;
    static const colour yellow;
    static const colour marine;
    static const colour purple;
    static const colour fuschia;
};




//////////////////////////
// Non-member operators
/////////////////////////
colour operator + ( const colour& a,  const colour& b );
colour operator - ( const colour& a,  const colour& b );
colour operator * ( const colour& a,  const colour& b );
colour operator / ( const colour& a,  const colour& b );




////////////////
// Functions
//////////////

colour lerp(  const colour& a,  const colour& b,  float f  );