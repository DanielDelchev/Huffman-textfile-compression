#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED
#include "Tree.h"

/**
 *@brief Objects of this class are similliar to the objects of the Vertex class.
         Nodes are constructed from Vertices,keeping their letter, and relations.
         The main difference is that Nodes do not need pointers to store the relations.
         ID-s (Key values) are used to store the relations between Nodes.This way
         objects from Node class can be serialized and deserialized , while objects
         of the Vertex class cannot.
 *@date 20 01 2016
 *@see NodeTree
 *@see Vertex
 */
class Node{
public:
    Node();
    Node(const Vertex& given);
    Node (const Node& given);
    Node& operator=(const Node& given);
    virtual ~Node();

    friend ostream& operator<<(ostream& os,const Node& given);

    int get_id()const;
    char get_letter()const;
    bool is_root()const;
    bool is_leaf()const;
    int get_left_successor_id()const;
    int get_right_successor_id()const;

private:
    void set_root(bool given);/**< setter for the root? bool variable */
    void set_id(int given);/**< setter for the id of the Node */
    void set_left_successor_id(int given); /**< setter for the leftsuccessor? bool variable */
    void set_right_successor_id(int given); /**< setter for the rightsuccessor? bool variable */
    void set_letter(char given);/**< setter for the letter held in the Node */
    void set_leaf(bool given);/**<  setter for the leaf? variable in the Node */
    void copy(const Node& given);/**< private copy function used in operator= and copyconstructo of the class */
    void destroy();/**< private destroy function used in Destructor of the class */
    int id; /**< id (key) variable to destinguish Nodes from one another */
    char letter; /**< the letter held in the Node */
    short int successors_id [2]; /**< array of two short integers holding the id-s to the left and right successors of the Node first int-left,second int- right ,if the value is negative then there is no successo */
    bool root; /**< if this is true then this Node is the root of a NodeTree */
    bool leaf;/**< if this is true then this Node is a leaf of a NodeTree */
};

#endif // NODE_H_INCLUDED
