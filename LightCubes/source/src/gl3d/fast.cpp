

#include "fast.h"
#include "def.h"
#include <cmath>
#include <xmmintrin.h>



namespace approx
{
    // Fast approximate reciprocal square root.
    // - 11-bit precision
    // - No infinity: returns 0 if x==0
    float rsqrtzero( float x ) {
        // Divss and sqrtss are slow ops which don't get pipelined.
        // rsqrtss is very fast and doesn't stall the pipeline.
    
        float r;
        __m128 in,z,rsq,isZ,mret;         // Opcode    Action
        in   = _mm_set_ss( x );           // movss     Load scalar to SSE vector register
        z    = _mm_setzero_ps();          // xorps     Set register to zero without memory access
        isZ  = _mm_cmpneq_ss( in, z );    // cmpneqss  Set all bits to 1 if input is not zero
        rsq  = _mm_rsqrt_ss( in );        // rsqrtss   Compute 1.0f / sqrt(x) with 11-bit precision
        mret = _mm_and_ps( rsq, isZ );    // andps     Set all bits to 0 if input was 0, else retain
               _mm_store_ss( &r, mret );  // movss     Store scalar again
        return r;
    }



    // Fast approximate sine.
    // Range [-pi,+pi].  Exact at intervals of pi/2, including zero.
    float sin( float rads ) {
        using def::pi;

        const float b =  4.0f /  pi;
        const float c = -4.0f / (pi*pi);
        const float p = 0.225f;

        float sine = (b * rads) + (c * rads * abs(rads));
        return       (p * ((sine * abs(sine)) - sine)) + sine;
    }
};

