#include "Tree.h"

/**
 *@brief Deffault constructor for the class.Creates an empty tree.
 *@date 20 01 2016
 */
Tree::Tree():Table::Table(),root(NULL),compressed_message(NULL),compressed_decimal_message(NULL){
    message_length=0;
    compressed_message_length=0;
    compressed_decimal_message_length=0;
};

/**
 *@brief Private destroy function used in the destuctor of the class.
 *@date 20 01 2016
 *@see ~Tree()
 *@return void
 */
void Tree::destroy(){
    delete [] compressed_message;
    delete [] compressed_decimal_message;
    destroy_tree(root);
}
/**
 *@brief Private destroy function used in the destuctor of the class.
 *@date 20 01 2016
 *@see destroy()
 */
Tree::~Tree(){
    destroy();
}

/**
 *@brief Copy function used in operator= and copy constructor of the class
 *@date 20 01 2016
 *@return void
 *@param given - the Tree to be copied
 */
void Tree::copy(const Tree& given){
    message_length=given.get_message_length();
    compressed_message_length=given.get_compressed_message_length();
    compressed_decimal_message_length=given.get_compressed_decimal_message_length();
    compressed_message=new bool [compressed_message_length];
    for (unsigned long long int i=0;i<compressed_message_length;i++){
        *(compressed_message+i)=*(given.get_compressed_message()+i);
    }
    compressed_decimal_message=new short unsigned int [compressed_decimal_message_length];
    for (unsigned long long int i=0;i<compressed_decimal_message_length;i++){
        *(compressed_decimal_message+i)=*(given.get_compressed_decimal_message()+i);
    }
    root=copy_tree(given.get_root());     //this copies the tree properly
}

/**
 *@brief Copy constructor of the class.
 *@date 20 01 2016
 *@param given - the Tree to be copied
 *@see copy(const Tree& given)
 */
Tree::Tree(const Tree& given):Table::Table(given),root(NULL),compressed_message(NULL),compressed_decimal_message(NULL){
    copy(given);
}

/**
 *@brief Operator= for the class.
 *@date 20 01 2016
 *@param given - the rvalue of the assignment.
 *@see copy(const Tree& given)
 *@see destroy()
 */
Tree& Tree::operator=(const Tree& given){
    Table::operator=(given);
    if (this!=&given){
        destroy();
        copy(given);
    }
    return *this;
}

/**
 *@brief Operator << for the class
 *@date 20 01 2016
 */
 //Prints the tree, the compressed message, and the compression benefit in the console. Unsuitable for large strings.
ostream& operator<<(ostream& os,const Tree& given){
    os<<"Tree root:";
    if(given.get_root()==NULL){
        os<<"N/A"<<endl;
    }
    else{
        os<<"letter:"<<given.get_root()->get_letter()<<" ,repetitions:"<<given.get_root()->get_repetitions()<<endl;
    }
    os<<"Compressed message:";
    if (given.get_compressed_message()==NULL){
        os<<"N/A";
    }
    else {
        os<<endl;
        for (unsigned long long int i=0;i<given.get_compressed_message_length();i++){
            if ( (i!=0)&&((i%7)==0)&&(i!=(given.get_compressed_message_length()+1))){//to make the output into blocks of digits of 8
                os<<" ";
            }
            os<<*(given.get_compressed_message()+i);
        }
    }
            os<<endl<<"Compressed decimal message:";

    if (given.get_compressed_decimal_message()==NULL){
        os<<"N/A";
    }
    else {
        os<<endl;
        for (unsigned long long int i=0;i<given.get_compressed_decimal_message_length();i++){
            os<<*(given.get_compressed_decimal_message()+i)<<" ";
        }
    }
    os<<endl;
    double benefit_bool=given.calculate_compression_benefit_bools();
    double benefit_int=given.calculate_compression_benefit_integers();
    os<<"Compression benefit from chars to bools:"<<benefit_bool<<endl<<endl;
    os<<"Compression benefit from chars to short integers:"<<benefit_int<<endl<<endl;
    return os;
}

