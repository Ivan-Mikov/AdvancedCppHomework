#pragma once

#include <vector>
#include <memory>

template <class T>
class SetImpl {
public:
    virtual ~SetImpl() = default;

    virtual void Add(T elem) = 0;
    virtual void Remove(T elem) = 0;
    virtual bool Contains(T elem) const = 0;
    virtual size_t Size() const = 0;
    virtual std::vector<T> GetElements() const = 0;
};