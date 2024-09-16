#include "linkedlist.h"
//? constructor():
List::List()
{
    this->pHead = this->pTail = nullptr;
    this->list_size = 0;
}

//? isEmpty():
bool List::isEmpty()
{
    bool value = false;

    //? if pHead == null, list is empty
    if (this->pHead == nullptr)
    {
        value = true;
    }

    return value;
}

//? insert(const string& line):
void List::insert(const string &line)
{
    //? Variables for storing information to correctly put into list
    string nName, nDesc;
    int delimiter = line.find(",");

    //? break up the line into respective parts w/ the delimiter being the ','
    nName = line.substr(0, delimiter);
    nDesc = line.substr(delimiter + 1, line.size() - 1);

    //? put divided up data into a new node
    Node *nNode = new Node(nName, nDesc);

    //? if list is empty:
    if (this->isEmpty() == true)
    {
        // cout << "in empty loop" << endl;
        this->pHead = nNode;
        this->pTail = nNode;
    }
    //? if list already has an element
    else
    {
        this->pTail->setNext(nNode);
        this->pTail = nNode;
    }

    //? increment the size of the list
    this->list_size++;

    return;
}

bool List::remove(const string &target_command)
{
    //? variables to keep track of the node after the target & one to create a copy list
    //? and a bool value to track if the command name was found
    bool found = false;
    Node *current = this->pHead;
    Node *previous = nullptr;

    cout << this->pTail->get_commandName() << endl
         << endl;
    cout << current->get_commandName() << endl;

    //? if list is empty:
    if (this->isEmpty() == true)
    {
        cout << "List is empty." << endl;
        return found;
    }

    //? if the target is the first element of the list
    if (current->get_commandName() == target_command)
    {
        found = true;
        current = current->getNext();
        this->pHead = current;
    }

    //? else:
    else
    {
        while (current->getNext() != nullptr)
        {
            previous = current;

            if (current->getNext()->get_commandName() == target_command)
            {
                found = true;
                break;
            }
            current = current->getNext();
        }
        current = current->getNext();
        previous->setNext(current->getNext());
        current = previous;
        this->pTail = previous;
    }

    if (found == true)
    {
        cout << "Target: " << target_command << " removed." << endl;
        this->list_size--;
    }

    return found;
}

//? display()
void List::display()
{
    if (this->isEmpty() == true)
    {
        cout << "List is empty, no elements to display." << endl;
        return;
    }

    Node *copyList = this->pHead;
    int i = 0;

    while (copyList != nullptr)
    {
        //? print current data cell in copy list
        cout << i + 1 << ". " << setw(5) << copyList->get_commandName() << "," << copyList->get_commandDesc() << endl;

        //? update copy list to the next item in the list
        copyList = copyList->getNext();

        //? increment i
        i++;
    }

    return;
}

//? size()
int List::size()
{
    return this->list_size;
}

//? overwrite()
void List::overwrite()
{
    ofstream myCommands("/home/matthewhong/CPTS223/PA-1_Hong/commands.csv", ios::trunc);

    //? make a copy of the list to ensure the original isn't edited
    Node *copyList = this->pHead;

    //? loop until all elements in the list are written to output file
    while (copyList != nullptr)
    {
        myCommands << copyList->get_commandName() << "," << copyList->get_commandDesc() << endl;
        copyList = copyList->getNext();
    }

    myCommands.close();
    return;
}

Node *List::search(const int &target_number)
{
    Node *copyList = this->pHead,
         *target;

    for (int i = 1; i < this->size(); i++)
    {
        if (target_number == i)
        {
            target = copyList; 
            break;
        }
        copyList = copyList->getNext();
    }

    return target; 
}
