#ifndef SECOND_LAB_NODE_H
#define SECOND_LAB_NODE_H

#include <memory>

template <typename T>
struct Node {
    T data;
    std::shared_ptr<Node<T>> next;
};

#endif //SECOND_LAB_NODE_H