/**
 *@brief Operator>> for the class.
 *@date 20 01 2016
 */
 //reads a string from the console and builds a tree with it
istream& operator>>(istream& is,Tree& given){
    char buffer[51];
    is.get(buffer,51);
    int length=strlen(buffer);
    char* newmemo=new char [length+1];
    strcpy(newmemo,buffer);
    char* newmemo2=NULL;
    while(strlen(buffer)>=50&&length<=1050){
        is.get(buffer,51);
        length+=strlen(buffer);
        newmemo2=new char[length+1];
        strcpy(newmemo2,newmemo);
        strcat(newmemo2,buffer);
        delete [] newmemo;
        newmemo=newmemo2;
    }

    if (length<50){
        Tree temporary(newmemo);
        given=temporary;
    }
    else if (length>=50){
        Tree temporary(newmemo2);
        given=temporary;
        delete [] newmemo;
    }
    return is;
}

/**
 *@brief Getter for the lenght of the input message.
 *@date 20 01 2016
 *@return The length of the input sting from which the Tree has been built.
 */
unsigned long long int Tree::get_message_length()const{
    return message_length;
}

/**
 *@brief Setter for the lenght of the input message.
 *@date 20 01 2016
 *@return The length of the input sting from which the Tree has been built.
 *@param given - the length to be assigned
 */
void Tree::set_message_length(unsigned long long int given){
    message_length=given;
}

/**
 *@brief Getter for the root of the tree.
 *@date 20 01 2016
 *@return Retruns a pointer to the root of the Huffmann Tree.
 */
Vertex* Tree::get_root()const{
    return root;
}

/**
 *@brief Getter for the compressed bool message.
 *@date 20 01 2016
 *@return A bool pointer to the beginning of the bool array representing the compressed bool message.
 */
bool* Tree::get_compressed_message()const{
    return compressed_message;
}

/**
 *@brief Getter for the lenght of the compressed bool message.
 *@date 20 01 2016
 *@return The length of the compressed bool message.
 */
unsigned long long int Tree::get_compressed_message_length()const{
    return compressed_message_length;
}

/**
 *@brief Getter for the compressed decimal message.
 *@date 20 01 2016
 *@return An int pointer to the beginning of the int array representing the compressed integer message .
 */
short unsigned int* Tree::get_compressed_decimal_message()const{
    return compressed_decimal_message;
}
/**
 *@brief Getter for the lenght of the compressed decimal message.
 *@date 20 01 2016
 *@return The length of the compressed decimal message.
 */
unsigned long long int Tree::get_compressed_decimal_message_length()const{
    return compressed_decimal_message_length;
}


/**
 *@brief Prints the compressed bool message into the console.
 *@date 20 01 2016
 *@return void
 */
void Tree::print_compressed_message()const{
    int i=0;
    while(*(compressed_message+i)){
        cout<<*(compressed_message+i);
        i++;
    }
    cout<<endl;
}

/**
 *@brief Pints the compressed decimal message into the console.
 *@date 20 01 2016
 *@return void
 */
void Tree::print_compressed_decimal_message()const{//ok
    int i=0;
    while(*(compressed_decimal_message+i)){
        cout<<*(compressed_decimal_message+i);
        i++;
    }
    cout<<endl;
}

/**
 *@brief Prints the Table inherited by the Tree (uses operator<< for Table).
 *@date 20 01 2016
 *@return void
 */
void Tree::print_table()const{//ok
    cout<<((Table) *this);
}

/**
 *@brief This function copies the tree and returns a root to a new tree copy.
         It first copies the data of the root Vetex and then calls itself (revurssively) to
         copy the successors of the current Vertex.The recurssion reaches end when the
         pointer to the current Vertex is NULL.As a result a new Vertex is created which is
         a copy of the root of a tree given as a parameter to the function, but no memory
         is shared by the Trees.
 *@date 20 01 2016
 *@param given - The pointer to a Vertex which points to the root of the tree to be copied.
 *@return A Vertex pointer to the root of the newly built tree which is a copy of the tree whose root was given as a parameter.
 */
