#include <iostream>

using namespace std;

struct node{

    char symbol;

    //
    node *right;
    node *left;
    node *up;
    node *down;

};

void createList(node *&);
void printList(node *&);

int main(){

    node *head = nullptr;

    createList(head);

    return 0;

}

void createList(node *&){

}