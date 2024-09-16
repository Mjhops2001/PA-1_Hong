#pragma once
#include <iomanip>
#include <cstring>
#include "node.h"


/*
 * Class: list
 ? Attributes:
 ? - Head Node:
    * points to the front of the list
 ? - Tail Node:
    * points to the end of the list
 ? - int size:
    * integer value to keep track of the current size of the node


 ? Functions:
 ? - isEmpty(): returns true/false depending if the list is empty or not
    * returns true if empty, false if it isnt

 ? - insert(): inserts new element in the list
    * takes in a string named line that breaks it up into two pieces
    * and places that into the

 ? - remove(): removes a new element in the list
    * takes in a string named 'target_name' that deletes the node w/ the
    * matching name

 ? - display(): prints out all elements in the list
    * displays all elements in list to the command terminal

 ? - size(): Returns the size of the list
    * returns the current size of the list as an integer
 */
class List
{
private:
   //? Attributes:
   Node *pHead;
   Node *pTail;
   int list_size;

public:
   //? Constructor/Destructor:
   List();

   //? Member Functions:
   bool isEmpty();
   void insert(const string &line);
   bool remove(const string &target_command);
   void display();
   int size();
   void overwrite();
   Node* search(const int& target_number); 
};