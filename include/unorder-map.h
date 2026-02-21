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
        head = new Node(0, 0, nullptr);
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
        return check(k); // если есть - то true
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

    void insert(const Tkey &k, const Tval &v) override
    {
        // Проверка на уникальность
        if (check(k))
        {
            throw std::runtime_error("Key already exists in list");
        }

        // Вставка в начало списка - O(1)
        Node *newNode = new Node(k, v, head); // next указывает на бывший head
        head = newNode;                       // head теперь новый узел
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

    // удаления буду делать по индексу, по ключу,
    virtual void remove(size_t pos) override
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
    virtual void remove(const Tkey &k) override
    {
        if (check(k) == false)
        {
            throw ("cannot find k in list");
        }

        Node *tmp = head;
        Node *prev = nullptr;

        while (tmp != nullptr && tmp->data.key != k)
        {
            prev = tmp;
            tmp = tmp->next;
        }

        if (tmp == nullptr)
        {
            throw("key not found after check");
        }
        if (prev == nullptr)
        {
            head = tmp->next; // новый head - следующий элемент
        }
        else if (tmp->next == nullptr)
        {
            prev->next = nullptr;
        }
        else
        {
            prev->next = tmp->next;
        }

        delete tmp;
        n--;
    }
    virtual pair pop(const Tkey &k) override
    {

        if (check(k) == false)
        {
            throw("cannot find k in list");
        }
        Node *tmp = head;
        Node *prev;
        for (int i = 0; i < n; i++)
        {
            if (tmp->data.key == k)
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
        return tmp->data;
    }
    virtual pair Pop(size_t pos)
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
        return tmp->data;
    }
    bool operator==(const unorderMap &m)
    {
        if (n != m.n)
        {
            return false;
        }
        Node *tmp1 = new Node(head->data.key, head->data.val, head->next);
        Node *tmp2 = new Node(m.head->data.key, m.head->data.val, m.head->next);
        for (int i = 0; i < n; i++)
        {
            if (tmp2.head->data.key != tmp1.head->data.key || tmp2.head->data.val != tmp1.head->data.val)
            {
                return false;
            }
            tmp1 = tmp1->next;
            tmp2 = tmp2->next;
        }
        return true;
    };
    pair &operator[](const size_t pos)
    {
        if (pos >= n)
        {
            throw("index out of range");
        }
        Node *tmp = head;
        for (int i = 0; i < pos; i++)
        {
            tmp = tmp->next;
        }
        return tmp->data;
    }
    void print()
    {
        Node *tmp = head;
        std::cout << "[";
        for (int i = 0; i < n; i++)
        {
            std::cout << "{" << tmp->data.key << ": " << tmp->data.val << "}";
            if (i < n - 1)
            {
                std::cout << ", ";
            }
            tmp = tmp->next;
        }
        std::cout << "]" << std::endl;
    }
};

#endif