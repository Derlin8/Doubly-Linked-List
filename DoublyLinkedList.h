//
// Created by mfbut on 2/11/2019.
//

#ifndef LINKEDLIST_DOUBLYLINKEDLIST_H
#define LINKEDLIST_DOUBLYLINKEDLIST_H

#include <vector>
#include <memory>
#include "DoublyLinkedNode.h"
#include "DoublyLinkedListEmptyError.h"
#include "ConstDoublyLinkedListIterator.h"
#include "DoublyLinkedListIterator.h"
#include "ConstReverseDoublyLinkedIterator.h"
#include "ReverseDoublyLinkedListIterator.h"

template<typename T>
class DoublyLinkedList {
 public:
  using Node_Ptr = DoublyLinkedNode<T>*;
  using iterator = DoublyLinkedListIterator<T>; //put the type of your iterator here
  using const_iterator =  ConstDoublyLinkedListIterator<T>; //put the type of your const iterator here
  using reverse_iterator = ReverseDoublyLinkedListIterator<T>; //put the type of your reverse iterator here
  using const_reverse_iterator = ConstReverseDoublyLinkedListIterator<T>; //put the type of your const reverse iterator here

  //create a Doubly Linked List that has the same values
  //as in the vector and in the same order
  explicit DoublyLinkedList(const std::vector<T>& values);

  //create an empty DoublyLinkedList
  DoublyLinkedList();


  //destructor
  virtual ~DoublyLinkedList();

  //remove all of the elements from your list
  void clear();

  //get a reference to the front element in the list
  const T& front() const;
  T& front();

  //get a reference to the last element in the list
  const T& back() const;
  T& back();

  //add a value to the front of the list
  void push_front(const T& value);

  //add a value to the back of the list
  void push_back(const T& value);

  //is the list empty?
  bool empty() const;

  //return the number of elements in the list
  int size() const;

  //return a constant bidirectional iterator to the front of the list
  const_iterator begin() const;
  const_iterator end() const;

  //return a nonconstant bidirectional iterator to the front of the list
  iterator begin();
  iterator end();

  const_reverse_iterator crbegin() const;
  const_reverse_iterator crend() const;

  reverse_iterator rbegin();
  reverse_iterator rend();

  //insert the value at the position in the list
  //I promise not to use the iterator again after the insertion is done
  //An example if we had the list 1 <-> 9 <-> 17
  //And the iterator was pointing to the 9 and we wanted to
  //insert -22 the result would be
  //1 <-> 22 <-> 9 <-> 17
  void insert(iterator& position, const T& value);

  //remove the element at the position pointed to
  //by the iterator.
  //I promise not to use the iterator again after the erase is done
  //An example if we had the list 1 <-> 9 <-> 17
  //And when the wanted to erase the iterator was at the 9
  //1 <-> 17
  void erase(iterator& position);

 private:
    Node_Ptr head;
    Node_Ptr tail;
};

//write to the stream each element in the list in order
//with a space in between them
template<typename T>
std::ostream& operator<<(std::ostream& out, const DoublyLinkedList<T>& doublyLinkedList);

//read elements from the stream as long as it is good
// or until a newline (\n) is encountered
//if a newline is encountered it should be consumed
template<typename T>
std::istream& operator>>(std::istream& in, DoublyLinkedList<T>& doublyLinkedList);

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList()  {
    head = NULL;
    tail = NULL;
}

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList(const std::vector<T>& values)  {
    head = NULL;
    tail = NULL;
    for (auto iter = values.begin(); iter != values.end(); iter++) {
        push_back(*iter);
    }
}

template<typename T>
bool DoublyLinkedList<T>::empty() const {
    return head == NULL && tail == NULL;
}

template<typename T>
int DoublyLinkedList<T>::size() const {
    int size = 0;

    const_iterator ptr = begin();
    while(ptr) {
        size++;
        ptr++;
    }
    return size;
}

template<typename T>
const T& DoublyLinkedList<T>::front() const {

    if(size() == 0) {
        throw DoublyLinkedListEmptyError("Empty");
    }

    return head->getValue();
}

template<typename T>
T& DoublyLinkedList<T>::front() {
    if(size() == 0) {
        throw DoublyLinkedListEmptyError("Empty");
    }
    return head->getValue();
}

template<typename T>
const T& DoublyLinkedList<T>::back() const {
    if(size() == 0) {
        throw DoublyLinkedListEmptyError("Empty");
    }
    return tail->getValue();
}

