//Author: Bomen Derick
// Implementation file for the r-tree algorithm header file

#include "rtree.h"
#include <iostream>

#define BOUNDING_POINTS 2   //number of points that make up a bounding box
#define NUMBER_OF_POINTS 6  //maximum number of points a leaf node can hold
#define CHANGING_FACTOR 10  //changing factor of bb use by the splitNode() function
#define CHANGING_BL_POINT 2     //constant to change the bottom left point of a bounding box
#define CHANGING_TR_POINT 2     //constant to change the top right point of a bounding box

using namespace std;

//global variables
rNode *root = nullptr;
Node *node = nullptr;

//generating a new node with given mbb and dimension to be store in a leaf node
Node *newNode(double mbb[], int name, int k){
    node = new Node;    //creating  new instance of a Node
    node->mbb = new double[k];  //allocating space to store the mbb
    for (int i = 0; i < k; ++i) {
        node->mbb[i] = mbb[i];  //copying given mbb into generated node
    }
    node->name = name;  //keeping track of the representation of the created node

    return node;
}

//generating a new node (internal node) with a bounding box that can hold other nodes (leaf nodes ) with mbb
rNode *newRNode(int k) {
    root = new rNode;   //creating new instance of the rNode type
    root->bb = new Node[BOUNDING_POINTS];   //allocating space to store bb(bottom left and top right points)
    for (int i = 0; i < BOUNDING_POINTS; ++i) {
        root->bb[i].mbb = new double[k];    //allocating space to store bb(bottom left and top right points)
    }
    root->leafNode = new Node[NUMBER_OF_POINTS];    //allocating space to store leaf nodes
    for (int j = 0; j < NUMBER_OF_POINTS; ++j) {
        root->leafNode[j].mbb = nullptr;    //initializing nodes to null
    }

    root->nextNode = nullptr;
    root->numberOfNodes = 0;

    return root;
}

//utility function that return true if a given leaf node is in an internal node and fale otherwise
bool isInRNode(rNode *rnodeptr, Node *nodeptr, int k) {
    if (rnodeptr == nullptr || nodeptr == nullptr)
        return false;
    int j = 0;  //for indexing bb
    int m = 0;  //counter for every valid node nodeptr mbb < root node rnodeptr bb
    for (int i = 0; i < k; ++i) {
        //comparing values for all axis of the dimension (k) and increment counter m if the value for node nodeptr is the smallest
        // and return false otherwise
        if (nodeptr->mbb[i] >= rnodeptr->bb[j].mbb[i] && nodeptr->mbb[i] <= rnodeptr->bb[j +1].mbb[i]) {
            ++m;
            continue;
        } else
            return false;
    }
    return m == k;  //return true if the node n_ptr has smaller values than the root node r_ptr for all axises involved
}

//utility function that return true if rnodeptr2 has smaller bounding box than rnodeptr1 and false otherwise
bool isSmaller(rNode *rnodeptr1, rNode *rnodeptr2, int k) {
    if (rnodeptr1 == nullptr || rnodeptr2 == nullptr)
        return false;   //return false if both internal nodes to compare are null
    int j = 0;  //for indexing in1_ptr mbb
    int m = 0;  //counter for every valid node rnodeptr2 bb < internal node rnodeptr1 bb
    for (int i = 0; i < k; ++i) {
        //comparing values for all axis of the dimension (k) and increment counter m if the value for internal node rnodeptr2 is the smallest
        // and return false otherwise
        if ((rnodeptr2->bb[j].mbb[i] > rnodeptr1->bb[j].mbb[i]) && (rnodeptr2->bb[j + 1].mbb[i] < rnodeptr1->bb[j + 1].mbb[i])) {
            ++m;
            continue;
        } else
            return false;
    }
    return m == k;  //return true if the node in2_ptr has smaller values than the internal node in1_ptr for all axises involved
}

