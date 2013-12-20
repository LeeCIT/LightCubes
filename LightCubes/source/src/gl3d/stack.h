

// Stack template
// The std::stack adapter has a nasty interface, so I made my own one.

#pragma once
#include <cassert>
#include <vector>



template <typename type>
class stack
{
  private:
    std::vector<type> core;



  public:
    void push( const type& element ) {
        core.push_back( element );
    }



    type pop() {
        assert(!empty());

        type element = core.back();
        core.pop_back();
        return element;
    }



    type& top() {
        return core.back();
    }



    const type& peek() const {
        return core.back();
    }



    void reserve( size_t size ) {
        core.reserve( size );
    }



    void clear() {
        core.clear();
    }



    size_t size() const {
        return core.size();
    }



    bool empty() const {
        return core.empty();
    }
};