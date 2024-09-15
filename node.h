#pragma once
#include <fstream>
#include <iostream>

using namespace std;

/* Class: node
 ?
 ? Attributes:
 ? - constructors
 ? - setters
 ? - getters

 ?
 ? Functions:
 */

class Node
{
private:
    string command_name;
    string command_defn;
    Node *pNext;

public:
    Node(const string &line);

    void setNext(Node *next);
    void set_commandName(const string &newName);
    void set_commandDesc(const string &newDesc);

    Node *getNext();
    string get_commandName();
    string get_commandDesc();
};