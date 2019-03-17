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
//void printGrid(node *&);
//function to delete the grid
//void deleteGrid(node *&);

int main(){

    //create a file input object
    fstream inputFile;

    Input(inputFile);

    //create the head pointer and assign it to nullptr
    node *head = new node;


    createGrid(head);

//    printGrid(head);

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

    //for the next 49 nodes
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
                //assign the pointers to new ositions
                temp1 = temp1->right;
                temp2 = temp2->right;
            }
        //assign temp1 to a new position
        temp1 = newNode1;
    }

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

    //string objects to store the individual commands
    string penStatus, direction, distancs, boldOrNot;

    while(inputFile >> text){



    }
}


