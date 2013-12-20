

/**
    Container which does not automatically use constructors/destructors.
    It's for dealing with raw bytes in a relatively friendly way.
*/



#pragma once
#include <cassert>
#include <memory>



namespace memory
{

    template <
        typename  T,
        const int alignment = 1  // If <= 1, uses malloc/free, otherwise uses aligned versions
    >
    class raw
    {

        ///////////////////////////////////////////////////////////////////////////
        // Members
        ///////////////////////////////////////////////////////////////////////////
        private:
            // Both vars are set by internal allocate/deallocate functions.
            T*     data;
            size_t dataCount;

            #ifdef _DEBUG
                bool hasDestructed;
                #define initDestructCheck()   hasDestructed = false;
                #define assertDestructCheck() assert( ! hasDestructed )
                #define assertRangeCheck(i)   assert( i>=0 && i<=dataCount && data!=nullptr )
                #define assertNullCheck()     assert( data != nullptr )
            #else
                #define initDestructCheck()
                #define assertDestructCheck()
                #define assertRangeCheck(i)
                #define assertNullCheck()
            #endif





        ///////////////////////////////////////////////////////////////////////////
        // Public
        ///////////////////////////////////////////////////////////////////////////
        public:
            // Construct (default, with no alignedContainer allocated)
            raw() {
                initDestructCheck();
                data      = nullptr;
                dataCount = 0;
            }



            // Construct (size)
            explicit raw( const size_t& count ) {
                initDestructCheck();
                allocateMemory( count );
            }



            // Construct (element-wise copy)
            explicit raw( const T* const source, const size_t& count ) {
                initDestructCheck();
                allocateMemory( count );
                copyElements( source, count );
            }



            // Construct (Copy)
            raw( const raw& other ) {
                initDestructCheck();
                allocateMemory( other.size() );
                copyBytes( other.data, other.bytes() );
            }



            // Construct (Move)
            raw( raw&& other ) {
                initDestructCheck();
                takeMemoryFrom( other );
            }



            // Destruct
            ~raw() {
                assert( (data == nullptr)  ?  (size()==0)  :  true ); // Ensure state consistency
                assertDestructCheck();
                deallocateMemory();
            }



            // Pointer cast operator (somewhat dangerous...)
            operator T* () const {
                assertDestructCheck();
                assertNullCheck();
                return data;
            }



            // = operator
            const raw& operator = ( const raw& other ) {
                assertDestructCheck();

                if (size() != other.size()) {
                    deallocateMemory();
                    allocateMemory( other.size() );
                }

                copyBytes( other.data, other.bytes() );

                return *this;
            }



            // [] const operator
            const T& operator [] ( const size_t& i ) const {
                assertDestructCheck();
                assertRangeCheck(i);
                return data[i];
            }



            // [] operator
            T& operator [] ( const size_t& i ) {
                assertDestructCheck();
                assertRangeCheck(i);
                return data[i];
            }



            // Operator ==.  True if all bytes are the same in both containers.
            bool operator == ( const raw& other ) {
                assertDestructCheck();
                if (size() != other.size())
                    return false;

                return (0 == memcmp(data, other.data, bytes()));
            }



            // Operator !=
            bool operator != ( const raw& other ) {
                assertDestructCheck();
                return ! (*this == other);
            }



            // Data pointer
            T* ptr() const {
                assertNullCheck();
                assertDestructCheck();
                return data;
            }



            // Iterator begin (just a pointer)
            T* begin() const {
                assertDestructCheck();            
                return data;
            }



            // Iterator end (one past the last element)
            T* end() const {
                assertDestructCheck();
                return data + size();
            }

            

            // Size (as logical element count of templated type).
            size_t size() const {
                return dataCount;
            }



            // Size in bytes (allocated memory).
            size_t bytes() const {
                return dataCount * sizeof(T);
            }



            // Whether there's no memory allocated
            bool empty() const {
                return (dataCount == 0);
            }



            // Empty the container.  Deallocates its memory.
            void clear() {
                deallocateMemory();
            }



            // Copy in terms of logical elements into this container.
            void copyElements( const T* const source,  const size_t& count ) {
                size_t byteCount = count * sizeof(T);
                assert( byteCount <= bytes() );

                if (byteCount > 0)
                    memcpy( data, source, byteCount );
            }



            // Copy raw bytes into this container.
            void copyBytes( const void* const source,  const size_t& bytesToCopy ) {
                assert( bytesToCopy <= bytes() );

                if (bytesToCopy > 0)
                    memcpy( data, source, bytesToCopy );
            }



            // Zeroes the entire memory block.
            void zero() {
                assertDestructCheck();
                assertNullCheck();
                memset( data, 0, bytes() );
            }



            // Take the contents of another raw container.
            // The other container is emptied and its state becomes equivalent to having been default-constructed.
            void move( raw& other ) {
                deallocateMemory();
                takeMemoryFrom( other );
            }



            // Resize in terms of logical elements.  Reallocates and does a bitwise copy.
            void resize( const size_t& newSize ) {
                if (newSize == size())
                    return;

                      auto   newMem     = raw<T,alignment>();
                const size_t oldSize    = size();
                const size_t minOfSizes = (newSize < oldSize)  ?  newSize  :  oldSize;

                newMem.allocateMemory( newSize );
        
                if (data != nullptr)
                    newMem.copyElements( data, minOfSizes );

                move( newMem );
            }



            // In-place default construct at logical index
            T* constructDefaultInPlace( const size_t& index ) {
                assert( index < size() );
                return new (data+index) T;
            }



            // In-place copy construct at logical index
            T* constructCopyInPlace( const size_t& index,  const T& objectToCopy ) {
                assert( index < size() );
                return new (data+index) T( objectToCopy );
            }



             // In-place destruct at logical index
            void destructInPlace( const size_t& index ) {
                assert( index < size() );
                (data+index)->~T();
            }





        ///////////////////////////////////////////////////////////////////////////
        // Internals
        ///////////////////////////////////////////////////////////////////////////
        private:

            // Allocate memory
            void allocateMemory( const size_t& count ) {
                this->dataCount = count;

                static_assert( (alignment > 0),                          "Alignment must be greater than zero." );
                static_assert( (alignment & (alignment-1)) != alignment, "Alignment must be a power of 2."      );

                if (alignment <= 1)
                     this->data = (T*) _aligned_malloc( bytes(), alignment );
                else this->data = (T*)          malloc( bytes()            );

                assert( data != nullptr ); // If malloc fails
            }



            // Deallocate memory
            void deallocateMemory() {
                if (alignment <= 1)
                     _aligned_free( this->data );
                else          free( this->data );

                this->data      = nullptr;
                this->dataCount = 0;
            }



            // Take memory (for move() and move constructor)        
            void takeMemoryFrom( raw& other ) {
                this->data      = other.data;
                this->dataCount = other.dataCount;

                other.data      = nullptr;
                other.dataCount = 0;
            }
    };



};