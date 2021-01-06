//
// Created by mfbut on 2/11/2019.
//

#ifndef LINKEDLIST_DOUBLELINKEDNODE_H
#define LINKEDLIST_DOUBLELINKEDNODE_H
#include <iostream>

template<typename T>
class DoublyLinkedNode {
    public:
        DoublyLinkedNode(const T& value);
        T& getValue();
        T& getNonConstValue();
        DoublyLinkedNode* getPrev() const;
        DoublyLinkedNode* getNext() const;

        void setPrev(DoublyLinkedNode<T>* newPrev);
        void setNext(DoublyLinkedNode<T>* newNext);

        T data;
        DoublyLinkedNode<T>* next;
        DoublyLinkedNode<T>* previous;
};

template<typename T>
DoublyLinkedNode<T>::DoublyLinkedNode(const T& value) : data(value), next(), previous() {
}

template<typename T>
T& DoublyLinkedNode<T>::getValue() {
    return data;
}


template<typename T>
DoublyLinkedNode<T>* DoublyLinkedNode<T>::getPrev() const {
    return this->previous;
}

template<typename T>
DoublyLinkedNode<T>* DoublyLinkedNode<T>::getNext() const {
    return this->next;
}

template<typename T>
void DoublyLinkedNode<T>::setPrev(DoublyLinkedNode<T>* newPrev) {
    previous = newPrev;
}

template<typename T>
void DoublyLinkedNode<T>::setNext(DoublyLinkedNode<T>* newNext) {
    next = newNext;
}

#endif //LINKEDLIST_DOUBLELINKEDNODE_H
