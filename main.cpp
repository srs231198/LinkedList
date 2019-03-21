#include <iostream>
#include <fstream>

using namespace std;

struct node{

    char symbol;

    //connecting nodes to create the structure
    node *right;
    node *left;
    node *up;
    node *down;

};

//function to create the grid on which the user will draw
void createGrid(node *&);
//function to take in input and process comands respectively
void Input(fstream &);
//function to print the grid!
void printGrid(node *);
//function to delete the grid
void deleteGrid(node *);
//function to draw north
void NorthDraw(node *, bool, bool, bool, int);

int main(){

    //create a file input object
    fstream inputFile;

    Input(inputFile);

    //create the head pointer and assign it to nullptr
    node *head = new node;


    createGrid(head);

    printGrid(head);

    return 0;

}

void createGrid(node *&head){

    //Assign a temp pointer to the head node
    node *temp = head;

    //Create the first row of 50 nodes
    //loop 49 times since the first node is already there
    for(int i = 0; i < 50; i++){
        //create a new node
        node *newNode = new node;
        newNode->right = nullptr;
        newNode->left = nullptr;
        //link the temp node to newNode
        temp->right = newNode;
        newNode->left = temp;
        //chenge temp's position
        temp = temp->right;
    }

    //create a temporary pointer to hold head's location
    node *temp1 = head;

    //for the next 49 rows
    for(int i = 1; i < 50; i++){
        node *newNode1 = new node;
        node *temp2 = newNode1;
        //and the columns on each row
            for(int i = 0; i < 50 ; i++){
                //create new node
                node *newNode2 = new node;
                //link the nodes to the appropriate places
                temp2->up = temp1;
                temp1->down = temp2;
                temp2->right = newNode2;
                newNode2->left = temp2;
                //assign the pointers to new positions
                temp1 = temp1->right;
                temp2 = temp2->right;
            }
        //assign temp1 to a new position
        temp1 = newNode1;
    }

}

void printGrid(node *head){

    if(head->down != nullptr){
        //assign the location of the node under head to a temporary pointer
        node *temp = head->down;
        //print out the row
        while(head->right != nullptr){
            cout << head->symbol;
            head = head->right;
        }
        //and a newline
        cout << endl;

        //call the same function using temp
        printGrid(temp);
    }
    else{
        //print out the last row
        while(head->right != nullptr){
            cout << head->symbol;
            head = head->right;
        }
        //and a newline
        cout << endl;
    }

}

void deleteGrid(node *head){

}

void Input(fstream &inputFile){
    //open the command file
    inputFile.open("commands.txt");

    //check for the proper opening of the file
    if(!inputFile.good()){
        exit(0);
    }

    //string object to store the line commmand
    string text, command;



    //loop to separate commands into separate inputs
    while(inputFile >> text){
        //flag for individual command
        int counter = 0;
        //variables to store the individual commands
        bool penStatus = false;
        bool boldStatus = false;
        bool printStatus = false;
        char direction = 'Q';
        int distance;

        //variable to store the index of ","
        unsigned long index = 0;

        //flag to make sure input is valid
        bool validCommand = true;

        //while the text still has some input left
        while(text.length() > 0){
            //loop until you find ","
            for(index = 0; index < text.length(); index++){
                //if we reach the end of the input
                if(text.find(',') == -1){
                    counter++;
                    command = text;
                    text= "";
                    break;
                }
                //when "," is found
                if(text.at(index) == ','){
                    //increment counter, modify the string(s) and then break
                    counter++;
                    command = text.substr(0, index);
                    text = text.substr(index + 1);
                    break;
                }
            }

            switch(counter){
                case 1: //check for pen status
                    if(stoi(command) == 1){
                        penStatus = false;
                    }
                    else if(stoi(command) == 2){
                        penStatus = true;
                    }
                    else{
                        validCommand = false;
                    }
                    break;
                case 2:  //check for direction
                    if(command == "N"){
                        direction = 'N';
                    }
                    else if(command == "S"){
                        direction = 'S';
                    }
                    else if(command == "E"){
                        direction = 'E';
                    }
                    else if(command == "W"){
                        direction = 'W';
                    }
                    else{
                        validCommand = false;
                    }
                    break;
                case 3: //check for distance
                    distance = stoi(command);
                    if(distance < 0){
                        validCommand = false;
                    }
                    break;
                case 4: //check for bold status
                    if(command == "B"){
                        boldStatus = true;
                    }
                    else{
                        validCommand = false;
                    }
                    break;
                case 5: //check for print
                    if(command == "P"){
                        printStatus = true;
                    }
                    else{
                        validCommand = false;
                    }
                    break;
            }

        }
        //make sure the input is valid and continue the loop if its not
        if(!validCommand){
            cout << "invalid command" << endl;
            continue;
        }

        //after all the commands are acquired call the function for the respective direction
        //INCOMPLETE CODE BITCH
        switch(direction){
            case 'N':
                break;
            default: break;
        }

    }


    inputFile.close();
}
