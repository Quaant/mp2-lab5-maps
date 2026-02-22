#ifndef TREE_H
#define TREE_H
#pragma once
#include <iostream>
#include "map.h"

template <typename Tkey, typename Tval>
class Tree : public Tmap<Tkey, Tval>
{
protected:
    using pair = typename TMap<Tkey, Tval>::pair;
    struct Node
    {
        pair data;
        Node *left;
        Node *right;
        Node *parent;
        Node(const Tkey &k, const Tval &v, Node *l, Node *r, Node *p) : (data.key = k), (data.val = v), (left = l), (right = r), (parent = p) {};
        Node(const pair a, Node *l, Node *r, Node *p) : (data = a), (left = l), (right = r), (parent = p) {};
    };
    Node *head;
    size_t n;

public:
    Node *GetHead() return *head;
    Tree()
    {
        head = nullptr;
        n = 0;
    }
    Tree(Node *h, size_t size)
    {
        head = h;
        n = size;
    }
    void deleteSubTree(Node *t)
    {
        if (t == nullptr)
        {
            return;
        }
        deleteSubTree(t->left);
        deleteSubTree(t->right);
        delete t;
    }
    ~Tree()
    {
        deleteSubTree(head);
    }

    virtual bool search(const Tkey &k) override // eto prosto proverka na nalichie
    {
        Node *tmp = head;
        while (tmp != nullptr || tmp->data.key == k)
        {
            if (tmp->data.key > k)
            {
                tmp = tmp->left;
            }
            else if (tmp->data.key < k)
            {
                tmp = tmp->right;
            }
        }
        if (tmp == nullptr)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    virtual Tval search_elem(const Tkey &k)
    {
        if (search(k) == false)
        {
            throw("cant find ur elem");
        }
        Node *tmp = head;

        while (tmp != nullptr)
        {
            if (tmp->data.key == k)
            {
                return tmp->data.val;
            }
            else if (tmp->data.key > k)
            {
                tmp = tmp->left;
            }
            else
            {
                tmp = tmp->right;
            }
        }
        throw("cant find ur elem");
    }

    virtual void insert(const Tkey &k, const Tval &v) override
    {
        if (n == 0)
        {
            head = new Node(k, v, nullptr, nullptr, nullptr);
            n++;
            return;
        }
        Node *tmp = head;
        while (tmp != nullptr)
        {
            prev = tmp;
            if (tmp->data.key > k)
            {
                tmp = tmp->left;
            }
            else if (tmp->data.key < k)
            {
                tmp = tmp->right;
            }
            else
            {
                throw("ur key is not unique");
            }
        }
        Node *res = new Node(k, v, nullptr, nullptr, tmp->parent);
        if (res->data.key > tmp->parent->data.key)
        {
            tmp->parent->right = res;
        }
        else
        {
            tmp->parent->left = res;
        }
        n++;
    }
    virtual remove(const Tkey &k) override
    {
        if (n <= 0)
        {
            throw("u can delete tree")
        }
        Node *tmp = head;
        while (tmp != nullptr && tmp->data.key == k)
        {
            if (tmp->data.key > k)
            {
                tmp = tmp->left;
            }
            else if (tmp->data.key < k)
            {
                tmp = tmp->right;
            }
        }
        if (tmp == nullptr)
        {
            throw("cannot find ur key in tree");
        }
        // listok
        if (tmp->right == nullptr && tmp->left == nullptr)
        {
            if (tmp->parent->right->data.key == tmp->data.key)
            {
                tmp->parent->right = nullptr;
            }
            else
            {
                tmp->parent->left = nullptr;
            }
            delete tmp;
        }
        // 1 naslednik
        else if (tmp->left == nullptr || tmp->right == nullptr)
        {
            if (tmp->left == nullptr)
            {
                if (tmp->parent->right->data.key == tmp->data.key)
                {
                    tmp->parent->right = tmp->right;
                }
                else
                {
                    tmp->parent->left = tmp->right;
                }
            }
            else
            {
                if (tmp->parent->right->data.key == tmp->data.key)
                {
                    tmp->parent->right = tmp->left;
                }
                else
                {
                    tmp->parent->left = tmp->left;
                }
            }
            delete tmp;
        }
        // 2 naslednika
        else
        {
            Node *it = tmp->right;
            while (it != nullptr)
            {
                it = it->left;
            }
            if (tmp->parent->right->data.key == tmp->data.key)
            {
                tmp->parent->right = it->parent;
            }
            else
            {
                tmp->parent->left = it->parent;
            }
            it->parent->left = nullptr;
            delete tmp;
        }
    }
    virtual remove(size_t pos) override
    {
    }

    // вывод дерева позаимствовал у рослова и кармаева(они разрешили)
    void printTreeWithKey(Node *root, std::string indent = "", bool isLeft = true)
    {
        if (root == nullptr)
            return;
        if (root->right)
        {
            printTreeWithKey(root->right, indent + (isLeft ? "│   " : "    "), false);
        }
        cout << indent << (isLeft ? "└── " : "┌── ") << root->data.key << ',' << root->data.value << endl;
        if (root->left)
        {
            printTreeWithKey(root->left, indent + (isLeft ? "    " : "│   "), true);
        }
    }
    void printTree(Node *root, std::string indent = "", bool isLeft = true)
    {
        if (root == nullptr)
            return;
        if (root->right)
        {
            printTree(root->right, indent + (isLeft ? "│   " : "    "), false);
        }
        cout << indent << (isLeft ? "└── " : "┌── ") << root->data.key << endl;
        if (root->left)
        {
            printTree(root->left, indent + (isLeft ? "    " : "│   "), true);
        }
    }
};

#endif