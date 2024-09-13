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

//void populate(Linked_List<string, string> *mainlist) // Read CSV and input data into a linked list
//{
    // ====================
    // ======= code =======
    // ====================
//}

int main()
{
    // variables for the game: 
    int userPoints = 0; 
    string userName = "player_name";


    while (true)
    {
        cout << "Please select an option listed below:\n";
        cout << "1. Game Rules\n2. Play Game\n3. Load Previous Game\n4. Add Command\n5. Remove Command\n6. Exit\n";

        int selection;
        cin >> selection;

        if (selection == 2) // Play Game
        {
            // local vars to grab userName & the number of questions
            // note: number of questions is always local to the current game being played. 
            int questionNumber;
            string nameSelect; 

            // grab player name & store it in global var 'userName'
            cout << "Please enter your name: ";  

            cin >> nameSelect; 
            userName = nameSelect; 

            // grab the amount of questions being asked & loops 
            // until a value between 5 & 30 is obtained
            while(questionNumber < 5 || questionNumber > 30){
                cout << "Please select how many questions you would like to " << endl
                 << "be asked [5 - 30]: "; 

                 cin >> questionNumber; 
            }
            
            cout << endl << endl; 
            cout << "User selected " << nameSelect << " as their name." << endl
                 << nameSelect << " selected " << questionNumber << " questions." << endl
                 << endl; 
        }
        else if (selection == 1) // Game Rules
        {
            // game rules & other functions of program
            cout << "To play the game select \"2\" where you will be prompted" << endl
                 << "for your name & number of questions" << endl 
                 << "Each question prompts the user with a specific linux" << endl
                 << "command wher you will then be able to choose from 3 " << endl
                 << "different options. Each correct answer yields a single" << endl
                 << "point and wrong answers remove a single point." << endl
                 << "One can also add & delete commands as needed" << endl; 
        }
        else if (selection == 3) // Load Previous Game
        {
            ifstream myProfiles("/home/mattthewhong/CPTS223/PA-1_Hong/profiles.csv"); 

            

            if(!myProfiles.is_open()){
                cout << "File wasn't opened" << endl; 
            }else{
                cout << "File is open, continuing operations." << endl; 
            }

            string line, word; 
            while(getline(myProfiles, line)){
                stringstream s(line); 

                while(getline(s, word, ',')){
                    cout << word << " "; 
                }

                cout << endl; 
            }
        }
        else if (selection == 4) // Add Command
        {
            // create input file variable
            


        }
        else if (selection == 5) // Remove Command
        {
            // =====================
            // ===== some code =====
            // =====================
        }
        else if (selection == 6) // Exit
        {
            //grab current date/time/year
            auto now = chrono::system_clock::now();
            time_t cTime = chrono::system_clock::to_time_t(now);

            //display when the user exited the program
            cout << "User Exited Program on " << ctime(&cTime) << endl; 
            return 0;
        }
    }
}

