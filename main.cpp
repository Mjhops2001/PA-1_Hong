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
#include "linkedlist.cpp"

using namespace std;

struct profile_data{
    string user_name = "player_name"; 
    int user_points = -1;
};

/*
 * populate()
 ? reads commands.csv & inputs data into linked list
 */
// void populate(Linked_List<string, string> *mainlist) // Read CSV and input data into a linked list
//{
//  ====================
//  ======= code =======
//  ====================
//}

/*
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

int main()
{
    //? variables for initializing 
    profile_data save_data; 

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

            //* local vars to grab userName & the number of questions
            //* Note: questionNumber is a local variable for every game
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
            }else //? target wasn't found, return to main loop
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
            //? create output file & check status
            ofstream commands("/home/matthewhong/CPTS223/PA-1_Hong/commands.csv", ios::app);
            check(commands);

            //? create input variables to store user inputted data
            string inputName, inputDesc, input;

            //? Main loop to add commands
            bool adding_items = true;
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

                //? write command name & desc. to commands.csv & console to
                //? confirm it was added
                commands << inputName << ",\"" << inputDesc << "\"" << endl;
                cout << "Added command: " << inputName << endl;

                //? input y/n to continue adding commands or return to main menu
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

            //? close file to ensure no loss of data
            commands.close();

            cout << "------------------------------------------" << endl;
            cout << endl
                 << endl;
        }

        //? Remove Commands
        else if (selection == 5)
        {
            cout << "---------------Remove Commands---------------" << endl;

            //? Might need to tinker w/ linked list, load all the elements
            //? in commands.csv into said list then remove w/ linked list
            //? functions and then re-write the edited list to
            //? commands.csv

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

            cout << "------------------------------------------" << endl;
            cout << endl
                 << endl;

            return 0;
        }
    }
}