Vertex* Tree::copy_tree(Vertex* given){

    Vertex* receiver=NULL;
    if(given!=NULL){
        receiver=new Vertex;
        receiver->set_repetitions(given->get_repetitions());
        receiver->set_letter(given->get_letter());
        receiver->set_code_length(given->get_code_length());
        receiver->set_code(given->get_code(),given->get_code_length());
        receiver->set_marked(given->is_marked());
        receiver->set_special_ID(given->get_special_ID());
        receiver->set_Node_ID(given->get_Node_ID());
        receiver->set_left_successor(copy_tree(given->get_left_successor()));
        receiver->set_right_successor(copy_tree(given->get_right_successor()));
    }
    return receiver;
}

/**
 *@brief Prints the tree into the console.In the following manne
         "ITSELF:" (current Vertex data) LEFT: (LEFT SUCCESSOR DATA) RIGHT: (RIGHT SUCCESSOR DATA);
         starting from the root of the tree, recurssion reaches end when the current pointer to a Vetex is NULL
 *@param given - a Vertex pointer to the root of the tree to be printed
 *@date 20 01 2016
 *@return void
 */
void Tree::print_tree(Vertex* given)const{
    if (given!=NULL){
        cout<<"**********************************************"<<endl;
        cout<<"ITSELF:"<<endl;
        cout<<given<<"  letter:"<<given->get_letter()<<" ,repetitions:"<<given->get_repetitions()<<" ,NODE_ID:"<<given->get_Node_ID()<<endl;
        cout<<"LEFT successor:"<<endl;
        cout<<given->get_left_successor()<<endl;
        if ((given->get_left_successor())!=NULL){
            cout<<"letter:"<<given->get_left_successor()->get_letter()<<" ,repetitions:"<<given->get_left_successor()->get_repetitions();
            cout<<" ,NODE_ID:"<<given->get_left_successor()->get_Node_ID()<<endl;
        }
        cout<<"RIGHT successor"<<endl;
        cout<<given->get_right_successor()<<endl;
        if ((given->get_right_successor())!=NULL){
            cout<<"letter:"<<given->get_right_successor()->get_letter()<<" ,repetitions:"<<given->get_right_successor()->get_repetitions();
            cout<<" ,NODE_ID:"<<given->get_right_successor()->get_Node_ID()<<endl;
        }
        print_tree(given->get_left_successor());
        print_tree(given->get_right_successor());
    }
}


/**
 *@brief Destroy function for the tree. Deletes all Vertices from the bottom-up.
 *@date 20 01 2016
 *@see destroy()
 *@see ~Tree();
 *@return void
 */

void Tree::destroy_tree(Vertex* given){
    if (given!=NULL){
        destroy_tree(given->get_left_successor());
        destroy_tree(given->get_right_successor());
        given->destroy();
        given->Vertex::destroy();//deletes the vertex's code
        delete given;//deletes the vertex
        given=NULL;
    }
}

/**
 *@brief This function is used to reset all the markers of the Vertices in the tree to false.
 *@date 20 01 2016
 *@see Vertex
 *@return void
 */
void Tree::refresh_tree(Vertex* root){
    if (root!=NULL){
        root->set_marked(false);
    }
    if (root->get_left_successor()!=NULL){
        refresh_tree(root->get_left_successor());
    }
    if (root->get_right_successor()!=NULL){
        refresh_tree(root->get_right_successor());
    }
}

