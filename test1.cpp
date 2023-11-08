
#include <iostream>
#include "rtree.h"
#include <chrono>

#define DIMENSION 3     //working dimension
#define INPUT_SIZE 10000  //input size, number of points to be generated and insert
#define RANDOM_MAX 99999999   //define maximum random value to work with
#define RAND_PT() (rand()/(int) RANDOM_MAX)   //define random function to generate points
using namespace std;
using namespace std::chrono;

int main(){
    //usefull local variables
    rNode *rootNode = nullptr;  //initial root of the tree

    double b[INPUT_SIZE][DIMENSION]; //two dimensional array to hold generated points
    Node nodes[INPUT_SIZE];     //array to store generated nodes
    //generate nodes with respect to the given input size
    //srand(time(0));   //to change the random points every time it runs
    for (int i = 0; i < INPUT_SIZE; ++i) {
        double c[DIMENSION];
        for (int j = 0; j < DIMENSION; ++j) {
            b[i][j] = RAND_PT();    //generate random points
            c[j] = b[i][j];
        }
        nodes[i] = *(newNode(c, i, DIMENSION));     //generate nodes with generated points for insertion
    }

    for (int k = 0; k < INPUT_SIZE; ++k) {
        if (k%10 == 0)
            cout<<endl;
        cout<<k<<"(";
        for (int i = 0; i < DIMENSION; ++i) {
            cout<<nodes[k].mbb[i]<<" ";
        }
        cout<<") ";
    }


    for (auto & node : nodes) {
        rootNode = insertNode(rootNode, &node, DIMENSION); //inserting generated nodes
    }


    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    for (auto & node : nodes) {
        searchNode(rootNode, &node, DIMENSION); //inserting generated nodes
    }
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    auto duration1 = duration_cast<microseconds>( t2 - t1 ).count();
    cout<<"\t"<<duration1;
    cout<<endl<<endl;
    //rootNode = deleteNode(rootNode, &nodes[0], DIMENSION);  //deleting a node
    //rootNode = moveNodes(rootNode, 2.1, DIMENSION);     //moving nodes to different positions in the tree
    /*cout<<"When nodes are static......../n";
    traverseNodes(rootNode, DIMENSION);     //visiting and displaying nodes' data
    rootNode = moveNodes(rootNode, 2.5, DIMENSION);
    cout<<endl<<endl<<"When nodes are static......../n";
    traverseNodes(rootNode, DIMENSION); */
    /*if (searchNode(rootNode, &nodes[6], DIMENSION)) {   //search for and return an appropriate flag
        cout<<"Node found"<<endl;
    } else
        cout<<"Node not found"<<endl;
    Node *node1 = nullptr;
    node1 = searchNodePosition(rootNode, &nodes[6], DIMENSION);     //search for the current position of a node

    for (int l = 0; l < DIMENSION; ++l) {
        cout<<node1->mbb[l]<<" ";       //display the current position
    }*/
    return 0;
}