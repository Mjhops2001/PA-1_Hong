/*
ADVANTAGES/DISADVANTAGES LINKED LIST

ADVANTAGES/DISADVANTAGES ARRAY
*/
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
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
    int user_points = -1;
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
 * Main function
 ? contains all main program functions
 */
int main()
{
    //? variables for initializing
    profile_data save_data;
    List commands;

    //? for testing list
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

        //? Play Game
        if (selection == 2)
        {
            cout << "---------------Play Game---------------" << endl;

            //? local vars to grab userName & the number of questions
            //? Note: questionNumber is a local variable for every game
            int qNumber;
            string nInput;

            //* grab player name from input & store it in global userName
            //* or print loaded user data grabbed from menu option 3
            /* if (userName == "player_name")
            {
                cout << "Please enter your name: ";
                cin >> nInput;
                userName = nInput;
            }
            else
            {
                cout << "Loaded User Data: " << endl
                     << "Username: " << userName << endl
                     << "Total Score: " << userPoints << endl;
            }

            //* grab the number of questions from user input [between 5 - 30]
            while (qNumber < 5 || qNumber > 30)
            {
                cout << "Please select how many questions you would like to " << endl
                     << "be asked [5 - 30]: ";

                cin >> qNumber;
            }

            cout << "User selected " << qNumber << " questions." << endl;
            */
            cout << "---------------------------------------" << endl;
            cout << endl
                 << endl;
        }

        //? Game Rules -- Done
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

        //? Load Previous Game
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

        //? Add Commands --will have to re-do, only alterations should be made to the linked list, not the actual .csv in this function
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

            cout << "------------------------------------------" << endl;
            cout << endl
                 << endl;
        }

        //? Remove Commands
        else if (selection == 5)
        {
            cout << "---------------Remove Commands---------------" << endl;

            //? create input vars for the target we're searching for & the y/n input
            string target_command, input;
            bool removing_items = true;

            //? display current contents of our list:
            while (removing_items == true)
            {

                cout << "List Contents: " << endl
                     << endl;
                commands.display();
                cout << endl
                     << endl;

                //? get command name
                cout << "Enter search target's name: ";
                cin.ignore();
                cin >> target_command;

                //! commands.remove(input);

                //* display if the command was found or not
                //? and ask if the user wants to do the removal search again
                //? user input y/n to stay in loop or exit
                do
                {
                    cout << "Command name not found, search again? [y/n]: ";
                    cin >> input;

                    if (input == "y" || input == "n" || input == "yes" || input == "no")
                    {
                        break;
                    }
                } while (true);
            }
            cout << "---------------------------------------------" << endl;
            cout << endl
                 << endl;
        }

        //? Exit --Done
        else if (selection == 6)
        {
            cout << "---------------Exit Program---------------" << endl;

            //? grab current date/time/year
            auto now = chrono::system_clock::now();
            time_t cTime = chrono::system_clock::to_time_t(now);

            //? display when the user exited the program
            cout << "User Exited Program on " << ctime(&cTime) << endl;

            //? overwrite the commands file to update the insertions added
            commands.overwrite();

            cout << "------------------------------------------" << endl;
            cout << endl
                 << endl;

            return 0;
        }
    }
}
