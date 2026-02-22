#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <vector>

template <typename Tkey, typename Tval>
class TMap
{
protected:
    struct pair
    {
        Tkey key;
        Tval val;
        pair(const Tkey &k, const Tval &v) : key(k), val(v) {}
    };

public:
    virtual bool search(const Tkey &key) = 0;
    virtual Tval search_elem(const Tkey &key) = 0;
    virtual void insert(const Tkey &k, const Tval &v) = 0;

    virtual pair pop(const Tkey &key) = 0;
    virtual void remove(const Tkey &key) = 0;
    virtual void remove(size_t pos) = 0; 
};

#endif // MAP_H