template<typename T>
T& DoublyLinkedList<T>::back() {
    if(size() == 0) {
        throw DoublyLinkedListEmptyError("Empty");
    }
    return tail->getValue();
}

template<typename T>
void DoublyLinkedList<T>::push_front(const T& value) {
//    Node_Ptr newSecond = head;
//    Node_Ptr newHead = new DoublyLinkedNode<T>(value);
//    head = newHead;
//    head->setNext(newSecond);
    Node_Ptr newNode = new DoublyLinkedNode<T>(value);
    if (head == NULL) {
        head = newNode;
    } else {
        newNode->next = head;
        head->previous = newNode;
        head = newNode;
    }

    if(tail == NULL) {
        tail = head;
    }
}

template<typename T>
void DoublyLinkedList<T>::push_back(const T& value) {

    Node_Ptr newNode = new DoublyLinkedNode<T>(value);
    if (tail == NULL) {
        tail = newNode;
    } else {
        tail->next = newNode;
        newNode->previous = tail;
        tail = tail->getNext();
    }

    if(head == NULL) {
        head = tail;
    }
}

template<typename T>
void DoublyLinkedList<T>::clear() {
    head = NULL;
    tail = NULL;
}

template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    head = NULL;
    tail = NULL;
}

template<typename T>
typename DoublyLinkedList<T>::const_iterator DoublyLinkedList<T>::begin() const {
    return *new const_iterator(head);
}

template<typename T>
typename DoublyLinkedList<T>::const_iterator DoublyLinkedList<T>::end() const {
    if (tail == NULL) {
        return *new const_iterator(tail);
    }
    return *new const_iterator(tail->getNext());
}

template<typename T>
typename DoublyLinkedList<T>::iterator DoublyLinkedList<T>::begin() {
    return *new iterator(head);
}

template<typename T>
typename DoublyLinkedList<T>::iterator DoublyLinkedList<T>::end() {
    if (tail == NULL) {
        return *new iterator(tail);
    }
    return *new iterator(tail->getNext());
}

template<typename T>
void DoublyLinkedList<T>::insert(iterator& position, const T& value) {

    Node_Ptr current = head;
    iterator it = *new iterator(head);
    while(it != position) {
        it++;
        current = current->next;
    }

    if (current == head) {
        push_front(value);
        return;
    }

    if (it == end()) {
        push_back(value);
        return;
    }

    Node_Ptr newNode = new DoublyLinkedNode<T>(value);
    newNode->next = current;
    newNode->previous = current->previous;
    current->previous->next = newNode;
    current->previous = newNode;
}

template<typename T>
void DoublyLinkedList<T>::erase(iterator& position) {
    Node_Ptr current = head;
    iterator it = *new iterator(head);
    while(it != position) {
        it++;
        current = current->next;
    }

    if (current == head && current == tail) {
        head = NULL;
        tail = NULL;
        free(current);
        return;
    }

    if (current == head) {
        head = current->next;
        current->next->previous = NULL;
        free(current);
        return;
    }

    if (current == tail) {
        tail = current->previous;
        tail->next = NULL;
        free(current);
        return;
    }

    current->previous->next = current->next;
    current->next->previous = current->previous;
    free(current);
}

template<typename T>
typename DoublyLinkedList<T>::const_reverse_iterator DoublyLinkedList<T>::crbegin() const {
    return *new const_reverse_iterator(tail);
}

template<typename T>
typename DoublyLinkedList<T>::const_reverse_iterator DoublyLinkedList<T>::crend() const {
    if (head == NULL) {
        return *new const_reverse_iterator(head);
    }
    return *new const_reverse_iterator(head->previous);
}

template<typename T>
typename DoublyLinkedList<T>::reverse_iterator DoublyLinkedList<T>::rbegin() {
    return *new reverse_iterator(tail);
}

template<typename T>
typename DoublyLinkedList<T>::reverse_iterator DoublyLinkedList<T>::rend() {
    if (head == NULL) {
        return *new reverse_iterator(head);
    }
    return *new reverse_iterator(head->previous);
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const DoublyLinkedList<T>& doublyLinkedList) {

    auto it = doublyLinkedList.begin();
    while(it != doublyLinkedList.end()) {
        out << *it;
        it++;
    }
    return out;
}

template<typename T>
std::istream& operator>>(std::istream& in, DoublyLinkedList<T>& doublyLinkedList) {

    T buffer;
    while(in >> buffer) {
        doublyLinkedList.push_back(buffer);
    }
    return in;
}

#endif //LINKEDLIST_DOUBLYLINKEDLIST_H
