#ifndef ORDER_MAP_H
#define ORDER_MAP_H

#pragma once
#include "map.h"
#include <stdexcept>

// n - количество занятых ячеек

template <typename Tkey, typename Tval>
class orderMap : public TMap<Tkey, Tval>
{
    using pair = typename TMap<Tkey, Tval>::pair;
    std::vector<pair *> a;
    size_t size; // фактическое количество занятых

public:
    int binsearch(const Tkey &k)
    {
        if (size == 0)
        {
            return -1;
        }

        int left = 0;
        int right = a.size() - 1;

        while (left <= right)
        {
            int middle = left + (right - left) / 2;
            if (a[middle]->key == k)
            {
                return middle;
            }
            else if (a[middle]->key < k)
            {
                left = middle + 1;
            }
            else
            {
                right = middle - 1;
            }
        }

        return -left - 1;
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
    bool check_unique(const Tkey &k)
    {
        for (int i = 0; i < size; i++)
        {
            if (a[i]->key == k)
            {
                return false;
            }
        }
        return true;
    }
    orderMap()
    {
        size = 0;
    }
    void insert(const Tkey &k, const Tval &v) override
    {
        int ind = binsearch(k);

        if (ind >= 0)
        {
            // ключ существует - бросаем исключение
            throw("Key already in vector a");
        }

        // ключа нет - вставляем новый
        int insertPos = -ind - 1;
        pair *b = new pair(k, v);
        a.insert(a.begin() + insertPos, b);
        size = a.size();
    }

    orderMap(std::vector<pair *> b)
    {
        size = b.size();
        for (int i = 0; i < b.size(); i++)
        {
            a.insert(b[i]);
        }
    }
    bool search(const Tkey &k) override
    {
        if (binsearch(k) < 0)
        {
            return false;
        }
        return true;
    }
    Tval search_elem(const Tkey &k) override
    {
        int index = binsearch(k);
        if (index < 0)
        {
            throw("cannot find key in order map");
        }
        else
        {
            return a[index]->val;
        }
    }
    void remove(const Tkey &k) override
    {
        if (binsearch(k) < 0)
        {
            throw("cannot find key");
        }
        else
        {
            a.erase(a.begin() + binsearch(k));
            size = size - 1;
        }
    }
    void remove(size_t pos) override
    {
        if (pos > size)
        {
            throw("Index out of range");
        }
        a.erase(a.begin() + pos);
        size = size - 1;
    }
    pair pop(const Tkey &k) override
    {
        if (binsearch(k) < 0)
        {
            throw("cannot find key");
        }
        pair *b = new pair(a[binsearch(k)]->key, a[binsearch(k)]->val);
        a.erase(a.begin() + binsearch(k));
        size = size - 1;
        return *b;
    }

    void print()
    {
        std::cout << "[";
        for (int i = 0; i < size; i++)
        {
            std::cout << "{" << a[i]->key << ": " << a[i]->val << "}";
            if (i < size - 1)
            {
                std::cout << ", ";
            }
        }
        std::cout << "]" << std::endl;
    }
    pair &operator[](const size_t pos)
    {
        return *a[pos];
    }
    ~orderMap()
    {
        for (auto ptr : a)
        {
            delete ptr;
        }
    }
};

#endif