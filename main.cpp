/*
ADVANTAGES/DISADVANTAGES LINKED LIST

ADVANTAGES/DISADVANTAGES ARRAY
*/
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <chrono>
#include <ctime>
#include "linkedlist.h"

using namespace std;

/*
 *---------------------------------------------------------------------*
 * profile_data
 ? struct to hold the stored data in profiles.csv
 ? (the points & name of saved player data)
 */
struct profile_data
{
    string user_name = "player_name";
    unsigned int user_points = -1;
};

/*
 *---------------------------------------------------------------------*
 * check()
 ? checks if the passed ifstream/ofstream variable opened properly
 ? returns true if open, false if closed
 */
bool check(ifstream &myFile)
{
    //? T/F variable
    bool boolean;

    if (myFile.is_open())
    {
        cout << "File Status: OPEN" << endl;
        boolean = true;
    }
    else
    {
        cout << "File Status: CLOSED - NOT FOUND" << endl;
        boolean = false;
    }

    return boolean;
}
bool check(ofstream &myFile)
{
    bool boolean;

    if (myFile.is_open())
    {
        cout << "File Status: OPEN" << endl;
        boolean = true;
    }
    else
    {
        cout << "File Status: CLOSED - NOT FOUND" << endl;
        boolean = false;
    }

    return boolean;
}

/*
 *---------------------------------------------------------------------*
 * populate()
 ? reads commands.csv & inputs data into linked list
 */
void populate(List &myList) // Read CSV and input data into a linked list
{
    cout << "---------------Populating List---------------" << endl;

    //? Open file containing list of commands & verify it opened
    ifstream myCommands("/home/matthewhong/CPTS223/PA-1_Hong/commands.csv");
    check(myCommands);
    string line,
        input;

    //? contine parsing thru file & insert the commands into the list
    while (getline(myCommands, line))
    {
        myList.insert(line);
    }

    //? ask user if they want to display the list contents
    do
    {
        cout << "List was successfuly loaded. Display list contents? [y/n]: ";
        cin >> input;
    } while (input != "y" && input != "n" && input != "Y" && input != "N");

    //? input == yes:
    if (input == "y" || input == "Y")
    {
        cout << "List size: " << myList.size() << endl;
        cout << "List contents: " << endl
             << endl;
        myList.display();
    }

    myCommands.close();
    cout << "---------------------------------------------" << endl;
    cout << endl
         << endl;

    if (input == "n" || input == "N")
    {
        system("clear");
    }
}

/*
 *---------------------------------------------------------------------*
 * isUnique()
 ? takes in a randomly generated number, the array of questions, & the current size of the array of questions
 */
bool isUnique(const int &random_number, const int *array, int array_size)
{
    bool found = false;

    for (int i = 0; i < array_size; i++)
    {
        if (array[i] == random_number)
        {
            found = true;
        }
    }

    return found;
}

/*
 *---------------------------------------------------------------------*
 * generateQuestions()
 ? takes in a randomly generated numbers, the array of questions, & the current size of the array of questions
 */
void generateQuestions(int *questions_array, int &number_of_questions, int size)
{

    //? grab the number of questions from user input [between 5 - 30]
    while (number_of_questions < 5 || number_of_questions > 30)
    {
        cout << "Please select how many questions you would like to " << endl
             << "be asked [5 - " << size << "]: ";

        cin >> number_of_questions;
    }

    cout << "User selected: " << number_of_questions << " questions." << endl;

    //? generate unique numbers for the x number of questions the user selected
    for (int i = 0; i < number_of_questions; i++)
    {
        int random_num;
        bool unique;
        do
        {
            random_num = 5 + rand() % (size - 5 + 1);
            unique = !isUnique(random_num, questions_array, i);
        } while (!unique);

        questions_array[i] = random_num;
    }
}

/*
 *---------------------------------------------------------------------*
 * Main function
 ? contains all main program functions
 */
