//Author: Bomen Derick
//Driver program to test the r-tree algorithm through available options(Insert, Delete, Search, Traverse, Moves)

#include <iostream>
#include <stdlib.h>
#include "rtree.h"
#include <ctype.h>

#define abs(a) (-a)? a : -(a)
using namespace std;
rNode *tree = nullptr; //Global variable to represent root of the r-tree
typedef enum Options //Enumeration of available options
{
    Insert_a_node = 1,
    Delete_a_node,
    search_a_node,
    traverse_R_tree,
    move_R_nodes,
    Exit
}Options;
//Utility function to return an enumeration option
const char* option(Options n)
{
    switch(static_cast<int>(n))
    {
        case 1:
            return "Insert_a_point";
        case 2:
            return "Delete_a_point";
        case 3:
            return "Search_a_point";
        case 4:
            return "Traverse_R_tree";
        case 5:
            return "Move_R_points";
        case 6:
            return "Exit";
        default:
            break;
    }
    return " ";
}

//Display list of available options
void displayOptions()
{
    cout<<endl<<".............................Available Options to interact with the Algorithm......................"<<endl<<endl;
    for (int i = 1; i <= Exit; ++i) {
        auto n = (Options) i;
        cout<<i<<". "<<option(n)<<endl;
    }
    cout<<endl;
}

//function that listen to the user chosen option and return to the caller
int chooseOption()
{
    int p;
    char c = 0;
    cout<<"choose an option number (eg 1 for insertion): "; //taking an ascii character
    cin>>c;
    p = c - '0'; //converting the ascii character to integer and return to the caller
    return p;
}

//execute the insert option to insert node. A wrapper over insertRNode()
void exeInsert(int k)
{
    int n = 0;
    //in case of multiple nodes to be inserted
    cout<<"Enter the number of points to insert: ";
    cin>>n;
    for (int i = 1; i <= n ; ++i)
    {
        double a[k];
        cout<<"Entering point number "<<i<<endl;
        for (int j = 0; j < k; ++j)
        {
            cout<<"\tEnter value of index "<<j<<": "; //collect points from the user
            cin>>a[j]; //store points in the array
        }
        int x = 0;
        cout<<"\tEnter point's name (An Integer): ";
        cin>>x;
        Node *node = newNode(a, x, k); //allocate memory through newRNode() to insert the node
        tree = insertNode(tree, node, k); //insert node and store in global root
    }
    cout<<endl<<endl;
}

//execute the delete option to delete a node. A wrapper over deleteRNode()
void exeDelete(int k)
{
    double a[k];
    cout<<"Enter point to delete: "<<endl;
    for (int i = 0; i < k; ++i)
    {
        cout<<"\tEnter value of index "<<i<<": ";
        cin>>a[i];
    }
    char x;
    cout<<"\tEnter point's name(An Integer): ";
    cin>>x;
    Node *node = newNode(a, x, k); //allocate memory to hold user input so as to trace user input from the tree
    tree = deleteNode(tree, node, k); //delete node and return resulting nodes in global root
    if (tree == nullptr)
        cout<<"R-Tree is still empty!!";
    cout<<endl<<endl;
}

//execute search option to search for a node. A wrapper over searchRNode()
void exeSearch(int k)
{
    double a[k];
    cout<<"Enter point to search: "<<endl;
    for (int i = 0; i < k; ++i)
    {
        cout<<"\tEnter value of index "<<i<<": "; //collect point to be search
        cin>>a[i]; //store point to be search
    }
    char x;
    cout<<"\tEnter point's name(An Integer): ";
    cin>>x;
    Node *node = newNode(a, x, k); //allocate node to be search in the tree
    //Respond to the search request..
    if(searchNode(tree, node, k))
    {
        cout<<"Point Found at position: "<<"("; //Print "Node Found!!!!" message in case the node(node) is found
        for (int i = 0; i < k; ++i) {
            cout<<" "<<node->mbb[i];
        }
        cout<<")"<<endl<<endl;
    }
    else
        cout<<"Point NOT Found!!!!"<<endl<<endl; //Print "Node NOT Found!!!!" message in case the node is not found
}

//execute traverse option to traverse an r-tree. A wrapper over traverseR()
void exeTraverse(int k)
{
    traverseNodes(tree, k);
    cout<<endl<<endl;
}

//Displacement of nodes within the r-tree
void exeMoves(int k)
{
    double t;
    cout<<"Enter time interval to move nodes: ";
    cin>>t;
    tree = moveNodes(tree, t, k);
    if (tree == nullptr)
        cout<<"R-Tree is still empty! no points to be move!"<<endl<<endl;
}

//default function to be executed in case of no valid option
void defaultAction()
{
    cout<<"Please choose a valid option!!"<<endl<<endl;
}

//driver function to test available functions on the available r-tree algorithm
int main()
{
    char c;
    int d;
    //Get the dimension to work with
    cout<<"Program to test R-Tree algorithm. \nNOTE! For now the program is efficient only with 2D or 3D points!!!!\n";
    cout<<"Enter the dimension of the workspace (Positive integer greater than zero (0)): ";
    cin>>c;
    d = c - '0';    //converting to integer
    d = abs(d); //return a positive dimension in case a negative dimension was accidentally entered

    //Ensuring we are working with a dimension greater than zero (0)
    //Keep asking the dimension when the dimension entered is different from the specified dimension
    while (d == 0 || d > 3)
    {
        cout<<"Enter the Dimension.. MUST be greater than zero(0)..."<<endl;
        cin>>c;
        d = c - '0';
        d = abs(d);
        if (d == 1 || d == 2 || d == 3)
            break;
    }
    displayOptions(); //display available options to be use
    //keep asking an option unless the exit option is entered
    cout<<endl;
    while (true)
    {
        Options choice = Delete_a_node; //local variable to define loop break
        //execute options depending on their numbering on the console returned by chooseOption()
        switch (chooseOption()) {
            case 1:
                exeInsert(d);
                displayOptions();
                break;
            case 2:
                exeDelete(d);
                displayOptions();
                break;
            case 3:
                exeSearch(d);
                displayOptions();
                break;
            case 4:
                exeTraverse(d);
                displayOptions();
                break;
            case 5:
                exeMoves(d);
                displayOptions();
                break;
            case 6:
                choice = Exit;
                break;
            default:
                defaultAction();
                displayOptions();
                break;
        }
        if (choice == Exit) //break out of the loop if Exit option is chosen
            break;
    }


    return 0;
}


