

// Map wrapper.
// The default interface is quite nasty.

#pragma once
#include <map>



template < typename typeKey, typename typeElem >
class hmap
{
  private:
    typedef typename std::map <typeKey,typeElem> typeThis;
    typedef typename std::pair<typeKey,typeElem> typePair;
    typedef typename typeThis::const_iterator    iter;
    


  private:
    typeThis xmap;



  public:
    void insert( const typeKey& key, const typeElem& elem )
    {
        // Add a pair to the map.
        // O(log n)
        
        xmap.insert( typePair(key,elem) );
    }



    bool exists( const typeKey& key ) const
    {
        // Check if a given key exists.
        // O(log n)

        size_t count = xmap.count( key );
        return (count == 1);
    }



    const typeElem& get( const typeKey& key ) const
    {
        // Given the key, get a reference to the linked element.
        // Make sure it actually exists first.
        // O(log n)

        iter ret = xmap.find( key );
        return ((*ret).second);
    }



    void erase( const typeKey& key )
    {
        // Erase a key/element pair from the map.
        // O(log n)

        iter ate = xmap.find( key );

        if (ate != xmap.end())
        {
            xmap.erase( ate );
        }
    }



    size_t size() const
    {
        return xmap.size();
    }



    void clear()
    {
        xmap.clear();
    }
};