/**
 *@brief Finds the path from the root to a specific Leaf (Vertex) in the Tree and stores it into a Stack.
         The function is reccursive.
         As a result a Stack with the path is returned (if we pop the stack we ll get the path in reverse-
         the path from the Leaf (Vertex) to the tree root. At each call of the function first is checked
         wheter at the top of the stack there is a Box containing a Vertex whose left successors is not NULL
         and has not been marked as traversed yet.If such is the case, then we push that left successor Vertex
         into the Stack and call the function again for the newly formed Stack.If the left successor is NULL or
         has already been marked as traversed then we perfom the same for the right successor of the Vertex at
         the top of the Stack.After these two operations have been applied enough times , we have reached a situation
         when at the top of the Stack there is a leaf.When it is no longer possible to go "lower" in the tree we check
         if we have reached our destination Leaf (Vertex),if yes we return the Stack, if no we mark the current Vertex
         as traversed and start popping back.
         In this way we perform a Left,Root,Right search for the Leaf (Vertex) and store the path to it in a Stack.
         It is important to point out that we must be sure that the Vertex given as a parameter will be found.
 *@date 20 01 2016
 *@see Stack
 *@see Box
 *@see find_reversed_path_to_leaf(Stack& sought_path,const Vertex& given_leaf)
 *@param sought_path - a pseudonym of the Stack we are storing the path in.
 *@param given_leaf - The Leaf (Vertex) the path to which we are looking for.
 *@return Stack containing the sought path.
 */
Stack Tree::find_path(Stack& sought_path,const Vertex& given_leaf){//THIS BUILDS A STACK , IF WE POP IT WE GET THE !REVERSED! PATH FROM TO THE SPECIFIED VERTEX
    if(sought_path.top().get_left_successor()!=NULL&& sought_path.top().get_left_successor()->is_marked()==false){
        sought_path.top().get_left_successor()->set_marked(true);
        sought_path.push(*sought_path.top().get_left_successor());
        find_path(sought_path,given_leaf);
    }
    if(sought_path.top().get_right_successor()!=NULL&& sought_path.top().get_right_successor()->is_marked()==false){
        sought_path.top().get_right_successor()->set_marked(true);
        sought_path.push(*sought_path.top().get_right_successor());
        find_path(sought_path,given_leaf);
    }
    if(sought_path.top()==given_leaf){
        return sought_path;
    }
    //now we 've gone to a leaf that is not the one we seek and we cannot go further down
    sought_path.top().set_marked(true);
    if(sought_path.empty()==false){
        sought_path.pop();
    }
    find_path(sought_path,given_leaf);
    return sought_path;
}

/**
 *@brief This function checks if the Vertex exists in the Table and therefore in the Tree
         and if it does exists it uses the find_path function , if not a deffaultly constructed
         Stack is returned.
 *@see find_path(Stack& sought_path,const Vertex& given_leaf)
 *@date 20 01 2016
 *@return Stack containing the sought path.
 */
Stack Tree::find_reversed_path_to_leaf(Stack& sought_path,const Vertex& given_leaf){//this makes sure the leaf actually exists
    bool vertex_exists=false;
    for (int i=0;i<get_count();i++){
        if ( (*(get_start()+i)).get_letter()==given_leaf.get_letter()){
            vertex_exists=true;
        }
    }
    if (vertex_exists){
      return find_path(sought_path,given_leaf);
    }
    return Stack();
}

/**
 *@brief Settter for the compressde bool message length.
 *@date 20 01 2016
 *@return void
 */
void Tree::set_compressed_message_length(unsigned long long int given){
    compressed_message_length=given;
}

/**
 *@brief Settter for the compressed decimal message length.
 *@date 20 01 2016
 *@return void
 */
void Tree::set_compressed_decimal_message_length(unsigned long long int given){
    compressed_decimal_message_length=given;
}

/**
 *@brief This function calculates the compression benefit of the process
         of compressing the initial string into bools.
 *@date 20 01 2016
 *@return The ration of the compressed message length and the lenght of the initial
          string times eight (bool:char = 1:8)
 */
double Tree::calculate_compression_benefit_bools()const{//ration of     (1bit per bool ) / (8bits per char)
    if (message_length==0||compressed_message_length==0){
        return 0;
    }
    return  ((double)get_compressed_message_length()/(double)((get_message_length())*BITS_IN_BYTE));
}


//This function is not used in the current version of the project.
/**
 *@brief This function calculates the compression benefit of the process
         of compressing the initial string into bools and then turning the bools to integers.
         Usually the size of the compessed int message is bigger than that of the initial message!
 *@date 20 01 2016
 *@return The ration of the compressed message length times 2 and the lenght of the initial
          string (short int:char = 2:1)
 */
