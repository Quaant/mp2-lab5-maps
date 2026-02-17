#ifndef ORDER_MAP_H
#define ORDER_MAP_H

#pragma once
#include "map.h"
#include <stdexcept>

// capacity - размер массива
// n - количество занятых ячеек

template <typename Tkey, typename Tval>
class orderMap : public TMap<Tkey, Tval>
{
    using pair = typename TMap<Tkey, Tval>::pair;
    std::vector<pair *> a;
    size_t size;     // фактическое количество занятых
    size_t capacity; // размер массива

public:
    int binsearch(const Tkey &k)
    {
        int left = 0;
        int right = a.size() - 1;
        while (left <= right)
        {
            int middle = left + (right - left) / 2;
            if (a[middle]->key > k)
            {
                right = middle - 1;
            }
            else if (a[middle]->key < k)
            {
                left = middle + 1;
            }
            else
            {
                return middle;
            }
        }
        return -1;
    }
    int findinsertplace(const Tkey &k)
    {
        int left = 0;
        int right = a.size() - 1;
        while (left <= right)
        {
            int middle = left + (right - left) / 2;
            if (a[middle]->key < k)
            {
                left = middle + 1;
            }
            else
            {
                right = middle - 1;
            }
        }
        return left;
    }
    orderMap()
    {
        size = 0;
        capacity = 0;
    }
    virtual void Insert(const Tkey &k, const Tval &v) override
    {
        int ind = binsearch(k);
        if (ind == -1)
        {
            throw("cannot find place for insert in vector");
        }
        if (size == capacity)
        {
            a.resize();
        }
        pair *b = new pair(k, v);

        int true_ind = findinsertplace(k);
        a.insert(a.begin() + true_ind, b);
        size = a.size();
    }
    virtual void resize() override
    {
        size_t newcapacity = capacity * 1.5 + 1;
        a.reserve(newcapacity);
        capacity = newcapacity;
    }
    orderMap(std::vector<pair *> b)
    {
        capacity = b.size();
        size = b.size();
        for (int i = 0; i < b.size(); i++)
        {
            a.Insert(b[i]);
        }
    }
    virtual bool search(const Tkey &k) override
    {
        if (binsearch(k) == -1)
        {
            return false;
        }
        return true;
    }
    virtual Tval search_elem(const Tkey &k) override
    {
        int index = binsearch(k);
        if (index == -1)
        {
            throw("cannot find key in order map");
        }
        else
        {
            return a[index].val;
        }
    }
    virtual void Remove(const Tkey &k) override
    {
        if (binsearch(k) == -1)
        {
            throw("cannot find key");
        }
        else
        {
            a.erase(a.begin() + binsearch(k));
            size = size - 1;
        }
    }
    virtual void Remove(size_t pos) override
    {
        if (pos > size)
        {
            throw("Index out of range");
        }
        a.erase(a.begin() + pos);
        size = size - 1;
    }
    virtual pair Pop(const Tkey &k) override
    {
        if (binsearch(k) == -1)
        {
            throw("cannot find key");
        }
        pair *b = new pair(a[binsearch(k)]->key, a[binsearch(k)]->val);
        a.erase(a.begin() + binsearch(k));
        size = size - 1;
        return b;
    }
    // ostream &operator<<(ostream &out, orderMap<Tkey, Tval> &l)
    // {
    //     out << "[";
    //     for (int i = 0; i < l.size; i++)
    //     {
    //         out << "{" << l.data[i]->key << ": " << l.a[i]->val << "}";
    //         if (i < size - 1)
    //         {
    //             out << ", ";
    //         }
    //     }
    //     out << "]";
    //     return out;
    // };
};

#endif