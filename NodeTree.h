#ifndef NODETREE_H_INCLUDED
#define NODETREE_H_INCLUDED
#include "Node.h"
#include <vector>
#include <queue>
/**
 *@brief Object of this class represent the HufmnnTree.Object from this class
         are generated from objects of Tree class, keeping the data of the Vertices
         in the Tree and their relations, by constructing Nodes from the Vertices.
         The difference between Tree and NodeTree is that Tree contains pointers in its
         private members in order to store the relations between the Vertices and cannot be
         written down in a file,while Objects from NodeTree class use ID-s ( keyvalues ) to store
         these relations and thus can be serialized and desirialized to/from files.Also objects
         from this NodeTree class are used for Decompressing already compressed with Tree ojbects
         strings.
 *@date 20 01 2016
 *@see Tree
 *@see Node
 *@see Vertex
 */
class NodeTree{
public:
    NodeTree();
    NodeTree(const Tree& given);
    NodeTree(const char* filename);
    NodeTree(const NodeTree& given);
    NodeTree& operator=(const NodeTree& given);
    virtual ~NodeTree();

    friend ostream& operator<<(ostream& os,const NodeTree& given);

    void write_node_tree(const char* filename)const;

    const Node& get_start()const;// returns the first Node in the vector which should be the root
    const vector<Node>& get_nodes_vector()const; // Getter for the vector containing the Nodes of the Tree
    const Node& find_node(int given)const;// Getter for a Node from the vector whith the coresponding id
    char decompress_letter(const bool*& position)const; // Decompresses a fragment (a single letter) of a bool compessed code
private:
    void add_node(const Node& given); /**< Adds a Node into the NodeTree */ //nodes shall not be removed//
    void copy(const NodeTree& given); /**< Private copy function  */
    void destroy(); /**< Private destroy function  */
    vector<Node> Nodes; /**< a std::vector<Node> structure containing all the Nodes of the NodeTree */
    vector<Node>& get_pseudo_nodes_vector(); /**< Private getter for the vector of Nodes of the NodeTree */
};



void Decompress(const char* TreeData,const char* CodeData,const char* DecompressTo);//decompresses, see specification
void transformer(queue<Vertex>& Q,vector<Node>& result); //turns Vertecies into nodes ,keeping the proper relations for the Nodes

#endif // NODETREE_H_INCLUDED
