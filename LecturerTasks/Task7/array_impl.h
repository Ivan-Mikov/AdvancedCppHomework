#pragma once

#include "set_impl.h"

#include <vector>
#include <algorithm>

template <class T>
class ArrayImpl : public SetImpl<T> {
    std::vector<T> elems;
public:

    ArrayImpl() {
        elems = {};
    }

    bool Contains(T elem) const override {
        return (std::find(elems.begin(), elems.end(), elem) != elems.end());
    }

    void Add(T elem) override {
        if (!Contains(elem))
            elems.push_back(elem);
    }

    void Remove(T elem) override {
        auto iter = std::find(elems.begin(), elems.end(), elem);
        if (iter != elems.end()) elems.erase(iter);
    }

    std::vector<T> GetElements() const override {
        return elems;
    }

    size_t Size() const override {
        return elems.size();
    }
};