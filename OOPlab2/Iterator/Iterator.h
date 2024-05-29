#ifndef SECOND_LAB_ITERATOR_H
#define SECOND_LAB_ITERATOR_H

#include <iostream>
#include <memory>
#include "../Node/Node.h"

template <typename T>
class List;

template <typename T>
class Iterator {
    friend class List<T>;
public:
    explicit Iterator<T>(List<T> lst): first(lst.first), count(lst.count), index(0) {}

    Iterator(const Iterator &it) = default;

    Iterator<T> start() {
        return Iterator(first, count);
    }

    Iterator<T> next() {
        ++index;
        return *this;
    }

    T value() {
        return getNode()->data;
    }

    bool isEnd() {
        if (index >= *count) {
            return true;
        } else {
            return false;
        }
    }

    Iterator<T> &operator++() {
        ++index;
        return *this;
    }

    T &operator*() {
        return getNode()->data;
    }

    bool operator==(const Iterator<T> &equal) const {
        return index == equal.index;
    }

    bool operator!=(const Iterator<T> &notEqual) const {
        return index != notEqual.index;
    }

private:
    std::shared_ptr<Node<T>> first;
    std::shared_ptr<size_t> count;
    size_t index = 0;

    Iterator(const std::shared_ptr<Node<T>> &f, const std::shared_ptr<size_t> &c, size_t ind = 0) : first(f), count(c), index(ind) {}

    std::shared_ptr<Node<T>> getNode() const {
        if (index >= *count) return nullptr;
        auto current = first;
        for (size_t i = 0; i < index; ++i)
            current = current->next;
        return current;
    }
};

#endif //SECOND_LAB_ITERATOR_H