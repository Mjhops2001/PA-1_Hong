#pragma once
#include <fstream>
#include <iostream>

using namespace std;

/* Class: node
 ?
 ? Attributes:
 ? - string command_name
 ? - string command_desc
 ? - Node *pNext
 ?
 ? Functions:
 ? setters:
    * stores passed in parameters into their respective variables for pNext,
    * command_name, & command_desc
 ? getters:
    * returns the current values stored in pNext, command_name, & command_desc

 */

class Node
{
private:
    string command_name;
    string command_defn;
    Node *pNext;

public:
    //? Constructors/destructor
    Node();
    Node(const string &nName, const string &nDesc);

    //? Member Functions
    void setNext(Node *next);
    void set_commandName(const string &newName);
    void set_commandDesc(const string &newDesc);

    Node *getNext();
    string get_commandName();
    string get_commandDesc();
};