#include "NodeTree.h"

/**
 *@brief deffault constructor for the class
 *@date 20 01 2016
 */
NodeTree::NodeTree(){
}
/**
 *@brief Copy constructor for the class
 *@see copy(const NodeTree& given)
 *@date 20 01 2016
 */
NodeTree::NodeTree(const NodeTree& given){
    this->copy(given);
}
/**
 *@brief Operator= for the class
 *@see copy(const NodeTree& given)
 *@see destroy()
 *@date 20 01 2016
 */
NodeTree& NodeTree::operator=(const NodeTree& given){
    if (this!=&given){
        destroy();
        copy(given);
    }
    return *this;
}

/**
 *@brief Private destroy() function used in the class Destructor
 *@see ~NodeTree()
 *@date 20 01 2016
 */
void NodeTree::destroy(){
}//no virtual memory currently
/**
 *@brief Destructor of the class
 *@see destroy()
 *@date 20 01 2016
 *@return void
 */
NodeTree::~NodeTree(){
}

/**
 *@brief Pivate copy function used in operator= and in copy constructor ofthe class
 *@date 20 01 2016
 *@return void
 */
void NodeTree::copy(const NodeTree& given){
    int vectorsize=given.get_nodes_vector().size();
    for (int i=0;i<vectorsize;i++){
        this->add_node((given.get_nodes_vector())[i]);
    }
}

/**
 *@brief Getter for the first Node in the std::vector<Node> containing all Nodes of the NodeTree
 *@date 20 01 2016
 *@return constant pseudonym to the first Node of the vector storing the Nodes of the tree or a deffaultly constructed Node if the NodeTree is empty
*/
const Node& NodeTree::get_start()const{
    if (Nodes.empty()){
        cout<<"Nodes vector is empty!"<<endl;
        return Node();
    }
    return Nodes[0];
}

/**
 *@brief Getter for the std::vector<Node> containing all Nodes of the NodeTree
 *@date 20 01 2016
 *@return constant pseudonym to that vector
*/
const vector<Node>& NodeTree::get_nodes_vector()const{
    return Nodes;
}

/**
 *@brief Private getter for the std::vector<Node> containing all Nodes of the NodeTree
 *@date 20 01 2016
 *@return pseudonym to that vector
*/
vector<Node>& NodeTree::get_pseudo_nodes_vector(){
    return Nodes;
}

/**
 *@brief This function adds a Node to the std::vector<Node> containing all Nodes of the NodeTree
 *@param given - the Node to be added
 *@date 20 01 2016
 *@return void
*/
void NodeTree::add_node(const Node& given){
    this->Nodes.push_back(given);
}

/**
 *@brief Finds a Node with the specified ID (keyvalue) in the NodeTree
 *@param given - the ID of the sought Node
 *@date 20 01 2016
 *@return constant pseudonym to that Node (if found) or deffaultly constructed Node if not found
*/
const Node& NodeTree::find_node(int given)const{
    int vectorsize=(this->get_nodes_vector()).size();
    for (int i=0;i<vectorsize;i++){
        if (this->get_nodes_vector()[i].get_id()==given){
            return get_nodes_vector()[i];
        }
    }
    cout<<"Node not found!"<<endl;
    return Node();// if not found
}

/**
 *@brief operator<< for the class
 *@date 20 01 2016
 */
ostream& operator<<(ostream& os,const NodeTree& given){
    int vectorsize=(given.get_nodes_vector()).size();
    for (int i=0;i<vectorsize;i++){
        os<<((given.get_nodes_vector())[i]);
    }
    os<<endl;
    return os;
}

/**
 *@brief This constructor constructs a NodeTree object from a Tree object.
         If the handed Tree is empty then an empty NodeTree is returned.
         In other casese a queue containing only the root (Vertex) of the Tree
         is constructed.Then transformer(...) function is called for the queue
         and the vector containing the Nodes of the NodeTree which is currently empty.
         After the transfome(...) function has been applied , the NodeTree contains
         Nodes with the same letters as the Vertices in the Tree object, and these
         Nodes keep the same relation amongs themselves like the Vertices in the Tree do.
 *@param given - the Tree from which the NodeTree will be built.
 *@see transformer(queue<Vertex>& Q,vector<Node>& result)
 *@date 20 01 2016
 */
