cmake_minimum_required(VERSION 3.13)
project(DoubleLinkedList LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

add_library(DoubleLinkedList STATIC
        DoublyLinkedNode.h
        DoublyLinkedList.h
        DoublyLinkedListError.h DoublyLinkedListError.cpp
        DoublyLinkedListEmptyError.h DoublyLinkedListEmptyError.cpp
        DoublyLinkedListOutOfBoundsError.cpp DoublyLinkedListOutOfBoundsError.h
        ConstDoublyLinkedListIterator.h ConstReverseDoublyLinkedIterator.h DoublyLinkedListIterator.h ReverseDoublyLinkedListIterator.h)

target_include_directories(DoubleLinkedList PUBLIC .)