//utility function to split a given node with no free space for storage
rNode *splitRNode(rNode *rnodeptr, int k) {
    //generating and initializing a new instance of rNode
    rNode *newNode = nullptr;
    newNode = newRNode(k);

    //cpying last three points of given node to new rNode instance generated
    for (int i = NUMBER_OF_POINTS - 3; i < NUMBER_OF_POINTS; ++i) {
        newNode->leafNode[i - (NUMBER_OF_POINTS - 3)] = rnodeptr->leafNode[i];  //
        rnodeptr->leafNode[i].mbb = nullptr;    //overwrite copied point to null
        rnodeptr->numberOfNodes--;  //update points counter of the given internal node
        newNode->numberOfNodes++;   //update points counter of newly generated rNode instance
    }

    //decreasing the top right point of the given internal node bb by a constant change factor defined above
    for (int j = 0; j < k; ++j) {
        rnodeptr->bb[BOUNDING_POINTS - 1].mbb[j] = rnodeptr->bb[BOUNDING_POINTS - 1].mbb[j] - CHANGING_FACTOR;
    }
    rnodeptr->bb = rnodeptr->bb; //taking the updated top right point of the given internal node as the its new top right point

    //increasing the top right point of the given internal node bb by a constant factor defined above
    for (int l = 0; l < k; ++l) {
        rnodeptr->bb[BOUNDING_POINTS - 1].mbb[l] = rnodeptr->bb[BOUNDING_POINTS - 1].mbb[l] + CHANGING_FACTOR;
    }
    newNode->bb = rnodeptr->bb;     //taking the updated top right point of the given internal node as the top right point of the newly generated instance of rNode bb

    //link the newly generated node to the given node if the given node is linked to no one
    if (rnodeptr->nextNode == nullptr) {
        rnodeptr->nextNode = newNode;
    }

    //insert the newly generated node between the given node and the node it links to.
    //NOTE: single linked list insertion
    else if (rnodeptr->nextNode != nullptr){
        newNode->nextNode = rnodeptr->nextNode;
        rnodeptr->nextNode = newNode;
    }

    return rnodeptr;  //return the given node with the newly generated node linked to it
}

//utility function to enlarge a given internal node with respect to a given leaf node so as to fit the given leaf node
rNode *enLargeRNode(rNode *rnodeptr, Node *nodeptr, int k) {
    if (rnodeptr == nullptr || nodeptr == nullptr) {
        rnodeptr = newRNode(k);     //create a new node if the given node to be enlarge is null
    }
    int i = 0; //local variable use to index bounding box
    //check if we need to enlarge the Bottom left(BL) point ie(if point is outside at the bottom or left of the bounding box)
    int q = 0; //local variable use by Bottom-Left point
    for (int j = 0; j < k; ++j) {
        if (rnodeptr->bb[i].mbb[j] > nodeptr->mbb[j])
        {
            ++q; //increment q if any index value of the BL point is greater than its corresponding index value in the given node
        }
    }
    if (q >= 1)
        rnodeptr->bb[i].mbb = nodeptr->mbb; //enlarge BL point of the bounding box to hold exactly the point

    int t = 0; //local variable use by Top-Right point
    //check if we need to enlarge the Top Right(TR) point ie(if point is outside at the Top or right of the bounding box)
    for (int l = 0; l < k; ++l){
        if (rnodeptr->bb[i + 1].mbb[l] < nodeptr->mbb[l])
            ++t; //increment t if any index value of the TR point is less than its corresponding index value in the given node
    }
    if (t >= 1)
        rnodeptr->bb[i + 1].mbb = nodeptr->mbb; //enlarge TR point of the bounding box to hold exactly the point
    return rnodeptr; //return the resulted enlarged bounding box
}

//search for a given node in the r-tree starting at the root
bool searchNode(rNode *rnodeptr, Node *nodeptr, int k) {
    if (rnodeptr == nullptr || nodeptr == nullptr)
        return false;   //return false if either or both given nodes are null

    //visiting all available internal nodes
    for (int i = 0; i < rnodeptr->numberOfNodes; ++i) {
        if (rnodeptr->leafNode[i].name == nodeptr->name)    //return true if the unique representation of the given leaf mode has a match
        {
            return true;
            //break;
        }
    }

    return searchNode(rnodeptr->nextNode, nodeptr, k);  //traverse to the next internal node
}

