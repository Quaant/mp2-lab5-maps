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
    };

    avlNode *head;

    inline avlNode* to_avl(typename Tree<Tkey, Tval>::Node* node) {
        return static_cast<avlNode*>(node);
    }
    
    void updateHeight(avlNode *root){ 
        if (root == nullptr) return;
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
        if (root == nullptr) return 0;
        int leftH = root->left ? to_avl(root->left)->height : 0;
        int rightH = root->right ? to_avl(root->right)->height : 0;
        return rightH - leftH;
    }
    
    avlNode* LL(avlNode *root){
        if (root == nullptr || root->left == nullptr) return root;
        
        avlNode* parent = to_avl(root->parent);
        avlNode* left_child = to_avl(root->left);
        avlNode* left_child_right = to_avl(left_child->right);

        left_child->right = root;
        root->left = left_child_right;
        
        if (left_child_right) left_child_right->parent = root;
        root->parent = left_child;
        left_child->parent = parent;
        
        if (parent != nullptr) {
            if (parent->left == root) parent->left = left_child;
            else parent->right = left_child;
        }
        
        updateHeight(root);
        updateHeight(left_child);
        
        if (left_child->parent == nullptr) head = left_child;
        
        return left_child;
    }
    
    avlNode* RR(avlNode *root){
        if (root == nullptr || root->right == nullptr) return root;
        
        avlNode* parent = to_avl(root->parent);
        avlNode* right_child = to_avl(root->right);
        avlNode* right_child_left = to_avl(right_child->left);

        right_child->left = root;
        root->right = right_child_left;
        
        if (right_child_left) right_child_left->parent = root;
        root->parent = right_child;
        right_child->parent = parent;
        
        if (parent != nullptr) {
            if (parent->left == root) parent->left = right_child;
            else parent->right = right_child;
        }
        
        updateHeight(root);
        updateHeight(right_child);
        
        if (right_child->parent == nullptr) head = right_child;
        
        return right_child;
    }
    
    avlNode* LR(avlNode *root){
        if (root == nullptr || root->left == nullptr) return root;
        root->left = RR(to_avl(root->left));
        return LL(root);
    }
    
    avlNode* RL(avlNode *root){
        if (root == nullptr || root->right == nullptr) return root;
        root->right = LL(to_avl(root->right));
        return RR(root);
    }
    
    void rebalance(avlNode *node){ 
        if (node == nullptr) return;
        
        avlNode* current = node;
        
        while (current != nullptr) {
            updateHeight(current);
            int bal = balance(current);
            
            if (bal == -2) {
                if (balance(to_avl(current->left)) == 1) {
                    current = LR(current);
                } else {
                    current = LL(current);
                }
            }
            else if (bal == 2) {
                if (balance(to_avl(current->right)) == -1) {
                    current = RL(current);
                } else {
                    current = RR(current);
                }
            }
            else {
                current = to_avl(current->parent);
            }
        }
    }

