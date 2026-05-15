#pragma once

#include "set_impl.h"

#include <vector>
#include <memory>

template <class T>
class TreeImpl : public SetImpl<T> {

    struct Node {
        T value;
        Node* left;
        Node* right;

        Node(T val) : value(val) {
            left = nullptr;
            right = nullptr;
        }
    };

    Node* root;
    size_t size;

    void add(Node*& node, T value) {
        if (!node) {
            node = new Node(value);
            return;
        }

        if (value == node->value) 
            return;

        if (value < node->value)
            add(node->left, value);
        else
            add(node->right, value);
    }

    void remove(Node*& node, T value) {
        if (node == nullptr) return;
        if (value < node->value) remove(node->left, value);
        else if (value > node->value) remove(node->right, value);
        else {
            if (!node->left && !node->right) {
                delete node;
                node = nullptr;
                return;
            } else if (!node->left && node->right) {
                auto right = node->right; 
                delete node;
                node = right;
                return;
            } else if (node->left && !node->right) {
                auto left = node->left;
                delete node;
                node = left;
                return;
            } else {
                auto curr = node->left;
                while(curr->right) {
                    curr = curr->right;
                }

                node->value = curr->value;
                remove(node->left, curr->value);
            }
        }
    }

    bool contains(Node* node, T value) const {
        if (!node) return false;
        if (node->value == value) return true;
        else if (value < node->value)
            return contains(node->left, value);
        else
            return contains(node->right, value);
    }

    void push(Node* node, std::vector<T>& v) const {
        if (!node) return;
        v.push_back(node->value);
        push(node->left, v);
        push(node->right, v);
    }

    void clear(Node* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

public:
    TreeImpl() {
        root = nullptr;
        size = 0;
    }

    ~TreeImpl() override {
        clear(root);
    }

    void Add(T elem) override {
        if (!Contains(elem)) {
            add(root, elem);
            size++;
        }
    }

    void Remove(T elem) override {
        if (Contains(elem)) {
            remove(root, elem);
            size--;
        }
    }

    bool Contains(T elem) const override {
        return contains(root, elem);
    }

    std::vector<T> GetElements() const override {
        std::vector<T> elems;
        push(root, elems);
        return elems;
    }

    size_t Size() const override {
        return size;
    }

};