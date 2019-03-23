//Shreyas Raj Singh sxs170100 CS 1337.007 Project 3
#include <iostream>
#include <fstream>

using namespace std;

//basic outline of the nodes in the linked list
struct node{

    //store the symbol in the node
    char symbol;

    //connecting nodes to create the structure
    node *right;
    node *left;
    node *up;
    node *down;

};

//function to create the grid on which the user will draw
void createGrid(node *&);
//function to print the grid!
void printGrid(node *);
//function to delete the grid
void deleteGrid(node *);
//function to take in input and process commands respectively
void Input(fstream &, node *);
//function to make changes to the output file
void OutputTranslate(fstream &, node *);
//function to draw north
void NorthDraw(node *&, bool, bool, int);
//function to draw north
void SouthDraw(node *&, bool, bool, int);
//function to draw east
void EastDraw(node *&, bool, bool, int);
//function to draw east
void WestDraw(node *&, bool, bool, int);


int main(){

    //create a file input object
    fstream inputFile;

    //create the head pointer and assign it to nullptr
    node *head = new node;

    //create the grid
    createGrid(head);

    //take in input
    Input(inputFile, head);

    //delete the linked list structure
    deleteGrid(head);

    return 0;

}

void createGrid(node *&head){

    //Assign a temp pointer to the head node
    node *temp = head;

    //Create the first row of 50 nodes
    //loop 49 times since the first node is already there
    for(int i = 0; i < 50; i++){
        temp->symbol = ' ';
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
            for(int j = 0; j < 50 ; j++){
                temp2->symbol = ' ';
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
        //and a newline(s)
        cout << endl;
        cout << endl;
        cout << endl;
    }

}

void deleteGrid(node *head){

    if(head->down != nullptr){
        //assign the location of the node under head to a temporary pointer
        node *temp = head->down;
        //free the entire row
        while(head->right != nullptr){
            head = head->right;
            node *deleteNode = head->left;
            free(deleteNode);
        }
        //and the last member of the row
        free(head);

        //call the same function using temp
        deleteGrid(temp);
    }
    else{
        //delete the last row
        while(head->right != nullptr){
            head = head->right;
            node *deleteNode = head->left;
            free(deleteNode);
        }
        //and the last member of the row
        free(head);
    }
}

void Input(fstream &inputFile, node *head){
    //Assign a temp pointer to the head node
    node *temp = head;
    //open the command file
    inputFile.open("commands.txt");

    //create output fstream object
    fstream outputFile;

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
        int distance = 0;

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
                    if(command == "1"){
                        penStatus = false;
                    }
                    else if(command == "2"){
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
                case 3: {//check for distance
                    //make sure distance is positive
                    int i = 0;
                    while (i < command.length()) {
                        if (!isdigit(command[i])) {
                            validCommand = false;
                            break;
                        }
                        i++;
                    }
                    if(validCommand)
                        distance = stoi(command);
                    break;
                }
                case 4: //check for bold status
                    if(command == "B"){
                        boldStatus = true;
                    }
                    else if(command == "P"){
                        printStatus = true;
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
                default: cout << "Error!" << endl;
                         break;
            }

        }
        //make sure the input is valid and continue the loop if its not
        if(!validCommand){
            cout << "invalid command" << endl;
            continue;
        }

        //After all the commands are acquired call the function for the respective direction
        switch(direction){
            case 'N':
                NorthDraw(temp, penStatus, boldStatus, distance);
                break;
            case 'S':
                SouthDraw(temp, penStatus, boldStatus, distance);
                break;
            case 'E':
                EastDraw(temp, penStatus, boldStatus, distance);
                break;
            case 'W':
                WestDraw(temp, penStatus, boldStatus, distance);
                break;
            default: break;
        }

        //make changes to the output file based on the changes to the linked list
        OutputTranslate(outputFile, head);

        //print if ordered
        if(printStatus){
            printGrid(head);
        }

    }

    //close the input file
    inputFile.close();
}