public:
    avltree() : Tree<Tkey, Tval>(), head(nullptr) {}; 
    
    avltree(avlNode *h) : Tree<Tkey, Tval>(), head(h) {
        if (head) head->parent = nullptr; 
    } 

    void insert(const Tkey &k, const Tval &v) override { 
        if (head == nullptr){ 
            head = new avlNode(k, v, nullptr, nullptr, nullptr, 1); 
            this->n = 1;
            return; 
        }

        avlNode* tmp = head; 
        avlNode* prev = nullptr; 

        while(tmp != nullptr){ 
            prev = tmp; 
            if (k < tmp->data.key){   
                tmp = to_avl(tmp->left);
            }
            else if (k > tmp->data.key){
                tmp = to_avl(tmp->right);
            }
            else{
                throw std::runtime_error("key is not unique");
            }
        }
        
        avlNode *newNode = new avlNode(k, v, nullptr, nullptr, prev, 1);
        this->n++;

        if (k < prev->data.key){
            prev->left = newNode;
        }
        else{
            prev->right = newNode;
        }

        rebalance(newNode);
    }
    
    void remove(const Tkey &k) override {
    if (head == nullptr) {
        throw std::runtime_error("tree is empty");
    }
    
    avlNode* toDelete = head;
    while (toDelete != nullptr && toDelete->data.key != k) {
        if (k < toDelete->data.key) {
            toDelete = to_avl(toDelete->left);
        } else {
            toDelete = to_avl(toDelete->right);
        }
    }
    
    if (toDelete == nullptr) {
        throw std::runtime_error("key not found");
    }
    
    avlNode* parent = to_avl(toDelete->parent);
    avlNode* startRebalance = parent;
    
    // list
    if (toDelete->left == nullptr && toDelete->right == nullptr) {
        if (parent == nullptr) {
            head = nullptr;
        } else if (parent->left == toDelete) {
            parent->left = nullptr;
        } else {
            parent->right = nullptr;
        }
        delete toDelete;
        this->n--;
    }
    //1 child 
    else if (toDelete->left == nullptr) {
        avlNode* child = to_avl(toDelete->right);
        if (parent == nullptr) {
            head = child;
            child->parent = nullptr;
        } else if (parent->left == toDelete) {
            parent->left = child;
            child->parent = parent;
        } else {
            parent->right = child;
            child->parent = parent;
        }
        delete toDelete;
        this->n--;
    }
    else if (toDelete->right == nullptr) {
        avlNode* child = to_avl(toDelete->left);
        if (parent == nullptr) {
            head = child;
            child->parent = nullptr;
        } else if (parent->left == toDelete) {
            parent->left = child;
            child->parent = parent;
        } else {
            parent->right = child;
            child->parent = parent;
        }
        delete toDelete;
        this->n--;
    }
    // 2 child 
    else {
        avlNode* minRight = to_avl(toDelete->right);
        while (minRight->left != nullptr) {
            minRight = to_avl(minRight->left);
        }
        
        Tkey minKey = minRight->data.key;
        Tval minVal = minRight->data.val;
        
        avlNode* minParent = to_avl(minRight->parent);
        startRebalance = minParent;
        
        if (minRight->right == nullptr) {
            if (minParent->left == minRight) {
                minParent->left = nullptr;
            } else {
                minParent->right = nullptr;
            }
        } else {
            // у minRight есть правый ребенок
            avlNode* child = to_avl(minRight->right);
            if (minParent->left == minRight) {
                minParent->left = child;
                child->parent = minParent;
            } else {
                minParent->right = child;
                child->parent = minParent;
            }
        }
        delete minRight;
        this->n--;
        
        Tkey tempKey = toDelete->data.key;
        Tval tempVal = toDelete->data.val;
        
        toDelete->data.key = minKey;
        toDelete->data.val = minVal;
        
        if (startRebalance != nullptr) {
            rebalance(startRebalance);
        }
        return;
    }
    
    if (startRebalance != nullptr) {
        rebalance(startRebalance);
    }
}

    bool search(const Tkey &k) override {
        return findNodeByKeyAvl(k) != nullptr;
    }

    Tval search_elem(const Tkey &k) override {
        avlNode* node = findNodeByKeyAvl(k);
        if (node == nullptr) {
            throw std::runtime_error("cant find ur elem");
        }
        return node->data.val;
    }

    void printAvlTree() {
        this->printTree(this->head, "HEAD: ");
    }
    
    void printAvlTreeWithKey() {
        this->printTreeWithKey(this->head);
    }

    avlNode* findNodeByPosition(size_t pos) {
        return static_cast<avlNode*>(this->findNodeByPos(pos));
    }
    
    avlNode* findNodeByKeyAvl(const Tkey &k) {
        avlNode* tmp = head;
    while (tmp != nullptr) {
        if (tmp->data.key == k) return tmp;
        else if (k < tmp->data.key) tmp = to_avl(tmp->left);
        else tmp = to_avl(tmp->right);
    }
    return nullptr;
    }
    
    size_t size() const {
        return this->n;
    }
    void clear() {
    this->deleteSubTree(this->head);
    head = nullptr;
    this->n = 0;
}
};

#endif