double Tree::calculate_compression_benefit_integers()const{//ration of     (2bytes per short int) / (1byte per char)
    if (message_length==0||compressed_message_length==0){
        return 0;
    }
    return  (  ((double)(get_compressed_decimal_message_length()*2))   /   ((double)((get_message_length())))   );
}

/**
 *@brief This function turns eight or less bools into an integer
         the eight or less bools are treated as a number in base two
         which is being transformed into an integer in base 10.
         For example we are given a pointer into the 5th bool of a bool array with
         length 200 and "given_length" of 4. Then we will use the 5th,6th,7th and 8th
         bool from the array to create an integer with the fith being the senior bit and 8th the
         minor bit.The integer will be = 8th*pow(2,0) +7th*pow(2,1)+6th*pow(2,2)+5th*pow(2,3) .
 *@date 20 01 2016
 *@param given - pointer to a bool which is the first (rightmost) digit of the base-two number
 *@param given_length - the count of bools to be considered a part of the base-two number
 *@return The integer in base 10 equal to the base-two number.
 */
short unsigned int  Tree::convert_bools_to_int(const bool* const given,int given_length)const{
    short unsigned int result=0;
        for (int i=0;i<given_length;i++){
            result+=*(given+i)*(pow(2,(given_length-1-i)));
        }
    return result;
}


//This function is not used in the current version of the project.
/**
 *@brief This function trnsforms an integer into 8 bools repeseinting the integer in binary code
         there might be initial zeroes in front of the base-two number. i.e. 6 can
         be represented as 00000110 or 001110 depending on the given_length parameter.
 *@date 20 01 2016
 *@see transmute(...)
 *@param buffer - bool array storing the binary code representing the integer
 *@param given the integer to be transformed into base two number
 *@param given_length the length of the binary code representing the integer
         (this determines how many initial zeroes the code will have - if the integer is 15
          and given_lengthi is 6 then the code will be 001111)
 *@return void
 */
void Tree::convert_int_to_bools(bool* const buffer,const short unsigned int& given,unsigned long long int given_length)const{
        short int copy_given=given;
        unsigned long long int position=given_length-1;///showing how many bits are at the end (might not be 8)
        if (copy_given==0){//if the integer number is 0 from the start
            *(buffer+position)=false;
            position-=1;
        }
        while(copy_given!=0){
            if (copy_given%2==0){
                *(buffer+position)=false;
            }
            else {
                *(buffer+position)=true;
            }
            position-=1;
            copy_given/=2;
        }
        for (;position>=0;position--){//adding initial zeroes if needed
            *(buffer+position)=false;
        }
    }


//This function is not used in the current version of the project.
/**
 *@brief helping function for decompress_decimal_message
         this function transmutes a compressed message in the form of int array
         into a compressed message in the form of bool array
         we can decompress a message only if it is in the form of a bool array;
 *@see convert_int_to_bools(...)
 *@date 20 01 2016
 *@return void
*/
void Tree::transmute(bool* receiver,const short unsigned int* const given,const unsigned long long int& length)const{
    if(*(given+length-1)!=0){//in this case the last integer was formed by less than 8 bits, tha last int in the array
        bool temporary[BITS_IN_BYTE];  //is equal to that number of bits(remnant), this way the last int will be transformed properly
        unsigned long long int j=0;
        for (unsigned long long int i=0;i<length-2;i++){
            convert_int_to_bools(temporary,*(given+i),BITS_IN_BYTE);
            for (;j<BITS_IN_BYTE*(i+1);j++){
                *(receiver+j)=*(temporary+(j%BITS_IN_BYTE));
            }
        }
        bool* temporary_dynamic=new bool [*(given+length-1)];//last int is the remnant
        convert_int_to_bools(temporary_dynamic,*(given+length-2),*(given+length-1));
        for (unsigned long long int k=0;k<*(given+length-1);k++){
            *(receiver+j+k)=*(temporary_dynamic+k);
        }
        delete [] temporary_dynamic;
    }
    else {//in this case no remainder exists (the last integer was also formed from 8 bools)
        bool temporary[BITS_IN_BYTE];
        unsigned long long int j=0;
        for (unsigned long long int i=0;i<length-1;i++){
            convert_int_to_bools(temporary,*(given+i),BITS_IN_BYTE);
            for (;j<BITS_IN_BYTE*(i+1);j++){
                *(receiver+j)=*(temporary+(j%BITS_IN_BYTE));
            }
        }
    }
}


