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
        avlNode()
            : Tree<Tkey, Tval>::Node(0,0,nullptr,nullptr,nullptr), height(1) {};             
        avlNode(const Tkey &k, const Tval &v, avlNode *l, avlNode *r, avlNode *p, int h = 1) 
            : Tree<Tkey, Tval>::Node(k, v, l, r, p), height(h) {}
        //разве для Node не нужен оператор=? 
    };
  
    avlNode *head;
    void updateHeight(avlNode *root){ 
        root->height = 1 + std::max(root->left.height, root->right.height);
    }
    int balance(avlNode *root) {
        if (root == nullptr){
            return 0; 
        }
        return root->right.height - root.left.height; 
    };
    avlNode* LL(avlNode *root){
        if (root == nullptr || root->left == nullptr){ 
            return root; 
        }
        avlNode* parent = root->parent; 
        avlNode* left_child = root->left; 
        avlNode* left_child_right = left_child->right; 

        left_child->right = root; 
        root->left = left_child_right;
        left_child_right->parent = root; 
        root->parent = left_child; 
    
        left_child->parent = parent; 
        if(parent != nullptr){
        if (parent->right == root){ 
            parent->right = left_child;
        }
        else{
            parent->left = left_child; 
        }}
        updateHeight(root);
        updateHeight(left_child);
        
        return left_child; 
    } 
    avlNode* LR(avlNode *root){
        if (root == nullptr || root->right == nullptr){ 
            return root; 
        } 
        if (root->right->left == nullptr){ 
            return RR(root); 
        }

        avlNode* parent = root->parent; 
        avlNode* left_child = root->left; 
        avlNode* left_child_right = left_child->right; 
        avlNode* lcr_left = left_child_right->left; 
        avlNode* lcr_right = left_child_right->right; 

        left_child_right->left = left_child; 
        left_child->parent = left_child_right; 
        left_child_right->right = root; 
        root->parent = left_child_right; 
        left_child_right->parent = parent; 

        root->left = lcr_right; 
        lcr_right->parent = root; 
        left_child->right = lcr_left;
        lcr_left->parent = left_child; 

        if(parent != nullptr){
        if(parent->left == root){ 
            parent->left = left_child_right; 
        }   

        else{ 
            parent->right = left_child_right; 
        }}

        updateHeight(root);
        updateHeight(left_child); 
        updateHeight(left_child_right);

        return left_child_right; 
    
    }
    avlNode* RR(avlNode *root){
        if (root == nullptr || root->left == nullptr){ 
            return root; 
        }
        avlNode* parent = root->parent; 
        avlNode* right_child = root->right; 
        avlNode* right_child_left = right_child->left; 

        right_child->left = root; 
        root->parent = right_child; 
        root->right = right_child_left; 
        right_child_left->parent = root; 

        right_child->parent = parent; 
        if(parent != nullptr){
        if(parent->left == root){ 
            parent->left = right_child; 
        }
        else{ 
            parent->right = right_child; 
        
        }}
        updateHeight(root); 
        updateHeight(right_child); 

        return right_child; 
    }
    avlNode* RL(avlNode *root){
        if (root == nullptr || root->right == nullptr){ 
            return root; 
        } 
        if (root->right->left == nullptr){ 
            return RR(root); 
        }
        avlNode* right_child = root->right; 
        avlNode* parent = root->parent; 
        avlNode* right_child_left = right_child->left; 
        avlNode* rcl_left = right_child_left->left; 
        avlNode* rcl_right = right_child_left->right; 

        right_child_left->left = root; 
        right_child_left->parent = parent; 
        right_child_left->right = right_child; 
        right_child->parent = right_child_left; 
        root->parent = right_child_left; 
        
        root->right = rcl_left; 
        rcl_left->parent = root; 
        right_child->left = rcl_right; 
        rcl_right->parent = right_child; 

        if(parent != nullptr){
        if(parent->right == root){ 
            parent->right = right_child_left;

        }
        else{ 
            parent->left = right_child_left;  
        }}
        updateHeight(root); 
        updateHeight(right_child); 
        updateHeight(right_child_left); 

        return right_child_left; 
    }
    void Rotate(avlNode *root){ //эту просто будем запускать после вставки рекурсивно, для балансировки(в ней будут лежать LL LR RL RR ) 
    }
public:
    avltree() : Tree<Tkey, Tval>(), head(nullptr) {}; 
    avltree(avlNode *h){
        head = h; 
        head->parent = nullptr; 
    } 
    void remove(size_t pos) override {};
    void remove(const Tkey &k) override {};
    void insert(const Tkey &k, const Tval &v) override {
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
        //upcast - mozhno ne castit' 
        //downcast - libo static_cast libo dynamic_cast 
        //
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