NodeTree::NodeTree(const Tree& given){
    if (given.get_root()==NULL){
        cout<<"Empty tree handed to changing constructor!"<<endl;
        *this=NodeTree();
    }
    else{
        queue<Vertex> Q;
        Q.push(*(given.get_root()));
        transformer(Q,this->get_pseudo_nodes_vector());
    }
}

/**
 *@brief This function receives pseudonym to a non-empty queue of Vertices and a pseudonym to a vector of Nodes.
         The function is recurssive.Each time the function is called the following operations are performed:
         If the queue is not empty:
         1) construct a Node from the Vertex at the front of the queque
         2) push_back that Node into the vector
         3) if the Vertex at the front of the queue has successos (left or right) put them at the back of the queue
         4) pop the front element of the queue
         5) if the queue is still not empty call the function again with the new queue and vector
         As a result when the recurssion ends (when the queue has been emptied) the vector will contain
         Nodes "mimicing" their coresponding Vertices from the queue with the same data for the letter
         and same relations.
 *@see Vertex
 *@see Node
 *@see Node::Node(const Vertex& given)
 *@see NodeTree::NodeTree(const Tree& given)
 *@param Q - A pseudonym to a queue of vertices (should not be empty when the function is called for the first time)
 *@param Result - a pseudonym to a vector in which the Nodes constructed from the Vertices in the queue are stored
 *@date 20 01 2016
 *@return void
 */
void transformer(queue<Vertex>& Q,vector<Node>& result){
        if(!Q.empty()){
            Node N(Q.front());//
            result.push_back(N);//
            if ((Q.front().get_left_successor())!=NULL){
                Q.push((*(Q.front().get_left_successor())));
            }
            if ((Q.front().get_right_successor())!=NULL){
                Q.push((*(Q.front().get_right_successor())));
            }
            Q.pop();
        }
        if (!Q.empty()){
            transformer(Q,result);
        }
}

/**
 *@brief This function writes down the NodeTree in a binary file.
         In the file are written all the Nodes from the std::vector<Node>
         containing the Nodes of the Tree.
 *@see Node
 *@return void
 *@param filename - the name of the binary file in which the NodeTree will be stored
 *@date 20 01 2016
*/
void NodeTree::write_node_tree(const char* filename)const{
    fstream fs(filename,ios::binary|ios::trunc|ios::out);
    vector<Node> vec=get_nodes_vector();
    int l=vec.size();
    for (int i=0;i<l;i++){//write down all Nodes
        fs.write((const char*)& vec[i],sizeof(Node));
    }
    fs.close();
}
/**
 *@brief This function reads Nodes from a binary file and adds them to the std::vector<Node>
         containing the Nodes of the NodeTree, and thus deserializing that NodeTree.
 *@see Node
 *@see NodeTree::add_node(const Node& given)
 *@param filename - the name of the binary file from which the Nodes for the NodeTree will be read
 *@date 20 01 2016
*/
NodeTree::NodeTree(const char* filename){
    fstream fs(filename,ios::binary|ios::in);
    Node temp;
    fs.seekg(0,ios::end);
    int counter=(fs.tellg()/sizeof(Node));//calculate how many Nodes will be read
    fs.seekg(0,ios::beg);
    for (int i=0;i<counter;i++){//read each Node and add it to the NodeTree
        fs.read((char*)&temp,sizeof(Node));
        this->add_node(temp);
    }
    fs.close();
}

/**
 *@brief This function is used to Decompress a bool compressed message stoed in PackedBytes stored in a binary file.
         For the decompression a NodeTree (coresponding to the HufmannTree fom which that compressed message has been built)
         is deserialized from another binary file.The PackedBytes get "unpacked" into a buffer and then the bools from that
         buffer get decompressed using the NodeTree.The result string is the initial string that has been previously compressed.
         That result string is then written into a textfile.
 *@param TreeData - a binary file from which a NodeTree can be deserialized
 *@param CodeData - a binary file containing PackedBytes containing bools from a bool compressed message which was created by the same Tree from which the NodeTree was created
 *@param DecompressTo - a text file in which the decompressed message (the initial string ) will be written down in
 *@see PackedByte
 *@see NodeTree::NodeTree(const char* filename)
 *@see NodeTree::decompress_letter(const bool*& position)const
 *@return void
 */