/**
 *@brief decompresses a single letter from the bool code by
         going through the code itself and the Tree
         for each 0 in the code we go left in the tree
         for each 1 in the code we go right in the tree
         when we reach a leaf we get the letter of that Vertex
 *@param pseudonym of a pointer to the current position in the bool code
 *@date 20 01 2016
 *@return a letter from the initial message
 */
char Tree::decompress_letter(const bool*& position)const{
    const Vertex* tree_pointer=root;//take the root
    while (!(tree_pointer->get_left_successor()==NULL && tree_pointer->get_right_successor()==NULL)){//while not a leaf
        if (*position==true){ //if 1 go right
            tree_pointer=tree_pointer->get_right_successor();
        }
        else{ //else go left
            tree_pointer=tree_pointer->get_left_successor();
        }
        position=position+1; //increase position in code
    }
    return tree_pointer->get_letter(); // when a leaf is reached return the letter of that Vertex
}

/**
 *@brief this function decompesses the bool message into a buffer
         and then writes that buffer down in a file
 *@param given - the bool array representing the bool code that is to be decompressed
 *@param decompressed_length - the length of the initial input message
 *@param decompress_to - the name of the file for the decompressed message to be written down in
 *@see decompress_letter(...)
 *@date 20 01 2016
 *@return void
 */
void Tree::decompress_bool_message(const bool* const given,const unsigned long long int& decompressed_length,const char* decompress_to)const{
    char* receiver= new char[decompressed_length+1];//no check for the lenght of the compressed bool message is needed because
    receiver[decompressed_length]='\0';             //it has been created by the initial string, so when the initial string s lenght
    const bool* pointer=given;                      //has been reached then the compressed bool message has also been reached
    for (unsigned long long int i=0;i<decompressed_length;i++){
        receiver[i]=decompress_letter(pointer);
    }
    fstream decompression(decompress_to,ios::out|ios::trunc);//writes into a file the decompressed message
    for (unsigned long long int i=0;i<decompressed_length;i++){
        decompression<<*(receiver+i);
    }
    decompression.close();
    delete []receiver; //deletes the temporary array holding the decompressed message
    return;
}

//This function is not used in the current version of the project.
/**
 *@brief This function decompresses a int compressed message (a bool compressed message transformed into integers)
         A buffer big enough to store the bool compressed fom of the int compressed message is created.
         After that the int compressed message is trasmuted into a bool compressed message.
         Then the bool compessed message is decompressed.
 *@param given - the int compressed message
 *@param expected_bool_arr_length - the length of the bool compressed message
 *@param given_int_arr_length - the lenght of the int compessed message
 *@param decompress_length - the lenght of the decompessed message
 *@param decompress_to - the name of the file for the decompressed message to be written down in
 *@see transmute(...)
 *@see decompress_bool_message(...)
 *@date 20 01 2016
 *@return void
*/
void Tree::decompress_decimal_message(const short unsigned int* const given,const unsigned long long int& expected_bool_arr_length,const unsigned long long int& given_int_arr_length,const unsigned long long int& decompressed_length,const char* decompress_to)const{
    bool* arr =new bool [expected_bool_arr_length];
    transmute(arr,given,given_int_arr_length);
    decompress_bool_message(arr,decompressed_length,decompress_to);
    delete [] arr;
}

