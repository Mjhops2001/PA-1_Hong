#pragma once
#include "node.h"

/*
 * Class: list
 ?
 ? Attributes: 
 ? - Head Node - points to the front of the list
 ? - Tail Node - points to the end of the list
 ?
 ? Functions:
 ? - isEmpty(): returns true/false depending if the list is empty or not
 ? - insert(): inserts new element in the list
 ? - remove(): removes a new element in the list
 ? - display(): prints out all elements in the list 
 ? - size(): Returns the size of the list
 */
class List
{
private:
    Node *pHead;
    Node *pTail;

public:
    //? Constructor/Destructor: 
    List();
    ~List(); 

    //? Member Functions: 
    bool isEmpty(); 
    void insert(); 
    void remove();
    void display(); 
    void size(); 
};