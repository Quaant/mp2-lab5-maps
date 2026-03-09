#ifndef AVLTREE_H
#define AVLTREE_H
#include "tree.h"

template <typename Tkey, typename Tval>
class avltree : public Tree<Tkey, Tval>
{
    struct avlNode : public Tree<Tkey, Tval>::Node
    {
        char balance;
        avlNode(const Tkey &k, const Tval &v, Node *l, Node *r, Node *p) : Tree<Tkey, Tval>::Node(k, v, l, r, p), balalce(0) {};
        avlNode(const pair &a, Node *l, Node *r, Node *p)
        {
            : Tree<Tkey, Tval>::Node(a, l , r, p), balace(0);
        }
    };
    avlNode *head;

public:
    void check_balance() {};

    void remove(size_t pos) override {};
    void remove(const Tkey &k) override {};
    void insert(const Tkey &k, const Tval &v) override {};
    bool search(const Tkey &k) override {};
    Tval search_elem(const Tkey &k) override {};

    void printAvlTree()
    {
        this->template printTree<avlNode>(head, "HEAD: ");
    }
    void printAvlTreeWithKey()
    {
        this->template printTreeWithKey<avlNode>(head);
    }
    avlNode *findNodebyPosition(size_t pos)
    {
        return this->template findNodeByPos<avlNode>(pos);
    }
    avlNode *findNodebyPosition(avlNode root, size_t pos, size_t target_pos)
    {
        return this->template findNodeByPos<avlNode>(root, pos, target_pos);
    }
    avlNode findNodeByKeyavl(const Tkey &k)
    {
        return this->template findNodeByKey<avlNode>(k);
    }
};

#endif