//insert a given node in an r-tree starting from the root node
rNode *insertNode(rNode *rnodeptr, Node *nodeptr, int k) {
    if (nodeptr == nullptr)
        return rnodeptr;      //return the given r-tree if the given node is null

    //generated a new root node if the given r-tree is empty
    else if (rnodeptr == nullptr) {
        //generated and inditialize new intance of rNode to be use as root node
        rNode *newrnodeptr = nullptr;
        newrnodeptr = newRNode(k);

        //initializing the bb of the new root node
        for (int i = 0; i < BOUNDING_POINTS; ++i) {
            //divide node nodeptr mbb by 2 and take it as the bottom left point of the root node rootNode1
            if (i == 0) {
                for (int j = 0; j < k; ++j) {
                    newrnodeptr->bb[i].mbb[j] = nodeptr->mbb[j] / CHANGING_BL_POINT;
                }
                continue;
            }
            //multiply node nodeptr mbb and take it as the top right point of the root node rootNode1
            for (int l = 0; l < k; ++l) {
                newrnodeptr->bb[i].mbb[l]= nodeptr->mbb[0] * CHANGING_TR_POINT;
            }
        }

        //store given point as leaf node
        newrnodeptr->leafNode[0] = *nodeptr;
        //newrnodeptr->leafNode[0].name = nodeptr->name;
        //newrnodeptr->leafNode[0].mbb = nodeptr->mbb;
        newrnodeptr->numberOfNodes++;

        return newrnodeptr;     //return resulting r-tree with generated root node and inserted leaf node
    }

    //insert given node only of it's not present in the r-tree. scan to avoid redundanct nodes
    if (!searchNode(rnodeptr, nodeptr, k)) {
        //insert in an internal node if the given node belongs to it and there is free space
        if (isInRNode(rnodeptr, nodeptr, k) && rnodeptr->numberOfNodes < NUMBER_OF_POINTS) {
            rnodeptr->leafNode[rnodeptr->numberOfNodes] = *nodeptr;
            //rnodeptr->leafNode[rnodeptr->numberOfNodes].name = nodeptr->name;
            //rnodeptr->leafNode[rnodeptr->numberOfNodes].mbb = nodeptr->mbb;
            rnodeptr->numberOfNodes++;
            return rnodeptr;
        }

        //split an internal node with no free space the given leaf node belongs to, and insert in it
        if (isInRNode(rnodeptr, nodeptr, k) && rnodeptr->numberOfNodes >= NUMBER_OF_POINTS) {
             insertNode(splitRNode(rnodeptr, k), nodeptr, k);
        }

        //insert in sibling internal node if given node does not belong to the current internal node
        if (!isInRNode(rnodeptr, nodeptr, k) && rnodeptr->nextNode != nullptr) {
             insertNode(rnodeptr->nextNode, nodeptr, k);
        }

        if (!isInRNode(rnodeptr, nodeptr, k) && rnodeptr->nextNode == nullptr) {
            //enlarge an internal node to accommodate the given node if it got free space but given node does not belong to
            if (rnodeptr->numberOfNodes < NUMBER_OF_POINTS) {
                insertNode(enLargeRNode(rnodeptr, nodeptr, k), nodeptr, k);
            }

            //generate a new internal node if given node does not not belong to none of the present internal nodes and hasn't yet been inserted
            if (rnodeptr->numberOfNodes >= NUMBER_OF_POINTS && !searchNode(rnodeptr, nodeptr, k)) {
                //same as above on creating a new node of type rNode
                rNode *rnode_ptr = nullptr;
                rnode_ptr = newRNode(k);
                rnode_ptr->leafNode[0] = *nodeptr;
                //rnode_ptr->leafNode[0].name = nodeptr->name;
                //rnode_ptr->leafNode[0].mbb = nodeptr->mbb;

                rnode_ptr->numberOfNodes++;
                int j = 0;
                for (int i = 0; i < k; ++i) {
                    rnode_ptr->bb[j].mbb[i] = nodeptr->mbb[i] / CHANGING_BL_POINT;
                }

                for (int l = 0; l < k; ++l) {
                    rnode_ptr->bb[j + 1].mbb[l] = nodeptr->mbb[l] * CHANGING_TR_POINT;
                }

                rnodeptr->nextNode = rnode_ptr;     //link newly generated internal node to given root node

                return rnodeptr;  //return root node with newly generated node linked to it
            }
        }
    }

    return rnodeptr;    //return resulting root node with all linkage
}

