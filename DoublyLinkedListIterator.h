//
// Created by mfbut on 11/24/2019.
//

#ifndef DLLPROJECT_DOUBLYLINKEDLISTITERATOR_H
#define DLLPROJECT_DOUBLYLINKEDLISTITERATOR_H

#include <iterator>
#include "DoublyLinkedNode.h"

template <typename T>
class DoublyLinkedListIterator {
 public:
  //type tags
  using iterator_category = std::bidirectional_iterator_tag;
  using value_type = T;
  using reference = value_type&;
  using const_reference = const value_type&;
  using pointer = value_type*;
  using const_pointer = const value_type*;
  using difference_type = ptrdiff_t;

  //create an iterator starting at the specified node
  explicit DoublyLinkedListIterator(DoublyLinkedNode<T>* start);

  //set the iterator to be at null
  DoublyLinkedListIterator();

  //copy constructor
  DoublyLinkedListIterator(const DoublyLinkedListIterator<T>& orig);

  //are the two iterators equal?
  bool operator==(const DoublyLinkedListIterator<T>& rhs) const;
  //are the two iterators different?
  bool operator!=(const DoublyLinkedListIterator<T>& rhs) const;
  //is the iterator safe to dereference?
  explicit operator bool() const;

  //go to the next element
  DoublyLinkedListIterator<T>& operator++(); //pre
  const DoublyLinkedListIterator<T> operator++(int);//post

  //go to the previous element
  DoublyLinkedListIterator<T>& operator--(); //pre
  const DoublyLinkedListIterator<T> operator--(int); //post

  //get a reference to the value
  const_reference operator*() const;
  reference operator*();

 private:
  DoublyLinkedNode<T>* curNode;
};

template<typename T>
DoublyLinkedListIterator<T>::DoublyLinkedListIterator(DoublyLinkedNode<T>* start) : curNode(start) {

}

template<typename T>
DoublyLinkedListIterator<T>::DoublyLinkedListIterator() : curNode(nullptr){

}

template<typename T>
DoublyLinkedListIterator<T>::DoublyLinkedListIterator(const DoublyLinkedListIterator<T>& orig) : curNode(orig.curNode){

}

template<typename T>
bool DoublyLinkedListIterator<T>::operator==(const DoublyLinkedListIterator<T>& rhs) const {
    if (curNode != NULL && rhs.curNode != NULL) {
        return (curNode->data == rhs.curNode->data);
    }
    return curNode == rhs.curNode;
}

template<typename T>
bool DoublyLinkedListIterator<T>::operator!=(const DoublyLinkedListIterator<T>& rhs) const {
    if (curNode != NULL && rhs.curNode != NULL) {
        return (curNode->data != rhs.curNode->data);
    }
    return curNode != rhs.curNode;
}

template<typename T>
DoublyLinkedListIterator<T>::operator bool() const {
  return curNode != nullptr;
}

template<typename T>
DoublyLinkedListIterator<T>& DoublyLinkedListIterator<T>::operator++() {
  curNode = curNode->next;
  return *this;
}

template<typename T>
const DoublyLinkedListIterator<T> DoublyLinkedListIterator<T>::operator++(int) {
  DoublyLinkedListIterator<T> curPos(*this);
  ++(*this);
  return curPos;
}

template<typename T>
DoublyLinkedListIterator<T>& DoublyLinkedListIterator<T>::operator--() {
  curNode = curNode->getPrev();
  return *this;
}

template<typename T>
const DoublyLinkedListIterator<T> DoublyLinkedListIterator<T>::operator--(int) {
  DoublyLinkedListIterator<T> curPos(*this);
  --(*this);
  return curPos;
}

template<typename T>
typename DoublyLinkedListIterator<T>::const_reference DoublyLinkedListIterator<T>::operator*() const {
  if(*this) {
    return curNode->getValue();
  }else{
    throw DoublyLinkedListOutOfBoundsError("Out of Bounds");
  }
}

template<typename T>
typename DoublyLinkedListIterator<T>::reference DoublyLinkedListIterator<T>::operator*() {
  if(*this) {
    return curNode->getValue();
  }else{
    throw DoublyLinkedListOutOfBoundsError("Out of Bounds");
  }
}





#endif //DLLPROJECT_DOUBLYLINKEDLISTITERATOR_H