//This function is not used in the current version of the project.
/**
 *@brief This function decompresses a binary file holding a bool compressed message.
         First the PackedBytes stored in the file are being "unpacked" and then the
         restored bool message is being decompressed using the decompress_bool_message(...) function
 *@date 20 01 2016
 *@param filename_from - the name of the binary file from which the compressed bool message will be read
 *@param filename_to - the name of the text file in which the decompessed message will be written down in
 *@see decompress_bool_message(...)
 *@see PackedByte
 *@return void
*/
void Tree::decompress_file(const char* filename_from,const char* filename_to)const{
    fstream fs(filename_from,ios::binary|ios::in);
    unsigned long long int decompressed_message_length=0;
    unsigned long long int PackedBytesCount=0;
    int leftovers = 0;

    fs.read( (char*)& decompressed_message_length,sizeof(unsigned long long int));
    fs.read( (char*)& PackedBytesCount,sizeof(unsigned long long int));
    fs.read( (char*)& leftovers,sizeof(int));

    unsigned long long int bool_compressed_length=BITS_IN_BYTE*PackedBytesCount;
    if (leftovers!=0){
        bool_compressed_length-=BITS_IN_BYTE;
        bool_compressed_length+=leftovers;
    }

    bool* bool_compressed = new bool [bool_compressed_length];

    PackedByte* packed=new PackedByte[PackedBytesCount];
    for (unsigned long long int i=0;i<PackedBytesCount;i++){
        fs.read( (char*)& packed[i],sizeof(PackedByte));
    }
    fs.close();


    if(leftovers == 0){
        for (unsigned long long int i=0;i<PackedBytesCount;i++){
            for (int j=0;j<BITS_IN_BYTE;j++){
                *(bool_compressed + (i*BITS_IN_BYTE) +j)= packed[i].get_bit(j);
            }
        }
    }

    else if (leftovers!=0){
        for (unsigned long long int i=0;i<PackedBytesCount-1;i++){
            for (int j=0;j<BITS_IN_BYTE;j++){
                *(bool_compressed + (i*BITS_IN_BYTE) +j)= packed[i].get_bit(j);
            }
        }

        for (int f=0;f<leftovers;f++){
            *(bool_compressed + (PackedBytesCount-1)*BITS_IN_BYTE +f) = packed[PackedBytesCount-1].get_bit(BITS_IN_BYTE-leftovers+f);
        }
    }
    const bool* const bool_compressed_msg=bool_compressed;

    decompress_bool_message(bool_compressed_msg,decompressed_message_length,filename_to);

    delete [] bool_compressed;
    delete [] packed;
}

//This function is not used in the current version of the project
/**
 *@brief this function decompresses a stored bool messsag in binary file
         using a Table object stored in another binary file.First a Tree object
         is created from the Table and then the message is decompressed throuh that Tree
         and written down in a textfile
 *@date 20 01 2016
 *@param TableData - the name of a binary file holding a Table object
 *@param CodeData - the name of a binary file holding the bool Code of the initial message
 *@param Decompessed - the name of a textfile in which the Decompressed message will be written down
 *@see Table
 *@see decompress_file(...)
 *@return void
*/
void decompress_through_table(const char* TableData,const char* CodeData,const char* Decompressed){
    Tree proba2(TableData);
    proba2.decompress_file(CodeData,Decompressed);
}

/**
 *@brief This function is an outclass function.It creates a Tree from a string in a textfile, and then compesses that string
         through the just built Tree.
 *@date 20 01 2016
 *@param from - the name of the textfile from which the initial string message will be read
 *@param code_to - the name of the binary file in which the bool compessed message will be written down in
 *@param tree_to - the name of the binary file in which the a NodeTree will be written down in
 *@param bool_code_to - NULL by deffault, if specified then the bool code will be wirtten down in a readable text file with the specified name
 *@param int_code_to - NULL by deffault, if specified then the int code will be wirtten down in a readable text file with the specified name
 *@see NodeTree
 *@return void
*/
void Compress(const char* from,const char* code_to,const char* tree_to,const char* bool_code_to,const char* int_code_to){
    Tree compress_tree(from,code_to,tree_to,bool_code_to,int_code_to);
    cout<<"Compression benefit: "<<compress_tree.calculate_compression_benefit_bools()<<endl;
}
