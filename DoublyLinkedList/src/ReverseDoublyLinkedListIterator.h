//
// Created by mfbut on 11/24/2019.
//

#ifndef DLLPROJECT_REVERSEDOUBLYLINKEDLISTITERATOR_H
#define DLLPROJECT_REVERSEDOUBLYLINKEDLISTITERATOR_H

#include <iterator>
#include "DoublyLinkedNode.h"

template <typename T>
class ReverseDoublyLinkedListIterator {
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
  explicit ReverseDoublyLinkedListIterator(DoublyLinkedNode<T>* start);
  //set the iterator to be at null
  ReverseDoublyLinkedListIterator();
  //copy constructor
  ReverseDoublyLinkedListIterator(const ReverseDoublyLinkedListIterator<T>& orig);

  //are the two iterators equal?
  bool operator==(const ReverseDoublyLinkedListIterator<T>& rhs) const;
  //are the two iterators different?
  bool operator!=(const ReverseDoublyLinkedListIterator<T>& rhs) const;
  //is the iterator safe to dereference?
  explicit operator bool() const;

  //go to the next element
  ReverseDoublyLinkedListIterator<T>& operator++(); //pre
  const ReverseDoublyLinkedListIterator<T> operator++(int);//post

  //go to the previous element
  ReverseDoublyLinkedListIterator<T>& operator--(); //pre
  const ReverseDoublyLinkedListIterator<T> operator--(int); //post

  //get a reference to the value
  const_reference operator*() const;
  reference operator*();

 private:
  DoublyLinkedNode<T>* curNode;
};

template<typename T>
ReverseDoublyLinkedListIterator<T>::ReverseDoublyLinkedListIterator(DoublyLinkedNode<T>* start) : curNode(start) {

}

template<typename T>
ReverseDoublyLinkedListIterator<T>::ReverseDoublyLinkedListIterator() : curNode(nullptr){

}

template<typename T>
ReverseDoublyLinkedListIterator<T>::ReverseDoublyLinkedListIterator(const ReverseDoublyLinkedListIterator<T>& orig) : curNode(orig.curNode){

}

template<typename T>
bool ReverseDoublyLinkedListIterator<T>::operator==(const ReverseDoublyLinkedListIterator<T>& rhs) const {
  return curNode == rhs.curNode;
}

template<typename T>
bool ReverseDoublyLinkedListIterator<T>::operator!=(const ReverseDoublyLinkedListIterator<T>& rhs) const {
  return !(*this == rhs);
}

template<typename T>
ReverseDoublyLinkedListIterator<T>::operator bool() const {
  return curNode != nullptr;
}

template<typename T>
ReverseDoublyLinkedListIterator<T>& ReverseDoublyLinkedListIterator<T>::operator++() {
  curNode = curNode->getPrev();
  return *this;
}

template<typename T>
const ReverseDoublyLinkedListIterator<T> ReverseDoublyLinkedListIterator<T>::operator++(int) {
  ReverseDoublyLinkedListIterator<T> curPos(*this);
  ++(*this);
  return curPos;
}

template<typename T>
ReverseDoublyLinkedListIterator<T>& ReverseDoublyLinkedListIterator<T>::operator--() {
  curNode = curNode->getNext();
  return *this;
}

template<typename T>
const ReverseDoublyLinkedListIterator<T> ReverseDoublyLinkedListIterator<T>::operator--(int) {
  ReverseDoublyLinkedListIterator<T> curPos(*this);
  --(*this);
  return curPos;
}

template<typename T>
typename ReverseDoublyLinkedListIterator<T>::const_reference ReverseDoublyLinkedListIterator<T>::operator*() const {
  if(*this) {
    return curNode->getValue();
  }else{
    throw DoublyLinkedListOutOfBoundsError();
  }
}

template<typename T>
typename ReverseDoublyLinkedListIterator<T>::reference ReverseDoublyLinkedListIterator<T>::operator*() {
  if(*this) {
    return curNode->getValue();
  }else{
    throw DoublyLinkedListOutOfBoundsError();
  }
}



#endif //DLLPROJECT_REVERSEDOUBLYLINKEDLISTITERATOR_H