//delete a given node in an r-tree starting form the root node
rNode *deleteNode(rNode *rnodeptr, Node *nodeptr, int k) {
    if (nodeptr == nullptr)
        return rnodeptr;    //return given r-tree if given node is null
    else if(rnodeptr == nullptr)
        return nullptr;     //return null if given r-tree is null
    //check if node to delete is present or not before visiting internal nodes
    if (searchNode(rnodeptr, nodeptr, k)) {
        //checks all availables internal nodes
        while (rnodeptr != nullptr) {
            for (int i = 0; i < rnodeptr->numberOfNodes; ++i) {
                //delete given node if its representation got a match
                if (rnodeptr->leafNode[i].name == nodeptr->name) {
                    delete rnodeptr->leafNode[i].mbb;   //deleting node
                    rnodeptr->leafNode[i].mbb = nullptr;    //overwriting memory location to null to avoid segmentation faults
                    rnodeptr->leafNode[i].name = -1;    //creating a sentinal for represention (since memory was allocated statically) to avoid false search since search is base on nodes' representation

                    return rnodeptr;    //return updated r-tree
                }
            }
            rnodeptr = rnodeptr->nextNode;      //delete in siblings if node not found in current internal node
        }
    }

    return rnodeptr;    //return updated r-tree
}

//visit all nodes of a given r-tree and display stored data
void traverseNodes(rNode *rnodeptr, int k) {
    if (rnodeptr == nullptr)
        return;

    //starting from the root, traverse all internal nodes and respective leaf nodes
    for (int i = 0; i < rnodeptr->numberOfNodes; ++i) {
        //skip to the next internal node if current internal node has null memory
        if (rnodeptr->leafNode[i].mbb == nullptr)
            continue;
        else {
            cout<<rnodeptr->leafNode[i].name<<"(";
            for (int j = 0; j < k; ++j) {
                cout<<rnodeptr->leafNode[i].mbb[j]<<" ";
            }
            cout<<"), ";
        }
    }
    cout<<endl;
    traverseNodes(rnodeptr->nextNode, k);   //recursion over sibling internal nodes
}

//move nodes to different positions in the r-tree for a given time in a given dimension
rNode *moveNodes(rNode *rnodeptr, float time1, int k) {
    if (rnodeptr == nullptr)
        return nullptr;

    for (int i = 0; i < rnodeptr->numberOfNodes; ++i) {
        if (rnodeptr->leafNode[i].mbb == nullptr)
            continue;
        for (int j = 0; j < k; ++j) {
            rnodeptr->leafNode[i].mbb[j]  *= time1;    //move every nodes by a multiple of the given time
        }
    }

    moveNodes(rnodeptr->nextNode, time1, k);  //move sibling internal nodes

    return rnodeptr;    //return updated r-tree
}

Node *searchNodePosition(rNode *rnodeptr, Node *nodeptr, int k) {
    if (rnodeptr == nullptr || nodeptr == nullptr)
        return nodeptr;   //return given node if given root node null

    //visiting all available internal nodes
    for (int i = 0; i < rnodeptr->numberOfNodes; ++i) {
        if (rnodeptr->leafNode[i].mbb == nullptr)
            continue;
        if (rnodeptr->leafNode[i].name == nodeptr->name)    //return current position of given leaf node if the unique representation of the given leaf mode has a match
            return &rnodeptr->leafNode[i];
    }

    searchNodePosition(rnodeptr->nextNode, nodeptr, k);  //traverse to the next internal node

    return nodeptr;
}