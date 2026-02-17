#ifndef UNORDER_MAP_H
#define UNORDER_MAP_H
#pragma once
#include "map.h"

template <typename Tkey, typename Tval>
class unorderMap : public TMap<Tkey, Tval>
{
    using pair = typename TMap<Tkey, Tval>::pair;
    struct Node
    {
        pair data;
        Node *next;
        Node(const Tkey &k, const Tval &v, Node *n) : data(k, v), next(n) {}
        Node(const Tkey &k, const Tval &v) : data(k, v), next(nullptr) {}
    };

    Node *head;
    size_t n;

    bool check(const Tkey &k)
    { // проверка на уникальность ключа
        Node *tmp = head;
        for (int i = 0; i < n; i++)
        {
            if (tmp->data.key == k)
            {
                return true;
            }
            tmp = tmp->next;
        }
        return false;
    }

public:
    Node GetHead()
    {
        return head;
    }

    unorderMap()
    {
        head->data.key = 0;
        head->data.val = 0;
        head->next = nullptr;
        n = 0;
    }
    unorderMap(std::vector<Node *> a)
    { // тут хз, предпологаем что внутри вектора a,ноды выстроенны в нужно порядке
      // P.S перечитал верхний комментарий, хз о чем я
        head = a[0];
        n = size(a);
    }
    virtual bool search(const Tkey &k) override
    {
        return check(k);
    }
    virtual Tval search_elem(const Tkey &k) override
    {
        Node *tmp = head;
        for (int i = 0; i < n; i++)
        {
            if (tmp->data.key == k)
            {
                return tmp->data.val;
            }
        }
        throw("cannot find key");
    }
    // Вместо простого  INSERT я хочу добавибь push_front and push_back

    void push_front(const Tkey &k, const Tval &v)
    {
        if (check(k) == true)
        {
            throw("u have already k in list");
        }
        Node *b = new Node(head->data.key, head->data.val, head->next);
        head = new Node(b->data.key, b->data.val, b->next);
        n++;
    }
    void push_after(size_t pos, const Tkey &k, const Tval &v)
    {
        if (check(k) == true)
        {
            throw("u have already k in list");
        }
        Node *tmp = head;
        Node *b = new Node(k, v, nullptr);
        for (int i = 0; i < pos && tmp != nullptr; i++)
        {
            tmp = tmp->next;
        }
        if (tmp == nullptr)
        {
            throw("Index out of range");
        }
        Node *c = tmp->next;
        tmp->next = b;
        b->next = c;
        n++;
    }
    Tval &operator[](size_t pos)
    {
        Node *tmp = head;
        for (int i = 0; i < pos && tmp != nullptr; i++)
        {
            tmp = tmp->next;
        }
        if (tmp == nullptr)
        {
            throw("Index out of range");
        }
        return tmp->data.val;
    }
    // удаления буду делать по индексу, по ключу,
    virtual void Remove(size_t pos) override
    {
        if (pos > n)
        {
            throw("Index out of range");
        }
        Node *tmp = head;
        Node *prev;
        for (int i = 0; i < pos && tmp != nullptr; i++) // тут ошибка может быть из-за индекса(поставить pos - 1)
        {
            prev = tmp;
            tmp = tmp->next;
        }
        if (tmp == nullptr)
        {
            throw("Index out of range");
        }
        if (tmp->next != nullptr)
            prev->next = tmp->next;
        else
        {
            prev->next = nullptr;
        }
        delete tmp;
    }
    virtual void Remove(const Tkey &k) override
    {
        if (check(k) == false)
        {
            throw("cannot find k in list");
        }
        Node *tmp = head;
        Node *prev;
        for (int i = 0; i < n; i++)
        {
            if (tmp->key == k)
            {
                break;
            }
            prev = tmp;
            tmp = tmp->next;
        }

        if (tmp->next != nullptr)
            prev->next = tmp->next;
        else
        {
            prev->next = nullptr;
        }
        delete tmp;
    }
    virtual Node Pop(const Tkey &k) override
    {

        if (check(k) == false)
        {
            throw("cannot find k in list");
        }
        Node *tmp = head;
        Node *prev;
        for (int i = 0; i < n; i++)
        {
            if (tmp->key == k)
            {
                break;
            }
            prev = tmp;
            tmp = tmp->next;
        }

        if (tmp->next != nullptr)
            prev->next = tmp->next;
        else
        {
            prev->next = nullptr;
        }
        return tmp;
    }
    virtual Node Pop(size_t pos) override
    {
        if (pos > n)
        {
            throw("Index out of range");
        }
        Node *tmp = head;
        Node *prev;
        for (int i = 0; i < pos && tmp != nullptr; i++) // тут ошибка может быть из-за индекса(поставить pos - 1)
        {
            prev = tmp;
            tmp = tmp->next;
        }
        if (tmp == nullptr)
        {
            throw("Index out of range");
        }
        if (tmp->next != nullptr)
            prev->next = tmp->next;
        else
        {
            prev->next = nullptr;
        }
        return tmp;
    }
};

#endif 