void Decompress(const char* TreeData,const char* CodeData,const char* DecompressTo){
    fstream fs(CodeData,ios::binary|ios::in); //open the file from which the compressed message will be read
    unsigned long long int decompressed_message_length=0;
    unsigned long long int PackedBytesCount=0;
    int leftovers = 0;

    fs.read( (char*)& decompressed_message_length,sizeof(unsigned long long int)); //read the length of the decompressed message
    fs.read( (char*)& PackedBytesCount,sizeof(unsigned long long int)); //read the number of PackedBytes to be read
    fs.read( (char*)& leftovers,sizeof(int));//read the leftovers (the number of bytes from which the last PackedByte was built (might be less than 8) )

    unsigned long long int bool_compressed_length=BITS_IN_BYTE*PackedBytesCount; //calculating the lenght of the bool compessed message
    if (leftovers!=0){
        bool_compressed_length-=BITS_IN_BYTE;
        bool_compressed_length+=leftovers;
    }

    bool* bool_compressed = new bool [bool_compressed_length]; //allocating enough memory to store the compressed bool message into a buffer

    PackedByte* packed=new PackedByte[PackedBytesCount];//allocating enoough memory to store the PackedBytes into a buffer
    for (unsigned long long int i=0;i<PackedBytesCount;i++){
        fs.read( (char*)& packed[i],sizeof(PackedByte));
    }
    fs.close();


    if(leftovers == 0){//in case there are no leftovers procceed in the following way
        for (unsigned long long int i=0;i<PackedBytesCount;i++){
            for (int j=0;j<BITS_IN_BYTE;j++){
                *(bool_compressed + (i*BITS_IN_BYTE) +j)= packed[i].get_bit(j); //from each PackedByte read 8 bits and store them in bool_compressed buffer
            }
        }
    }

    else if (leftovers!=0){//if there are indeed leftovers proceed in this way
        for (unsigned long long int i=0;i<PackedBytesCount-1;i++){
            for (int j=0;j<BITS_IN_BYTE;j++){
                *(bool_compressed + (i*BITS_IN_BYTE) +j)= packed[i].get_bit(j);  //from each PackedByte read 8 bits and store them in bool_compressed buffer
            }
        }

        for (int f=0;f<leftovers;f++){//the last PackedByte is exception and has less than 8 bits, read only them into the buffer
            *(bool_compressed + (PackedBytesCount-1)*BITS_IN_BYTE +f) = packed[PackedBytesCount-1].get_bit(BITS_IN_BYTE-leftovers+f);
        }
    }


    NodeTree decompressing_tree(TreeData); //construct a NodeTree from a binary file in which a NodeTree has been serialized before

    const bool* pointer=bool_compressed;//get a pointer to the first bool in the compressed_message buffer
    char receiver;// a temporary char buffer to store the last decompressed letter
    fstream fs2(DecompressTo,ios::trunc|ios::out);//open a text file in which the decompressed message will be witten down
    for (unsigned long long int i=0;i<decompressed_message_length;i++){
        receiver=decompressing_tree.decompress_letter(pointer); //decompress each letter from the initial string input message
        fs2<<receiver; //write that letter into the file
    }
    fs2.close();
}

/**
 *@brief This function is handed a pseudonym to a bool pointer
         and depending on wheter the pointer is currently pointing to 1 or 0
         we move from the NodeTree root to right or left and move the pointer to
         the next bool of the bool code.We do that until we 've reached a leaf in the
         NodeTree and return the letter held in that Node.
 *@see  Decompress(const char* TreeData,const char* CodeData,const char* DecompressTo)
 *@return A char contained in the leaf of the NodeTree we 've reached.
 *@date 20 01 2016
 */
char NodeTree::decompress_letter(const bool*& position)const{
    Node tree_node=this->get_start();//get the root of the NodeTree
    while (!tree_node.is_leaf()){//while not a leaf
        if (*position==true){
            tree_node=find_node(tree_node.get_right_successor_id()); //if position currently points to 1 in the code ,we go to the right successor of the current Node
        }
        else{
            tree_node=find_node(tree_node.get_left_successor_id());  //if position currently points to 0 in the code, we go to the left successor of the current Node
        }
        position++; // move the pointer to the next bool of the bool compressed code
    }
    return tree_node.get_letter(); //return the letter of the Leaf (Node) we 've reached
}
