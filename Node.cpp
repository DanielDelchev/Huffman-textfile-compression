#include "Node.h"
#include <iomanip>
/**
 *@brief Deffault constructor fo the class
 *@date 20 01 2016
*/
Node::Node():id(-1),letter('Ù'),root(false),leaf(false){
    successors_id[0]=-2;
    successors_id[1]=-3;
}

/**
 *@brief Getter for the letter in the Node
 *@date 20 01 2016
 *@return the letter held in the Node
*/
char Node::get_letter()const{
    return this->letter;
}

/**
 *@brief Getter for the id of the Node
 *@date 20 01 2016
 *@return a positive number representint the ID of the node,if the returned value is a negative number then the Node has been created by a deffault constructor and is not currently valid
*/
int Node::get_id()const{
    return this->id;
}
/**
 *@brief Cheks if the Node is a root of a NodeTree
 *@date 20 01 2016
 *@return true if it is the root, false if not
*/
bool Node::is_root()const{
    return this->root;
}
/**
 *@brief Cheks if the Node is a leaf of a NodeTree
 *@date 20 01 2016
 *@return true if it is a leaf, false if not
*/
bool Node::is_leaf()const{
    return this->leaf;
}

/**
 *@brief Getter for the id of the left successor of the Node
 *@date 20 01 2016
 *@return non-negative number representing the id of the left successor if such exists, negative number if it doesn't exist
*/
int Node::get_left_successor_id()const{
    return this->successors_id[0];
}
/**
 *@brief Getter for the id of the right successor of the Node
 *@date 20 01 2016
 *@return non-negative number representing the id of the right successor if such exists, negative numbe if it doesn't exist
*/
int Node::get_right_successor_id()const{
    return this->successors_id[1];
}

/**
 *@brief Setter for the letter held in the Node
 *@date 20 01 2016
 *@param given - the char to be assigned as the letter of the Node
 *@return void
*/
void Node::set_letter(char given){
    letter=given;
}
/**
 *@brief Setter for the ID of the Node
 *@date 20 01 2016
 *@param given - the number to be assigned as ID of the Node
 *@return void
*/
void Node::set_id(int given){
    id=given;
}
/**
 *@brief Setter for the root? bool of the Node
 *@date 20 01 2016
 *@param given - a bool to be assigned to the bool variable
 *@return void
*/
void Node::set_root(bool given){
    root=given;
}
/**
 *@brief Setter for the leaf? bool of the Node
 *@date 20 01 2016
 *@param given - a bool to be assigned to the bool variable
 *@return void
*/
void Node::set_leaf(bool given){
    leaf=given;
}
/**
 *@brief Setter for the id of the left successor of the Node.
 *@date 20 01 2016
 *@param given - an integer to be assigned to the left successor id variable of the Node
 *@return void
*/
void Node::set_left_successor_id(int given){
    successors_id[0]=given;
}
/**
 *@brief Setter for the id of the right successor of the Node.
 *@date 20 01 2016
 *@param given - an integer to be assigned to the right successor id variable of the Node
 *@return void
*/
void Node::set_right_successor_id(int given){
        successors_id[1]=given;
}

/**
 *@brief private copy function used in operator= and in the copy constructor of the class
 *@param given - the Node to be copied
 *@date 20 01 2016
 *@return void
*/
void Node::copy(const Node& given){
    set_id(given.get_id());
    set_letter(given.get_letter());
    set_root(given.is_root());
    set_leaf(given.is_leaf());
    set_left_successor_id(given.get_left_successor_id());
    set_right_successor_id(given.get_right_successor_id());
}

/**
 *@brief Copy constructor of the class
 *@param the Node to be copied
 *@see copy(const Node& given)
 *@date 20 01 2016
 */
Node::Node(const Node& given){
    copy(given);
}
/**
 *@brief Operator= of the class
 *@param the Node to be used as rvalue of the assignement
 *@see copy(const Node& given)
 *@see destroy()
 *@date 20 01 2016
 */
Node& Node::operator=(const Node& given){
    if (this!=&given){
        destroy();
        copy(given);
    }
    return *this;
}

/**
 *@brief private destroy function used in the destructor of the class.Currently no dynamic memory is in the class, so the function does nothing.
 *@date 20 01 2016
 *@return void
*/
void Node::destroy(){
//no dynamic memory currently
}

/**
 *@brief Destructor of the class
 *@see destroy()
 *@date 20 01 2016
 */
Node::~Node(){
    destroy();
}
/**
 *@brief Operator << for the class
 *@date 20 01 2016
 */
ostream& operator<<(ostream& os,const Node& given){
    os<<"id:"<<given.get_id();
    os<<",letter:";
    if (given.is_leaf()){
        os<<given.get_letter()<<" ";
    }
    else{
        os<<"N/A ";
    }
    os<<",is_root:"<<boolalpha<<given.is_root()<<" ";
    os<<",is_leaf:"<<boolalpha<<given.is_leaf()<<endl;
    if (given.get_left_successor_id()>=0){
        os<<"left_successor_id:"<<given.get_left_successor_id()<<" ";
    }
    else{
        os<<"left_successor_id:"<<"N/A ";
    }
    if (given.get_right_successor_id()>=0){
        os<<",right_successor_id:"<<given.get_right_successor_id()<<" ";
    }
    else{
        os<<",right_successor_id:"<<"N/A ";
    }
    os<<endl;
    return os;
}

/**
 *@brief This function constructs a Node object from a Vertex object
         the resulting Node has the same letter as the Vertex and the
         same relations to other Nodes , keeping the relations the Vertex
         has to other Vertices.
 *@param given - The Vertex to be "mimiced" by the Node
 *@date 20 01 2016
 *@see Vertex
 */
Node::Node(const Vertex& given):id(-1),root(false){
    set_id(given.get_Node_ID());
    if (given.get_Node_ID()==0){
        set_root(true);
    }
    set_letter(given.get_letter());
    if (given.get_left_successor()==NULL && given.get_right_successor()==NULL){
        set_leaf(true);
    }
    if (given.get_left_successor()!=NULL){
        set_left_successor_id(given.get_left_successor()->get_Node_ID());
    }
    else{
        set_left_successor_id(-1);//invalid value
    }
    if (given.get_right_successor()!=NULL){
        set_right_successor_id(given.get_right_successor()->get_Node_ID());
    }
    else{
        set_right_successor_id(-1);//invalid value
    }
}
