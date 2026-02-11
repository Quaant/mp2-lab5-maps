#pragma once
#include "map.h"

// capacity - размер массива
// n - количество занятых ячеек

template <typename Tkey, typename Tval>
class orderMap : public TMap<Tkey, Tval>
{
    using Node = typename Tmap<Tkey, Tval>::Node

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
        while (l <= r)
        {
            middle = left + (right - left) / 2;
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

public:
    orderMap()
    {
        n = 0;
        capacity = 0;
    }
    virtual void Insert(const Tkey &k, const Tval &v) override
    {
        int ind = binsearch(k);
        if (ind == 0)
        {
            throw runtime_error("cannot find place for insert in vector")
        }
        if (n == capacity)
        {
            a.resize();
        }
        Node *b = new Node(k, b, nullptr);

        int true_ind = findinsertplace(k);
        a.insert(a.begin() + true_ind, b);
        n = a.size();
    }
    virtual void resize() override
    {
        size_t newcapacity = capacity * 1.5 + 1;
        a.reserve(newcapacity);
        capacity = newcapacity;
    }
    orderMap(vector<Node *> b)
    {
        capacity = b.size();
        n = b.size();
        for (int i = 0; i < b.size(); i++)
        {
            a.Insert(b[i]);
        }
    }
    virtual bool search(const Tkey &key) override
    {
        if (binsearch(k) == -1)
        {
            return false;
        }
        return true;
    }
    virtual Node search(const Tkey &key) override
    {
        if (binsearch(k) == -1)
        {
            throw runtime_error("cannot find key in order map")
        }
        else
        {
            return a[binsearch(k)];
        }
    }
    virtual void Remove(const Tkey &k) override
    {
        if (binsearch(k) == -1)
        {
            throw runtime_error("cannot find key");
        }
        else
        {
            a.erase(a.begin() + binsearch(k));
            n = n - 1;
        }
    }
    virtual Node Pop(const Tkey &k) override
    {
        if (binsearch(k) == -1)
        {
            throw runtime_error("cannot find key");
        }
        Node *b = new Node(a[binsearch(k)]->key, a[binsearch(k)]->val, nullptr);
        a.erase(a.begin() + binsearch(k));
        n = n - 1;
        return b;
    }
};