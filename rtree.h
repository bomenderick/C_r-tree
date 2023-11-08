//Author: Bomen
//header file for the r-tree algorithm

#ifndef UNTITLED1_RTREE_H_H
#define UNTITLED1_RTREE_H_H

#endif //UNTITLED1_RTREE_H_H

//structure for a point or an object
typedef struct Node
{
    double *mbb;    //minimum bounding box of point
    int name;   //point representation
}Node;

//structure for an internal node
typedef struct rNode
{
    Node *bb;   //bounding box of an internal node (with bottom left and top right points)
    Node *leafNode;     //placeholder to store points or leaf nodes
    int numberOfNodes;  //leaf nodes counter
    struct rNode *nextNode; //pointer to next internal node
}rNode;

Node *newNode(double mbb[], int name, int dimension);   //to create a new node form a given point
rNode *newRNode(int dimension);   //to create a new internal node given a dimension
bool isInRNode(rNode*, Node*, int dimension);     //to determine if a node belong to internal node in a given dimension
bool isSmaller(rNode*, rNode*, int dimension);    //to determine the smallest between two nodes in a given dimension
rNode *splitRNode(rNode*, int dimension);     //to split a given internal node into two internal nodes
rNode *enLargeRNode(rNode*, Node*, int dimension);    //to increase the bounding box of a given internal node
bool searchNode(rNode*, Node*, int dimension);    //to search for a given node in the tree
rNode *insertNode(rNode*, Node*, int dimension);  //ro insert a given node in the tree
rNode *deleteNode(rNode*, Node*, int dimension);  //to delete a given node in the tree
void traverseNodes(rNode*, int dimension);    //to visit and display all nodes information
rNode *moveNodes(rNode*, float time, int dimension);     //to move node to different positions in the tree
Node *searchNodePosition(rNode*, Node*, int dimension);    //to search for the current position of a node or predict to future position over a given time