//
// Created by mfbut on 11/24/2019.
//

#ifndef DLLPROJECT_CONSTREVERSEDOUBLYLINKEDITERATOR_H
#define DLLPROJECT_CONSTREVERSEDOUBLYLINKEDITERATOR_H

#include <iterator>
#include "DoublyLinkedNode.h"

template <typename T>
class ConstReverseDoublyLinkedListIterator {
 public:
  //type tags
  using iterator_category = std::bidirectional_iterator_tag;
  using value_type = T;
  using reference =  const value_type&;
  using pointer =  const value_type*;
  using difference_type = ptrdiff_t;

  //create an iterator starting at the specified node
  explicit ConstReverseDoublyLinkedListIterator(const DoublyLinkedNode<T>* start);

  //set the iterator to be at null
  ConstReverseDoublyLinkedListIterator();

  //copy constructor
  ConstReverseDoublyLinkedListIterator(const ConstReverseDoublyLinkedListIterator<T>& orig);

  //are the two iterators equal?
  bool operator==(const ConstReverseDoublyLinkedListIterator<T>& rhs) const;
  //are the two iterators different?
  bool operator!=(const ConstReverseDoublyLinkedListIterator<T>& rhs) const;
  //is the iterator safe to dereference?
  explicit operator bool() const;

  //go to the next element
  ConstReverseDoublyLinkedListIterator<T>& operator++(); //pre
  const ConstReverseDoublyLinkedListIterator<T> operator++(int);//post

  //go to the previous element
  ConstReverseDoublyLinkedListIterator<T>& operator--(); //pre
  const ConstReverseDoublyLinkedListIterator<T> operator--(int); //post

  //get a reference to the value
  reference operator*() const;


 private:
  const DoublyLinkedNode<T>* curNode;
};

template<typename T>
ConstReverseDoublyLinkedListIterator<T>::ConstReverseDoublyLinkedListIterator(const DoublyLinkedNode<T>* start) {

}

template<typename T>
ConstReverseDoublyLinkedListIterator<T>::ConstReverseDoublyLinkedListIterator() {

}

template<typename T>
ConstReverseDoublyLinkedListIterator<T>::ConstReverseDoublyLinkedListIterator(const ConstReverseDoublyLinkedListIterator<T>& orig) {

}

template<typename T>
bool ConstReverseDoublyLinkedListIterator<T>::operator==(const ConstReverseDoublyLinkedListIterator<T>& rhs) const {

}

template<typename T>
bool ConstReverseDoublyLinkedListIterator<T>::operator!=(const ConstReverseDoublyLinkedListIterator<T>& rhs) const {

}

template<typename T>
ConstReverseDoublyLinkedListIterator<T>::operator bool() const {


}

template<typename T>
ConstReverseDoublyLinkedListIterator<T>& ConstReverseDoublyLinkedListIterator<T>::operator++() {


}

template<typename T>
const ConstReverseDoublyLinkedListIterator<T> ConstReverseDoublyLinkedListIterator<T>::operator++(int) {


}

template<typename T>
ConstReverseDoublyLinkedListIterator<T>& ConstReverseDoublyLinkedListIterator<T>::operator--() {


}

template<typename T>
const ConstReverseDoublyLinkedListIterator<T> ConstReverseDoublyLinkedListIterator<T>::operator--(int) {


}

template<typename T>
typename ConstReverseDoublyLinkedListIterator<T>::reference ConstReverseDoublyLinkedListIterator<T>::operator*() const {

}




#endif //DLLPROJECT_CONSTREVERSEDOUBLYLINKEDITERATOR_H
