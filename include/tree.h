#ifndef TREE_H
#define TREE_H
#pragma once
#include <iostream>
#include "map.h"

template <typename Tkey, typename Tval>
class Tree : public TMap<Tkey, Tval>
{

protected:
    using pair = typename TMap<Tkey, Tval>::pair;
    struct Node
    {
        pair data;
        Node *left;
        Node *right;
        Node *parent;
        Node(const Tkey &k, const Tval &v, Node *l, Node *r, Node *p)
            : data(k, v), left(l), right(r), parent(p) {}
        Node(const pair &a, Node *l, Node *r, Node *p) : data(a), left(l), right(r), parent(p) {}
        virtual ~Node() = default; 
    };
    size_t n;


private:
    Node *head;
public:
    Node *GetHead() { return head; }
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

    virtual bool search(const Tkey &k) override
    {
        return findNodeByKey(k) != nullptr;
    }
    virtual Tval search_elem(const Tkey &k)
    {
        if (head == nullptr)
        {
            throw("tree is empty");
        }

        Node *node = findNodeByKey(k);
        if (node == nullptr)
        {
            throw("cant find ur elem");
        }
        return node->data.val;
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
        Node *prev = nullptr;

        while (tmp != nullptr)
        {
            prev = tmp;
            if (k < tmp->data.key)
            {
                tmp = tmp->left;
            }
            else if (k > tmp->data.key)
            {
                tmp = tmp->right;
            }
            else
            {
                throw std::runtime_error("key is not unique");
            }
        }

        Node *newNode = new Node(k, v, nullptr, nullptr, prev);

        if (k < prev->data.key)
        {
            prev->left = newNode;
        }
        else
        {
            prev->right = newNode;
        }
        n++;
    }
    virtual void remove(const Tkey &k) override
    {
        if (n <= 0)
        {
            throw("u can delete tree");
        }

        Node *tmp = head;
        Node *parent = nullptr;

        while (tmp != nullptr && tmp->data.key != k)
        {
            parent = tmp;
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

            if (tmp->parent == nullptr) // удаляем корень
            {
                head = nullptr;
            }
            else if (tmp->parent->right == tmp)
            {
                tmp->parent->right = nullptr;
            }
            else
            {
                tmp->parent->left = nullptr;
            }
            delete tmp;
            n--;
            return;
        }
        // 1 naslednik
        else if (tmp->left == nullptr || tmp->right == nullptr)
        {
            Node *child = (tmp->left != nullptr) ? tmp->left : tmp->right; // определяем потомка

            if (tmp->parent == nullptr)
            {
                head = child;
                child->parent = nullptr;
            }
            else if (tmp->parent->right == tmp)
            {
                tmp->parent->right = child;
                child->parent = tmp->parent;
            }
            else
            {
                tmp->parent->left = child;
                child->parent = tmp->parent;
            }
            delete tmp;
            n--;
            return;
        }
        // 2 naslednika
        else
        {
            Node *it = tmp->right;
            while (it->left != nullptr) // идем пока есть левый
            {
                it = it->left;
            }

            Tkey minKey = it->data.key;
            Tval minVal = it->data.val;

            if (it->parent->left == it)
            {
                it->parent->left = it->right;
            }
            else
            {
                it->parent->right = it->right;
            }
            if (it->right != nullptr)
            {
                it->right->parent = it->parent;
            }

            tmp->data.key = minKey;
            tmp->data.val = minVal;

            delete it;
            n--;
        }
    }
    // iterator от сюда можно будет взять
    virtual void remove(size_t pos) override
    {
        if (pos >= n)
        {
            throw("index out of range0");
        }
        Node *tmp = findNodeByPos(pos);
        Tkey to_delete = tmp->data.key;
        remove(to_delete);
    }
    Node *findNodeByPos(Node *root, size_t pos, size_t target_pos)
    {
        if (root == nullptr)
        {
            return nullptr;
        }
        Node *leftRes = findNodeByPos(root->left, pos, target_pos);
        if (leftRes != nullptr)
        {
            return leftRes;
        }
        if (pos == target_pos)
        {
            return root;
        }
        pos++;
        return findNodeByPos(root->right, pos, target_pos);
    }
    Node *findNodeByPos(size_t target_pos)
    {
        size_t pos = 0;
        return findNodeByPos(head, pos, target_pos);
    }
    Node *findNodeByKey(const Tkey &k)
    {
        if (head == nullptr)
        {
            return nullptr;
        }

        Node *tmp = head;
        while (tmp != nullptr)
        {
            if (tmp->data.key == k)
            {
                return tmp;
            }
            else if (k < tmp->data.key)
            {
                tmp = tmp->left;
            }
            else
            {
                tmp = tmp->right;
            }
        }
        return nullptr;
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
        std::cout << indent << (isLeft ? "└── " : "┌── ") << root->data.key << ',' << root->data.val << std::endl;
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
        std::cout << indent << (isLeft ? "└── " : "┌── ") << root->data.key << std::endl;
        if (root->left)
        {
            printTree(root->left, indent + (isLeft ? "    " : "│   "), true);
        }
    }
    virtual pair pop(const Tkey &k) override
    {
        Node *node = findNodeByKey(k);
        if (node == nullptr)
        {
            throw("Key not found");
        }

        pair result = node->data;
        remove(k);
        return result;
    }

    
};

#endif