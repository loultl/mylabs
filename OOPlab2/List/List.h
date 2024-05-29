#ifndef SECOND_LAB_LIST_H
#define SECOND_LAB_LIST_H

#include <iostream>
#include <vector>
#include "../Node/Node.h"
#include "../Iterator/Iterator.h"
#include "../Errors/Errors.h"

template <typename T>
class List {
    friend class Iterator<T>;
public:
    List();
    List(const List<T>& lst);
    List(List<T>&& lst) noexcept ;
    List(std::initializer_list<T> lst);
    ~List();
    size_t getLength() const;
    void add(const T& elem);
    void addRange(const List<T>& lst);
    void addRange(T* arr, int size);
    void setElem(int index, const T& elem);
    T& getElem(int index);
    void removeElem(int index);
    List<T> combine(const List<T>& lst);
    void sort(int (*comp)(const T& r1, const T& r2));
    int getIndex(T &elem) const;
    T* toArray();
    static int compare(const T& a, const T& b);
    T& operator[](int index);
    List<T>& operator =(const List<T>& lst);
    Iterator<T> begin() const noexcept { return Iterator<T>(first, count); }
    Iterator<T> end() const noexcept { return Iterator<T>(first, count, *count); }
private:
    std::shared_ptr<Node<T>> first;
    std::shared_ptr<size_t> count;
};



template <typename T>
List<T>::List() : first(nullptr), count(std::make_shared<size_t>(0)) {}

template <typename T>
List<T>::List(const List<T>& lst) : first(nullptr), count(std::make_shared<size_t>(0)) {
    std::shared_ptr<Node<T>> current = lst.first;
    while (current != nullptr) {
        add(current->data);
        current = current->next;
    }
}

template <typename T>
List<T>::List(List<T>&& lst) noexcept : first(std::move(lst.first)), count(std::move(lst.count)) {
    lst.first = nullptr;
    lst.count = nullptr;
}

template <typename T>
List<T>::List(std::initializer_list<T> lst) : first(nullptr), count(std::make_shared<size_t>(0)) {
    for (const T& element : lst) {
        add(element);
    }
}

template <typename T>
List<T>::~List() = default;

template <typename T>
List<T>& List<T>::operator=(const List<T>& lst) {
    if (this == &lst)
        return *this;
    first = nullptr;
    count = std::make_shared<size_t>(lst.getLength());
    Iterator<T> it(lst);
    for (it.start(); !it.isEnd(); it.next()) {
        add(it.value());
    }
    return *this;
}

template <typename T>
size_t List<T>::getLength() const {
    return *count;
}

template <typename T>
void List<T>::add(const T& elem) {
    auto node = std::make_shared<Node<T>>();
    node->data = elem;
    node->next = nullptr;
    if (first == nullptr) {
        first = node;
    } else {
        auto temp = first;
        while (temp->next != nullptr)
            temp = temp->next;
        temp->next = node;
    }
    (*count)++;
}

template <typename T>
void List<T>::addRange(const List<T>& lst) {
    Iterator<T> it(lst);
    for (it.start(); !it.isEnd(); it.next())
        add(it.value());
}

template <typename T>
void List<T>::addRange(T* arr, int size) {
    if (size < 0) {
        throw InvalidSizeError(INVALID_SIZE_ERROR);
    }
    for(int i = 0;i < size; i++) {
        add(arr[i]);
    }
}

template <typename T>
void List<T>::setElem(int index, const T& elem) {
    auto p = first;
    if (p == nullptr)
        throw EmptyListError(EMPTY_LIST_ERROR);
    if (getLength() < index || index < 0) {
        throw IndexError(INDEX_ERROR);
    }
    for (int i = 0;i < index;i++) {
        p = p->next;
    }
    p->data = elem;
}

template <typename T>
T& List<T>::getElem(int index) {
    auto p = first;
    if (p == nullptr)
        throw EmptyListError(EMPTY_LIST_ERROR);
    if (getLength() < index || index < 0) {
        throw IndexError(INDEX_ERROR);
    }
    for (int i = 0;i < index;i++) {
        p = p->next;
    }
    return p->data;
}

template <typename T>
void List<T>::removeElem(int index) {
    auto p = first;
    if (p == nullptr)
        throw EmptyListError(EMPTY_LIST_ERROR);
    if (getLength() < index || index < 0) {
        throw IndexError(INDEX_ERROR);
    }
    for (int i = 0;i < index - 1 ;i++) {
        p = p->next;
    }
    auto p1 = p;
    if (index == 0) {
        first = first->next;
    } else if (p->next->next != nullptr) {
        p1->next = p->next->next;
    } else {
        p1->next = nullptr;
    }
    (*count)--;
}

template <typename T>
List<T> List<T>::combine(const List<T>& lst) {
    List<T> originList(*this);
    originList.addRange(lst);
    return originList;
}

template <typename T>
void List<T>::sort(int (*comp)(const T& r1, const T& r2)) {
    if (getLength() <= 1) return;
    bool swapped;
    do {
        swapped = false;
        std::shared_ptr<Node<T>> ptr1 = first;
        std::shared_ptr<Node<T>> ptr2 = first->next;
        while (ptr2 != nullptr) {
            if (comp(ptr1->data, ptr2->data) > 0) {
                std::swap(ptr1->data, ptr2->data);
                swapped = true;
            }
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }
    } while (swapped);
}

template <typename T>
int List<T>::compare(const T& a, const T& b) {
    if (a < b) return -1;
    if (a > b) return 1;
    return 0;
}

template <typename T>
int List<T>::getIndex(T &elem) const {
    int index = 0;
    int answer = -1;
    Iterator<T> it(*this);
    for (it.start(); !it.isEnd(); it.next()) {
        if (it.value() == elem) {
            answer = index;
            break;
        }
        index++;
    }
    return answer;
}

template <typename T>
T* List<T>::toArray() {
    int length = getLength();
    T* arr = new T[length];
    int index = 0;
    Iterator<T> it(*this);
    for (it.start(); !it.isEnd(); it.next()) {
        arr[index++] = it.value();
    }

    return arr;
}

template <typename T>
T& List<T>::operator[](int index) {
    std::shared_ptr<Node<T>> p = first;
    if (p == nullptr)
        throw EmptyListError(EMPTY_LIST_ERROR);
    if (getLength() < index || index < 0) {
        throw IndexError(INDEX_ERROR);
    }
    for (int i = 0;i < index;i++) {
        p = p->next;
    }
    return p->data;
}

template <typename T>
std::ostream& operator <<(std::ostream& os, List<T>& lst) {
    Iterator<T> it(lst);
    for (it.start(); !it.isEnd(); it.next()) {
        os << it.value() << " ";
    }
    return os;
}

#endif //SECOND_LAB_LIST_H
