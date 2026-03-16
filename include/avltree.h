#ifndef AVLTREE_H
#define AVLTREE_H
#pragma once
#include "tree.h"
#include <cmath>


template <typename Tkey, typename Tval>
class avltree : public Tree<Tkey, Tval>
{
private: 
    struct avlNode : public Tree<Tkey, Tval>::Node
    {
        int height;
        avlNode(const Tkey &k, const Tval &v, avlNode *l, avlNode *r, avlNode *p, int h = 1) 
            : Tree<Tkey, Tval>::Node(k, v, l, r, p), height(h) {}

        };
  
    avlNode *head;
    void newHeight(avlNode *root){ 
        root->height = 1 + std::max(root->left.height, root->right.height);
    }
    int balance(avlNode *root) {
        return abs(root->right.height - root.left.height); 
    };
    void LLrotate(avlNode *root){
        
    } 
    void LRrotate(avlNode *root){
    }
    void RRrotate(avlNode *root){
    }
    void RLrotate(avlNode *root){ 
    }

public:
    avltree() : Tree<Tkey, Tval>(), head(nullptr) {}
    void remove(size_t pos) override {};
    void remove(const Tkey &k) override {};
    void insert(const Tkey &k, const Tval &v) override {
        tree::insert
    };
    bool search(const Tkey &k) override
    {
        return true; // chtob ne otkisalo pri complire
    };
    Tval search_elem(const Tkey &k) override {};

    void printAvlTree()
    {
        this->printTree(this->head, "HEAD: ");
    }
    void printAvlTreeWithKey()
    {
        this->printTreeWithKey(this->head);
    }
    avlNode *findNodebyPosition(size_t pos)
    {
        return static_cast<avlNode*>(this->findNodeByPos(pos));
    }
    avlNode *findNodebyPosition(avlNode root, size_t pos, size_t target_pos)
    {
        return static_cast<avlNode*>(this->findNodeByPos(root, pos, target_pos));
    }
    avlNode* findNodeByKeyAvl(const Tkey &k)
    {
        return static_cast<avlNode*>(this->findNodeByKey(k));
    }
};

#endif