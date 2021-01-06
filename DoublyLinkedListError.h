//
// Created by mfbut on 11/24/2019.
//

#ifndef TESTDOUBLELINKEDLIST_DOUBLYLINKEDLISTERROR_H
#define TESTDOUBLELINKEDLIST_DOUBLYLINKEDLISTERROR_H
#include <string>
class DoublyLinkedListError: public std::exception {

    virtual const char* what() const throw (){
        return message.c_str();
    }

protected:
    std::string message;

    explicit DoublyLinkedListError(const std::string& message) : message(message) {

    }
};

#endif //TESTDOUBLELINKEDLIST_DOUBLYLINKEDLISTERROR_H
