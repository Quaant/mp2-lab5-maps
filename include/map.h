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
    virtual void Insert(const Tkey &k, const Tval &v) = 0;

    virtual pair Pop(const Tkey &key) = 0;
    virtual pair Pop(size_t pos) = 0; // дописать в ordermap
    virtual void Remove(const Tkey &key) = 0;
    virtual void Remove(size_t pos) = 0; // дописать в ordermap
    virtual void resize() = 0;           // если массив заполнился, то перевыделяем память, в стд векторе в 2 раза увеличивается, мы будем делать мб в 1.5 раза
};

#endif // MAP_H