int main()
{
    //? variables for profiles & list of commands
    profile_data save_data;
    List commands;

    //? populate the linked list w/ the commands in commands.csv
    populate(commands);

    //? Main Menu Loop
    while (true)
    {
        cout << "Please select an option listed below:\n";
        cout << "1. Game Rules\n2. Play Game\n3. Load Previous Game\n4. Add Command\n5. Remove Command\n6. Exit\n";

        int selection;
        cin >> selection;
        cout << endl
             << endl;

        //? Play Game --DONE
        if (selection == 2)
        {
            cout << "---------------Play Game---------------" << endl;

            //? local vars to grab userName & the number of questions
            //? Note: questionNumber is a local variable for every game
            int number_of_questions,
                questions_array[30];
            string nInput;
            srand(time(0));

            //? ask for user data
            if (save_data.user_name == "player_name")
            {
                cout << "Please enter your name: ";
                cin >> nInput;
                save_data.user_name = nInput;
            }
            //? load user data
            else
            {
                cout << "Loaded User Data: " << endl
                     << "Username: " << save_data.user_name << endl
                     << "Total Score: " << save_data.user_points << endl;
            }

            //? generate unique questions and populate the array
            generateQuestions(questions_array, number_of_questions, commands.size());

            //? main game-play loop
            int rounds = 0,
                random_layout,
                user_answer;

            while (rounds != number_of_questions)
            {
                cout << "---------------Round " << rounds + 1 << "---------------" << endl;
                //? create 3 nodes: 1 for the correct answer, and 2 for the decoy answers
                Node *c_answer = new Node(),
                     *d_answer1 = new Node(),
                     *d_answer2 = new Node();

                //? store data into the correct node & decoys
                c_answer = commands.search(questions_array[rounds]);
                d_answer1 = commands.search(questions_array[rounds] + 2);
                d_answer2 = commands.search(questions_array[rounds] - 2);

                random_layout = 1 + rand() % 3;

                if (random_layout == 1)
                {
                    cout << "Command: " << c_answer->get_commandName() << endl;
                    cout << "1. " << c_answer->get_commandDesc() << endl
                         << "2. " << d_answer1->get_commandDesc() << endl
                         << "3. " << d_answer2->get_commandDesc() << endl;

                    do
                    {
                        cout << "Answer [1-3]: ";
                        cin >> user_answer;
                    } while (user_answer < 1 || user_answer > 3);

                    if (user_answer == 1)
                    {
                        save_data.user_points++;
                        cout << "Correct! " << c_answer->get_commandName() << " = " << c_answer->get_commandDesc() << endl
                             << "Total Points: " << save_data.user_points << endl;
                    }
                    else
                    {
                        save_data.user_points--;
                        cout << "Incorrect! " << c_answer->get_commandName() << " = " << c_answer->get_commandDesc() << endl
                             << "Total Points: " << save_data.user_points << endl;
                    }
                }
                else if (random_layout == 2)
                {
                    cout << "Command: " << c_answer->get_commandName() << endl;
                    cout << "1. " << d_answer1->get_commandDesc() << endl
                         << "2. " << c_answer->get_commandDesc() << endl
                         << "3. " << d_answer2->get_commandDesc() << endl;

                    do
                    {
                        cout << "Answer [1-3]: ";
                        cin >> user_answer;
                    } while (user_answer < 1 || user_answer > 3);

                    if (user_answer == 2)
                    {
                        save_data.user_points++;
                        cout << "Correct! " << c_answer->get_commandName() << " = " << c_answer->get_commandDesc() << endl
                             << "Total Points: " << save_data.user_points << endl;
                    }
                    else
                    {
                        save_data.user_points--;
                        cout << "Incorrect! " << c_answer->get_commandName() << " = " << c_answer->get_commandDesc() << endl
                             << "Total Points: " << save_data.user_points << endl;
                    }
                }
                else if (random_layout == 3)
                {
                    //? display command name & 3 options
                    cout << "Command: " << c_answer->get_commandName() << endl;
                    cout << "1. " << d_answer2->get_commandDesc() << endl
                         << "2. " << d_answer1->get_commandDesc() << endl
                         << "3. " << c_answer->get_commandDesc() << endl;

                    do
                    {
                        cout << "Answer [1-3]: ";
                        cin >> user_answer;
                    } while (user_answer < 1 || user_answer > 3);

                    //? if correct
                    if (user_answer == 3)
                    {
                        save_data.user_points++;
                        cout << "Correct! " << c_answer->get_commandName() << " = " << c_answer->get_commandDesc() << endl
                             << "Total Points: " << save_data.user_points << endl;
                    }
                    //? if wrong
                    else
                    {
                        save_data.user_points--;
                        cout << "Incorrect! " << c_answer->get_commandName() << " = " << c_answer->get_commandDesc() << endl
                             << "Total Points: " << save_data.user_points << endl;
                    }
                }
                rounds++;
            }

            cout << "-------------------------------------" << endl;
            cout << endl
                 << endl;
        }

        //? Game Rules -- DONE
        else if (selection == 1)
        {
            cout << "---------------Display Game Rules---------------" << endl;

            //? Displays game rules & other program functions
            cout << "To play the game select \"2\" where you will be prompted" << endl
                 << "for your name & number of questions" << endl
                 << "Each question prompts the user with a specific linux" << endl
                 << "command wher you will then be able to choose from 3 " << endl
                 << "different options. Each correct answer yields a single" << endl
                 << "point and wrong answers remove a single point." << endl
                 << "One can also add & delete commands as needed" << endl;

            cout << "------------------------------------------------" << endl;
            cout << endl
                 << endl;
        }

        //? Load Previous Game -- DONE
        else if (selection == 3)
        {
            cout << "---------------Load Previous Game---------------" << endl;

            //? create input file stream & check file status
            ifstream myProfiles("/home/matthewhong/CPTS223/PA-1_Hong/profiles.csv");
            check(myProfiles);

            //? parse thru file contents
            bool target_found = false;
            string input,
                target;

            //? input target username we're searching for
            cout << "Enter profile name: ";
            cin.ignore();
            cin >> target;

            //? variables for parsing thru file
            string line,
                fString;

            while (getline(myProfiles, line))
            {
                stringstream stream(line);

                while (getline(stream, fString, ','))
                {
                    if (target == fString)
                    {
                        target_found = true;
                        //? set global variable username to fString [or target]
                        save_data.user_name = fString;

                        //? parse to the next item [the user's points]
                        getline(stream, fString, ',');

                        //? set global userpoints to fString [will be the # of points stored next to the user's name]
                        save_data.user_points = stoi(fString);
                    }
                }
            }

            //? display target info if found
            if (target_found == true)
            {
                cout << "Target found, displaying user info: " << endl
                     << "Username: " << save_data.user_name << endl
                     << "Total Score: " << save_data.user_points << endl;
            }
            else //? target wasn't found, return to main loop
            {
                cout << "Target wasn't found" << endl;
            }

            //? close file to ensure data isn't lost
            myProfiles.close();

            cout << "------------------------------------------------" << endl;
            cout << endl
                 << endl;
        }

        //? Add Commands -- DONE
        else if (selection == 4)
        {
            cout << "---------------Add commands---------------" << endl;
            //? create input variables to store user inputted data & bool var to
            //? keep track of if the user is in the loop or not
            string inputName, inputDesc, input, line;
            bool adding_items = true;

            //? Main loop to add commands
            while (adding_items == true)
            {
                //? input command name
                cout << "Enter command name: ";
                cin.ignore();
                cin >> inputName;

                //? input command description
                cout << "Enter command description: ";
                cin.ignore();
                getline(cin, inputDesc);

                line = inputName + "," + "\"" + inputDesc + "\"";
                cout << endl
                     << endl;

                //? insert user inputs into linked list
                commands.insert(line);

                //? display list to confirm insertion
                cout << "List Contents: " << endl
                     << endl;
                commands.display();
                cout << endl
                     << endl;

                //? user input y/n to stay in loop or exit
                do
                {
                    cout << "Continue adding commands? [y/n]";
                    cin >> input;

                    if (input == "y" || input == "n" || input == "yes" || input == "no")
                    {
                        break;
                    }
                } while (true);

                //? if input = 'n', break out of sub-loop & return to main menu
                if (input == "n" || input == "no")
                {
                    adding_items = false;
                }
            }
            cout << "size: " << commands.size() << endl;

            cout << "------------------------------------------" << endl;
            cout << endl
                 << endl;
        }

        //? Remove Commands -- DONE
        else if (selection == 5)
        {
            cout << "---------------Remove Commands---------------" << endl;
            //? create input vars for the target we're searching for & the y/n input
            string target_command, input;
            bool removing_items = true,
                 removed = false;

            //? main loop to remove commands
            while (removing_items == true)
            {
                //? display contents of list
                cout << "List Contents: " << endl
                     << endl;

                commands.display();

                cout << endl
                     << endl;

                //? get command name
                cout << "Enter search target's name: ";
                cin.ignore();
                cin >> target_command;

                //? pass target name to remove function in list
                removed = commands.remove(target_command);

                //? if the element was removed & we are still in the loop of removing items
                if (removed == true && removing_items == true)
                {
                    //? safety loop to ensure input values are y, Y, n, N
                    do
                    {
                        cout << "Continue removing commands? [y/n]: ";
                        cin >> input;

                        if (input == "y" || input == "n" || input == "Y" || input == "N")
                        {
                            break;
                        }
                    } while (true);

                    //? if the user input is n/N, break out and return to main loop
                    if (input == "n" || input == "N")
                    {
                        removing_items = false;
                    }
                }

                cout << "List Contents: " << endl
                     << endl;

                commands.display();
            }

            cout << "size: " << commands.size() << endl;
            cout << "---------------------------------------------" << endl;
            cout << endl
                 << endl;
        }

        //? Exit -- DONE
        else if (selection == 6)
        {
            cout << "---------------Exit Program---------------" << endl;

            //? grab current date/time/year
            auto now = chrono::system_clock::now();
            time_t cTime = chrono::system_clock::to_time_t(now);

            //? display when the user exited the program
            cout << "User Exited Program on " << ctime(&cTime) << endl;

            //? overwrite the commands file to update the list w/ the added/removed commands during the program's run-time
            commands.overwrite();

            //? open profiles.csv & save data
            ofstream myProfiles("/home/matthewhong/CPTS223/PA-1_Hong/profiles.csv", ios::app);
            check(myProfiles);

            myProfiles << save_data.user_name << "," << save_data.user_points << endl;

            myProfiles.close();
            //? console messages showing data was saved
            cout << "Commands saved to commands.csv" << endl;
            cout << "Player data saved to profiles.csv" << endl;

            cout << "------------------------------------------" << endl;
            cout << endl
                 << endl;

            return 0;
        }
    }
}
