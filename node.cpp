#include "node.h"

Node::Node(const string &line)
{
    this->set_commandDesc(line); 

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
