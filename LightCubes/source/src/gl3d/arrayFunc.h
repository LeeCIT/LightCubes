

// Generic array functions.

#pragma once



template <typename type>
type* genArrayLinear( type start, type count, type step=1 ) {
    type* data = new type[ count ];

    for (type i=0; i<count; i++)
        data[i] = start + (i*step);

    return data;
}