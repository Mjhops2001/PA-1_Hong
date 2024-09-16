#include "node.h"

Node::Node()
{
    this->command_name = "command_name";
    this->command_defn = "command_defn";
    this->pNext = nullptr;
}

Node::Node(const string &nName, const string &nDesc)
{
    this->set_commandName(nName); 
    this->set_commandDesc(nDesc); 
    this->pNext = nullptr; 
}

void Node::setNext(Node *next)
{
    this->pNext = next;
}

void Node::set_commandName(const string &newName)
{
    this->command_name = newName;
}

void Node::set_commandDesc(const string &newDefn)
{
    this->command_defn = newDefn;
}

Node *Node::getNext()
{
    return this->pNext;
}

string Node::get_commandName()
{
    return this->command_name;
}

string Node::get_commandDesc()
{
    return this->command_defn;
}