void OutputTranslate(fstream &outputFile, node *head){
    node *head_ref = head;
    node *head_down = head;

    //open the outputfile
    outputFile.open("paint.txt", ios :: in | ios :: out );

    //for each row
    for(int row = 0; row < 50; row++){
        //and for each column
        for(int column = 0; column < 50; column++){
            outputFile << head_ref->symbol;
            head_ref = head_ref->right;
        }
        //assign head_ref to head_down
        head_ref = head_down->down;
        //move head_down a step down
        head_down = head_down->down;
        //go to newline
        if(row != 49)
            outputFile << endl;
    }
    //close the file
    outputFile.close();

}

void NorthDraw(node *&head_ref, bool penStatus, bool boldStatus, int distance){
    node *temp = head_ref;

    //check for out of bounds
    for(int i = 0; i < distance; i++){
        //if the command causes an out of bounds error, return back to the input function
        if(temp->up == nullptr && (i < distance)){
            cout << "out of bounds" << endl;
            return;
        }
        //otherwise keep going up
        temp = temp->up;
    }

    //assign temp to head once again
    temp = head_ref;

    //loop for the distance
    for(int i = 0; i < distance; i++){
        //move the pointer up
        temp = temp->up;

        //check for precedence
        if(temp->symbol == '#'){
            continue;
        }

        if(penStatus && boldStatus){
            temp->symbol = '#';
        }
        else if(penStatus){
            temp->symbol = '*';
        }
    }

    //assign head a new position from which we will resume the next command
    head_ref = temp;

}

void SouthDraw(node *&head_ref, bool penStatus, bool boldStatus, int distance){
    node *temp = head_ref;

    //check for out of bounds
    for(int i = 0; i < distance; i++){
        //if the command causes an out of bounds error, return back to the input function
        if(temp->down == nullptr && (i < distance)){
            cout << "out of bounds" << endl;
            return;
        }
        //otherwise keep going down
        temp = temp->down;
    }

    //assign temp to head once again
    temp = head_ref;

    //loop for the distance
    for(int i = 0; i < distance; i++){
        //move the pointer left
        temp = temp->down;

        //check for precedence
        if(temp->symbol == '#'){
            continue;
        }

        if(penStatus && boldStatus){
            temp->symbol = '#';
        }
        else if(penStatus){
            temp->symbol = '*';
        }
    }

    //assign head a new position from which we will resume the next command
    head_ref = temp;
}

void EastDraw(node *&head_ref, bool penStatus, bool boldStatus, int distance){
    node *temp = head_ref;

    //check for out of bounds
    for(int i = 0; i < distance; i++){
        //if the command causes an out of bounds error, return back to the input function
        if(temp->right == nullptr && (i < distance)){
            cout << "out of bounds" << endl;
            return;
        }
        //otherwise keep going right
        temp = temp->right;
    }

    //assign temp to head once again
    temp = head_ref;

    //loop for the distance
    for(int i = 0; i < distance; i++){
        //move the pointer right
        temp = temp->right;

        //check for precedence
        if(temp->symbol == '#'){
            continue;
        }

        if(penStatus && boldStatus){
            temp->symbol = '#';
        }
        else if(penStatus){
            temp->symbol = '*';
        }
    }

    //assign head a new position from which we will resume the next command
    head_ref = temp;
}

void WestDraw(node *&head_ref, bool penStatus, bool boldStatus, int distance){
    node *temp = head_ref;

    //check for out of bounds
    for(int i = 0; i < distance; i++){
        //if the command causes an out of bounds error, return back to the input function
        if(temp->left == nullptr && (i < distance)){
            cout << "out of bounds" << endl;
            return;
        }
        //otherwise keep going left
        temp = temp->left;
    }

    //assign temp to head once again
    temp = head_ref;

    //loop for the distance
    for(int i = 0; i < distance; i++){
        //move the pointer left
        temp = temp->left;

        //check for precedence
        if(temp->symbol == '#'){
            continue;
        }

        if(penStatus && boldStatus){
            temp->symbol = '#';
        }
        else if(penStatus){
            temp->symbol = '*';
        }
    }

    //assign head a new position from which we will resume the next command
    head_ref = temp;
}


