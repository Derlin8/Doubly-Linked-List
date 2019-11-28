//
// Created by mfbut on 2/14/2019.
//

#ifndef LINKEDLIST_DOUBLELINKEDLISTTEST_H
#define LINKEDLIST_DOUBLELINKEDLISTTEST_H

#include <string>
#include <vector>
#include <iostream>
#include "gtest/gtest.h"
#include "DoublyLinkedList.h"

template<typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& vec) {
  for (const auto& val : vec) {
    out << val << " ";
  }
  return out;
}

template<typename T>
std::istream& operator>>(std::istream& in, std::vector<T>& vec) {
  while (in) {
    T temp;
    in >> temp;
    vec.push_back(temp);
  }
  return in;
}



template<typename IteratorType>
void iterateForward(IteratorType& itr, int amount) {
  for (int i = 0; i < amount; ++i) {
    ++itr;
  }
}

template<typename IteratorType>
void iterateBackwards(IteratorType& itr, int amount) {
  for (int i = 0; i < amount; ++i) {
    --itr;
  }
}



template<typename DLLIteratorType, typename VectorIteratorType>
::testing::AssertionResult ValuesAreSame(DLLIteratorType dllItr,
                                         DLLIteratorType dllEnd,
                                         VectorIteratorType vecItr,
                                         VectorIteratorType vecEnd,
                                         const std::string& iteratorType) {

  int i = 0;
  for (; dllItr != dllEnd && vecItr != vecEnd; ++dllItr, ++vecItr) {
    if (*dllItr != *vecItr) {
      return ::testing::AssertionFailure()
          << "Your doubly linked list contained a different value from the vector on " << iteratorType << " iteration."
          << std::endl
          << "The first element that was different was element " << i << std::endl
          << "It should have been " << *vecItr << " but was instead " << *dllItr;
    }
    ++i;
  }

  if (!(dllItr == dllEnd && vecItr == vecEnd)) {
    return ::testing::AssertionFailure() << iteratorType
                                         << " iterators did not end at same time despite reporting same size";
  }

  return ::testing::AssertionSuccess();
}


template<typename T>
::testing::AssertionResult dllAndVectorMatch(const DoublyLinkedList<T>& dll, const std::vector<T>& vec) {
  if (static_cast<unsigned int>(dll.size()) != vec.size()) {
    return ::testing::AssertionFailure() <<
                                         "Your doubly linked list has " << dll.size()
                                         << " elements when it should have " << vec.size() << " elements";
  }

  auto dllForwardItr = dll.begin();
  auto dllEndForwardItr = dll.end();
  auto vecForwardItr = vec.begin();
  auto vecEndForwardItr = vec.end();

  ::testing::AssertionResult
      forwardSame = ValuesAreSame<typename DoublyLinkedList<T>::const_iterator, typename std::vector<T>::const_iterator>
      (dllForwardItr, dllEndForwardItr, vecForwardItr, vecEndForwardItr, "forward");
  if (!forwardSame) {
    return forwardSame;
  }

  auto dllConstReverseItr = dll.crbegin();
  auto dllEndConstReverseItr = dll.crend();
  auto vecConstReverseItr = vec.crbegin();
  auto vecEndConstReverseItr = vec.crend();

  ::testing::AssertionResult
      reverseSame = ValuesAreSame<typename DoublyLinkedList<T>::const_reverse_iterator,
                                  typename std::vector<T>::const_reverse_iterator>
      (dllConstReverseItr, dllEndConstReverseItr, vecConstReverseItr, vecEndConstReverseItr, "reverse");
  if (!reverseSame) {
    return reverseSame;
  }

  return ::testing::AssertionSuccess();

}

template<typename T>
class DoubleLinkedListTest : public ::testing::Test {
 public:
  static std::vector<T> constructorArgs;
  static std::vector<T> pushFrontArgs;
  static std::vector<T> pushBackArgs;
};

#endif //LINKEDLIST_DOUBLELINKEDLISTTEST_H
