


// Construct and destruct objects in-place.
// Intended for use inside containers.

#pragma once



namespace memory {

        template< typename T >
        T* constructInPlace( T* const place ) {
            return new (place) T;
        }



        template< typename T >
        T* constructCopyInPlace( T* const place, const T& objectToCopy ) {
            return new (place) T( objectToCopy );
        }



        template< typename T >
        void destructInPlace( T* const place ) {
            place->~T();
        }

};