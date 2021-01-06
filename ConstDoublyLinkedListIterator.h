//
// Created by mfbut on 11/24/2019.
//

#ifndef DLLPROJECT_CONSTDOUBLYLINKEDLISTITERATOR_H
#define DLLPROJECT_CONSTDOUBLYLINKEDLISTITERATOR_H

#include <iterator>
#include "DoublyLinkedNode.h"
#include "DoublyLinkedListOutOfBoundsError.h"

template<typename T>
class ConstDoublyLinkedListIterator {
 public:
  //type tags
  using iterator_category = std::bidirectional_iterator_tag;
  using value_type = T;
  using reference = const value_type&;
  using pointer = const value_type*;
  using difference_type = ptrdiff_t;

  //create an iterator starting at the specified node
  explicit ConstDoublyLinkedListIterator(const DoublyLinkedNode<T>* start);

  //set the iterator to be at null
  ConstDoublyLinkedListIterator();

  //copy constructor
  ConstDoublyLinkedListIterator(const ConstDoublyLinkedListIterator<T>& orig);

  //are the two iterators equal?
  bool operator==(const ConstDoublyLinkedListIterator<T>& rhs) const;
  //are the two iterators different?
  bool operator!=(const ConstDoublyLinkedListIterator<T>& rhs) const;
  //is the iterator safe to dereference?
  explicit operator bool() const;

  //go to the next element
  ConstDoublyLinkedListIterator<T>& operator++(); //pre
  const ConstDoublyLinkedListIterator<T> operator++(int);//post

  //go to the previous element
  ConstDoublyLinkedListIterator<T>& operator--(); //pre
  const ConstDoublyLinkedListIterator<T> operator--(int); //post

  //get a reference to the value
  reference operator*() const;

 private:
  const DoublyLinkedNode<T>* curNode;
};

template<typename T>
ConstDoublyLinkedListIterator<T>::ConstDoublyLinkedListIterator(const DoublyLinkedNode<T>* start)  {
    curNode = start;
}

template<typename T>
ConstDoublyLinkedListIterator<T>::ConstDoublyLinkedListIterator()  {

}

template<typename T>
ConstDoublyLinkedListIterator<T>::ConstDoublyLinkedListIterator(const ConstDoublyLinkedListIterator<T>& orig) {
    curNode = orig.curNode;
}

template<typename T>
bool ConstDoublyLinkedListIterator<T>::operator==(const ConstDoublyLinkedListIterator<T>& rhs) const {
    if (curNode != NULL && rhs.curNode != NULL) {
        return (curNode->data == rhs.curNode->data);
    }
    return curNode == rhs.curNode;
}

template<typename T>
bool ConstDoublyLinkedListIterator<T>::operator!=(const ConstDoublyLinkedListIterator<T>& rhs) const {
    if (curNode != NULL && rhs.curNode != NULL) {
        return (curNode->data != rhs.curNode->data);
    }
    return curNode != rhs.curNode;
}

template<typename T>
ConstDoublyLinkedListIterator<T>::operator bool() const {
    return curNode != NULL;
}

template<typename T>
ConstDoublyLinkedListIterator<T>& ConstDoublyLinkedListIterator<T>::operator++() {
    this->curNode = curNode->getNext();
    return *this;
}

template<typename T>
const ConstDoublyLinkedListIterator<T> ConstDoublyLinkedListIterator<T>::operator++(int) {
    ConstDoublyLinkedListIterator<T>& current = *this;
    this->curNode = curNode->getNext();
    return current;
}

template<typename T>
ConstDoublyLinkedListIterator<T>& ConstDoublyLinkedListIterator<T>::operator--() {
    this->curNode = curNode->getPrev();
    return this;
}

template<typename T>
const ConstDoublyLinkedListIterator<T> ConstDoublyLinkedListIterator<T>::operator--(int) {
    ConstDoublyLinkedListIterator<T>& current = *this;
    this->curNode = curNode->getPrev();
    return current;
}

template<typename T>
typename ConstDoublyLinkedListIterator<T>::reference ConstDoublyLinkedListIterator<T>::operator*() const {
    if(*this) {
        return curNode->data;
    }else{
        throw new DoublyLinkedListOutOfBoundsError("Out of Bounds.");
    }
}



#endif //DLLPROJECT_CONSTDOUBLYLINKEDLISTITERATOR_H
