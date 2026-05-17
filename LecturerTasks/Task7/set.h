#pragma once

#include "set_impl.h"
#include "array_impl.h"
#include "tree_impl.h"

#include <iostream>
#include <typeinfo>

template <class T>
class Set {

    static constexpr const size_t CRITICAL_SIZE = 10;

    std::unique_ptr<SetImpl<T>> pimpl;
    bool is_tree;

public:

    Set() {
        pimpl = std::make_unique<ArrayImpl<T>>();
        is_tree = false;
    }

    Set(const std::vector<T>& v) {
        pimpl = std::make_unique<ArrayImpl<T>>();
        for (auto elem : v) {
            Add(elem);
        }
    }

    Set(const Set& rhs) {
        pimpl = std::make_unique<ArrayImpl<T>>();
        auto elems = rhs.pimpl->GetElements();
        for (auto e : elems) {
            Add(e);
        }
    }

    Set& operator=(const Set& rhs) {
        if (this != &rhs) {
            Set tmp(rhs);
            std::swap(pimpl, tmp.pimpl);
            std::swap(is_tree, tmp.is_tree);
        }
        return *this;
    }

    Set(Set&& rhs) = default;
    Set& operator=(Set&& rhs) = default;

    void Add(T elem) {
        if (pimpl->Size() == CRITICAL_SIZE && !is_tree) {
            std::cout << "\nLet's become a TreeImpl! Now pimpl type is " << typeid(*pimpl).name() << std::endl;
            is_tree = true;
            std::vector<T> elems = pimpl->GetElements();
            pimpl = std::make_unique<TreeImpl<T>>();
            for (auto e : elems) {
                pimpl->Add(e);
            }
            std::cout << "\nAnd after transformation pimpl type is " << typeid(*pimpl).name() << "\n" << std::endl;
        }
        pimpl->Add(elem);
    }

    void Remove(T elem) {
        pimpl->Remove(elem);
    }

    bool Contains(T elem) {
        return pimpl->Contains(elem);
    }

    Set Union(const Set& rhs) {
        Set set;
        auto elems1 = pimpl->GetElements();
        auto elems2 = rhs.pimpl->GetElements();
        for (auto e : elems1)
            set.Add(e);
        for (auto e : elems2)
            set.Add(e);

        return set;
    }

    Set Intersection(const Set& rhs) {
        Set set;
        auto elems2 = rhs.pimpl->GetElements();
        for (auto e : elems2) {
            if (Contains(e))
                set.Add(e);
        }

        return set;
    }
};
