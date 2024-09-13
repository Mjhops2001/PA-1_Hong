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

        if (selection == 2) //* Play Game
        {
            //* local vars to grab userName & the number of questions
            //* Note: questionNumber is a local variable for every game
            int qNumber;
            string nInput; 

            //* grab player name from input & store it in global userName 
            //* or print loaded user data grabbed from menu option 3
            if(userName == "player_name"){
                cout << "Please enter your name: ";  
                cin >> nInput; 
                userName = nInput; 
            }else{
                cout << "Loaded User Data: " << endl
                     << "Username: " << userName << endl
                     << "Total Score: " << userPoints << endl; 
            }
            

            //* grab the number of questions from user input [between 5 - 30]
            while(qNumber < 5 || qNumber > 30){
                cout << "Please select how many questions you would like to " << endl
                 << "be asked [5 - 30]: "; 

                 cin >> qNumber; 
            }
            
            cout << "User selected " << qNumber << " questions." << endl;
        }
        else if (selection == 1) //* Game Rules
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
        else if (selection == 3) //* Load Previous Game
        {
            cout << "--------Load Previous Game--------" << endl;
            //* open file containing the saved profiles
            ifstream myProfiles("/home/matthewhong/CPTS223/PA-1_Hong/profiles.csv"); 
            
            //* necessary variables: 
            string target; 

            //* confirm if file is open
            if(myProfiles.is_open()){
                cout << "File is open, continuing operations." << endl; 
            }else{
                cout << "File failed to open, terminating." << endl;
            }

            //* grab name to search for
            cout << "Enter profile name: "; 
            cin.ignore(); 
            cin >> target; 

        
            //* parse thru file
            string line, fString; 
            while(getline(myProfiles, line)){
                stringstream stream(line); 

                while(getline(stream, fString, ',')){
                    if(target == fString){
                        //* set global username to fString [or target]
                        userName = fString; 

                        //* parse to the next item on the current line
                        getline(stream, fString, ','); 

                        //* set global userpoints to fString [will be the # of points stored next to the user's name]
                        userPoints = stoi(fString); 
                    }
                }

                if(userName == "player_name"){
                    cout << "Target name wasn't found." << endl; 
                }else{
                    cout << "Target found, displaying user info: " << endl
                         << "Username: " << userName << endl
                         << "Total Score: " << userPoints << endl; 
                }  
            }
            
            myProfiles.close(); 

            cout << "----------------------------------" << endl; 
            cout << endl << endl; 
        }
        else if (selection == 4) //* Add Command
        {
            cout << "--------Add Command--------" << endl;
            //* create output file variable
            ofstream commands("/home/matthewhong/CPTS223/PA-1_Hong/commands.csv", ios::app); 

            //* create variable to give user control over looping the adding process
            bool adding_items = true; 

            //* create input variables to store user inputted data
            string inputName, inputDesc, input; 


            //* check if file is open
            if(commands.is_open()){
                cout << "File is open, continuing operations." << endl; 
            }else{
                cout << "File failed to open, terminating." << endl;
            }
            
            
            //* Main loop to add commands
            while(adding_items == true){
                //* grab command name
                cout << "Enter command name: ";
                cin.ignore();  
                cin >> inputName;  


                //* grab command description: 
                cout << "Enter command description: ";
                cin.ignore();
                getline(cin, inputDesc); 


                //* write the previous inputs to the commands.csv file
                commands << inputName << ",\"" << inputDesc << "\"" << endl;  
                

                //* input vars for this should only be 'y' or 'n'
                do{
                    cout << "Continue adding commands? [y/n]"; 
                    cin >> input; 

                    if(input == "y"|| input == "n" || input == "yes" || input == "no"){
                        break;
                    }
                } while (true);
                

                //* if the input is equal to n or no, terminate the loop and go back
                //* to the main menu loop
                if(input == "n" || input == "no"){
                    adding_items = false; 
                }
            }
            
            //* close file to safely store contents added
            commands.close();
            cout << "---------------------------" << endl; 
            cout << endl << endl; 

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

