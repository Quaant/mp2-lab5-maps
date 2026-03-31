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

    inline avlNode* to_avl(typename Tree<Tkey, Tval>::Node* node) {
    return static_cast<avlNode*>(node);
}
    
    avlNode* LL(avlNode *root){
        if (root == nullptr || root->left == nullptr){ 
            return root; 
        }
        avlNode* parent = to_avl(root->parent); 
        avlNode* left_child = to_avl(root->left); 
        avlNode* left_child_right = to_avl(left_child->right); 

        
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
        if (to_avl(root->right->left) == nullptr){ 
            return RR(root); 
        }

        avlNode* parent = to_avl(root->parent); 
        avlNode* left_child = to_avl(root->left); 
        avlNode* left_child_right = to_avl(left_child->right); 
        avlNode* lcr_left = to_avl(left_child_right->left); 
        avlNode* lcr_right = to_avl(left_child_right->right); 

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
        // if (root == nullptr || root->left == nullptr){ 
        //     return root; 
        // }
        // avlNode* parent = root->parent; 
        // avlNode* right_child = root->right; 
        // avlNode* right_child_left = right_child->left; 

        // right_child->left = root; 
        // root->parent = right_child; 
        // root->right = right_child_left; 
        // right_child_left->parent = root; 

        // right_child->parent = parent; 
        // if(parent != nullptr){
        // if(parent->left == root){ 
        //     parent->left = right_child; 
        // }
        // else{ 
        //     parent->right = right_child; 
        
        // }}
        // updateHeight(root); 
        // updateHeight(right_child); 

        // return right_child; 
    }
    avlNode* RL(avlNode *root){
        // if (root == nullptr || root->right == nullptr){ 
        //     return root; 
        // } 
        // if (root->right->left == nullptr){ 
        //     return RR(root); 
        // }
        // avlNode* right_child = root->right; 
        // avlNode* parent = root->parent; 
        // avlNode* right_child_left = right_child->left; 
        // avlNode* rcl_left = right_child_left->left; 
        // avlNode* rcl_right = right_child_left->right; 

        // right_child_left->left = root; 
        // right_child_left->parent = parent; 
        // right_child_left->right = right_child; 
        // right_child->parent = right_child_left; 
        // root->parent = right_child_left; 
        
        // root->right = rcl_left; 
        // rcl_left->parent = root; 
        // right_child->left = rcl_right; 
        // rcl_right->parent = right_child; 

        // if(parent != nullptr){
        // if(parent->right == root){ 
        //     parent->right = right_child_left;

        // }
        // else{ 
        //     parent->left = right_child_left;  
        // }}
        // updateHeight(root); 
        // updateHeight(right_child); 
        // updateHeight(right_child_left); 

        // return right_child_left; 
    }
    void updateHeight(avlNode *root){ 
        int a = 0, b = 0; 
        if (root->left != nullptr){ 
            a = to_avl(root->left)->height; 
        }
        if (root->right != nullptr){
            b = to_avl(root->right)->height; 
        }
        root->height = 1 + std::max(a, b);
    }
    int balance(avlNode *root) {
        if (root == nullptr){    
            return 0; 
        }

        
        //УМИРАЕМ ЗДЕСЬ!!!!
        if (root->right != nullptr && root->left != nullptr){ 
        return to_avl(root->right)->height - to_avl(root->left)->height;} 
        else if (root->right == nullptr && root->left != nullptr){ 
            return -to_avl(root->left)->height; 
        } 
        else if (root->left == nullptr && root->right != nullptr){ 
            return to_avl(root->right)->height; 
        }
        else{ 
            return 0; 
        }
    };
    void rebalance(avlNode *root){ 
        if (root == nullptr) {
            return;}
        avlNode* bal = root; 

        while (bal != nullptr){ 

            int balik = balance(bal);
            std::cout << bal->data.key << ':' << balik << "\n";

        if (balik == -2){ 
            if (balance(static_cast<avlNode*>(bal->left)) == 1){ 
                //LR 
                bal = LR(bal); 
                bal = static_cast<avlNode*>(bal->parent); 
            }
            else if (balance(static_cast<avlNode*>(bal->left)) == -1){ 
                //LL
                bal = LL(bal);
                bal = static_cast<avlNode*>(bal->parent); 
            }
        }
        else if (balik == 2){ 
            if(balance(static_cast<avlNode*>(bal->right)) == 1){ 
                // RR
                bal = RR(bal); 
                bal = static_cast<avlNode*>(bal->parent); 
            } 
            else if (balance(static_cast<avlNode*>(bal->right)) == -1){ 
                // RL
                bal = RL(bal);
                bal = static_cast<avlNode*>(bal->parent); 
            }
        }
        else{
            updateHeight(bal); 
            bal = static_cast<avlNode*>(bal->parent); 
        }
    }}
public:
    avltree() : Tree<Tkey, Tval>(), head(nullptr) {}; 
    avltree(avlNode *h){
        head = h; 
        head->parent = nullptr; 
    } 

    void _insert(const Tkey&k, const Tval&v){ 
         if (head == nullptr){ 
            head = new avlNode(k, v, nullptr, nullptr, nullptr, 1); 
            return; 
        }

        avlNode* tmp = head; 
        avlNode* prev = nullptr; 

        while(tmp != nullptr){ 
            prev = tmp; 
            if (k < tmp->data.key)
        {
            
            tmp = static_cast<avlNode*>(tmp->left);
        }
        else if (k > tmp->data.key)
        {
            tmp = static_cast<avlNode*>(tmp->right);
        }
        else
        {
            throw std::runtime_error("key is not unique");
        }
        }
        avlNode *newNode = new avlNode(k, v, nullptr, nullptr, prev, 1);

    if (k < prev->data.key)
    {
        prev->left = newNode;

    }
    else
    {
        prev->right = newNode;
    }

    rebalance(newNode); 
    }

    void insert(const Tkey &k, const Tval &v) override 
    { 
        _insert(k, v);
    }
    void remove(size_t pos) override {};
    void remove(const Tkey &k) override {};


    //~~~SEARCH~~~ 
    bool search(const Tkey &k) override
    {
        return true; // chtob ne otkisalo pri complire
    };
    Tval search_elem(const Tkey &k) override {};


    //~~~~PRINT~~~~
    void printAvlTree()
    {
        this->printTree(this->head, "HEAD: ");
    }
    void printAvlTreeWithKey()
    {
        this->printTreeWithKey(this->head);
    }


    //~~OTHER~~~
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