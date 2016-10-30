#include "Vertex.h"

/**
 *@brief operator > for the class
 *@param second vertex to compare with
 *@return true if this Vertex's repetitions are more than  the second one's , false othewrwise
 *@date 20 01 2016
 */
bool Vertex::operator>(const Vertex& given)const{
    return ((this->repetitions)>given.get_repetitions());
}
/**
 *@brief operator >= for the class
 *@param second vertex to compare with
 *@return true if this Vertex's repetitions are more than  or equal to the second one's , false othewrwise
 *@date 20 01 2016
 */
bool Vertex::operator>=(const Vertex& given)const{
    return ((this->repetitions)>=given.get_repetitions());
}
/**
 *@brief operator < for the class
 *@param second vertex to compare with
 *@return true if this Vertex's repetitions are less than  the second one's , false othewrwise
 *@date 20 01 2016
 */
bool Vertex::operator<(const Vertex& given)const{
    return ((this->repetitions)<given.get_repetitions());
}
/**
 *@brief operator <= for the class
 *@param second vertex to compare with
 *@return true if this Vertex's repetitions are less than or equal to the second one's , false othewrwise
 *@date 20 01 2016
 */
bool Vertex::operator<=(const Vertex& given)const{
    return ((this->repetitions)<=given.get_repetitions());
}
/**
 *@brief operator == for the class
 *@param second vertex to compare with
 *@return true if this Vertex's repetitions are equal to the second one's , false othewrwise
 *@date 20 01 2016
 */
bool Vertex::operator==(const Vertex& given)const{
    return (given.get_letter()==this->letter && given.get_repetitions()==this->repetitions);
}
/**
 *@brief compares the letters , the repetitions , and the special ID's of the vertecies
 *@param second vertex to compare with
 *@return true if all the letters,repetitions,special ID of the object are equal to those of the second Vertex, false otherwise
 *@date 20 01 2016
 */
bool Vertex::special_comparison(const Vertex& given)const{
    return (given.get_letter()==this->letter && given.get_repetitions()==this->repetitions&& given.get_special_ID()==this->special_ID);
}
/**
 *@brief operator<< for the class
 *@date 20 01 2016
 */
ostream& operator<<(ostream& os,const Vertex& given){
    os<<"letter:"<<given.get_letter()<<" ,repetitions:"<<given.get_repetitions();
    os<<" ,code length:"<<given.get_code_length()<<" ,code:";
    if(given.get_code()==NULL){
        os<<"N/A";
    }
    if (given.get_code()!=NULL){
        for (int i=0;i<given.get_code_length();i++){
            os<<*(given.get_code()+i);
        }
    }
    os<<endl;
    return os;
}
/**
 *@brief getter for the left successor of the Vertex
 *@date 20 01 2016
 *@return pointer to the left successor of the Vertex
 */
Vertex* Vertex::get_left_successor()const{
    return left_successor;
}
/**
 *@brief getter for the right successor of the Vertex
 *@date 20 01 2016
 *@return pointer to the right successor of the Vertex
 */
Vertex* Vertex::get_right_successor()const{
    return right_successor;
}

/**
 *@brief getter for the letter of the Vertex
 *@date 20 01 2016
 *@return the letter of the Vertex
 */
char Vertex::get_letter()const{
    return letter;
}

/**
 *@brief getter for the repetitions of the letter of the Vertex
 *@date 20 01 2016
 *@return the repetitions of the letter of the Vertex
 */
unsigned long int Vertex::get_repetitions()const{
    return repetitions;
}

/**
 *@brief getter for the code of the Vertex
 *@date 20 01 2016
 *@return the code of the Vertex
 */
bool* Vertex::get_code()const{//returns the beginning of a bool array representing the code
    return code;
}

/**
 *@brief getter for the length of the code of the Vertex
 *@date 20 01 2016
 *@return the length of the code of the Vertex
 */
int Vertex::get_code_length()const{
    return code_length;
}
/**
 *@brief getter for the marked state of the Vertex
 *@date 20 01 2016
 *@return true if the Vertex is marked, false otherwise
 */
bool Vertex::is_marked()const{
    return marked;
}
/**
 *@brief getter for the special_ID of the Vertex
 *@date 20 01 2016
 *@return the special ID of the Vertex
 */
char Vertex::get_special_ID()const{
    return special_ID;
}
/**
 *@brief getter for the Node_ID of the Vertex
 *@date 20 01 2016
 *@return the Node ID of the Vertex
 */
int Vertex::get_Node_ID()const{
    return Node_ID;
}
/**
 *@brief setter for the left successor of the Vertex
 *@date 20 01 2016
 *@param given - a pointer to a Vertex to be set as a left successor
 *@return void
 */
void Vertex::set_left_successor(Vertex* given){
    left_successor=given;
}
/**
 *@brief setter for the right successor of the Vertex
 *@date 20 01 2016
 *@param given - a pointer to a Vertex to be set as a right successor
 *@return void
 */
void Vertex::set_right_successor(Vertex* given){
    right_successor=given;
}
/**
 *@brief setter for the letter of the Vertex
 *@date 20 01 2016
 *@param given - a char to be set as the letter
 *@return void
 */
void Vertex::set_letter(const char& given){
    letter=given;
}
/**
 *@brief setter for the repetitions of the letter of the Vertex
 *@date 20 01 2016
 *@param given - an int to be set as the repetitions
 *@return void
 */
void Vertex::set_repetitions(const unsigned long int& given){
    repetitions=given;
}
/**
 *@brief setter for the code of the Vertex
         deletes the previous code and replaces it with the given bool array
         also assigns the code length to be equal to the length of the new code
 *@date 20 01 2016
 *@param given - pointer to a beginning of an bool array
 *@param length - the legth of that bool array
 *@return void
 */
void Vertex::set_code(const bool* given,const int& length){
    if (code!=NULL){
        delete [] code;
    }
    if (given==NULL){
        code=NULL;
        set_code_length(0);
        return;
    }
    code=new bool[length];
    for (int i=0;i<length;i++){
        code[i]=given[i];
    }
    code_length=length;

}
/**
 *@brief setter for the code length of the Vertex
 *@date 20 01 2016
 *@param given - an integer to be set as the length
 *@return void
 */
void Vertex::set_code_length(const int& given){
    code_length=given;
}

/**
 *@brief setter for the marked state of the Vertex
 *@date 20 01 2016
 *@param given - a bool to be set as the marked state of the Vertex
 *@return void
 */
void Vertex::set_marked(bool given){
    marked=given;
}
/**
 *@brief setter for the special ID of the Vertex
 *@date 20 01 2016
 *@param given - a char to be set as the special ID of the Vertex.Presumably R for right and L for left
 *@return void
 */
void Vertex::set_special_ID(char given){
    special_ID=given;
}
/**
 *@brief setter for the Node_ID of the Vertex
 *@date 20 01 2016
 *@param given - an intege to be set as the Node_ID
 *@return void
 */
void Vertex::set_Node_ID(int given){
    Node_ID=given;
}

/**
 *@brief deffault constructor of a Vertex
 *@date 20 01 2016
 */
Vertex::Vertex():left_successor(NULL),right_successor(NULL),code(NULL){
    set_Node_ID(-1);
    set_special_ID('M');
    set_code_length(0);
    set_repetitions(0);
    set_marked(false);
    set_letter('Ù');//will be initialized with a proper letter later if it is a leaf
}

/**
 *@brief destroy function used in the destructor of the class
 *@date 20 01 2016
 *@see ~Vertex()
 *@return void
 */
void Vertex::destroy(){
    if (this!=NULL){
        delete [] code;
    }
}

/**
 *@brief virtual destructor for the class
 *@date 20 01 2016
 *@see destroy()
 */
Vertex::~Vertex(){
    destroy();
}

/**
 *@brief copy function used in operator= and copy constructor of the class
 *@date 20 01 2016
 *@param given - the Vertex to be copied
 */
void Vertex::copy(const Vertex& given){
    set_repetitions(given.get_repetitions());
    set_letter(given.get_letter());
    set_code_length(given.get_code_length());
    set_left_successor(given.get_left_successor());
    set_right_successor(given.get_right_successor());
    set_code(given.get_code(),given.get_code_length());
    set_marked(given.is_marked());
    set_special_ID(given.get_special_ID());
    set_Node_ID(given.get_Node_ID());
}

/**
 *@brief copy constructor for the class
 *@date 20 01 2016
 *@param given - the Vertex to be copied
 */
Vertex::Vertex(const Vertex& given):left_successor(NULL),right_successor(NULL),code(NULL){
    copy(given);
}

/**
 *@brief operator= for the class
 *@date 20 01 2016
 *@param given - the Vertex to be used as a rvalue of the assignment
 */
Vertex& Vertex::operator=(const Vertex& given){
    if (this!=&given){
        destroy();
        copy(given);
    }
    return *this;
}

/**
 *@brief adds a bit (a bool) at the end of code of the Vertex
         also increases the length of the code by 1
 *@date 20 01 2016
 *@param given - a bool to be added at the end of the code of the Vertex
 */
void Vertex::add_bit_to_code(const bool& given){
    int length=get_code_length();
    bool* newmemo=new bool[length+1];
    for (int i=0;i<length;i++){
        newmemo[i]=code[i];
    }
    newmemo[length]=given;
    delete [] code;
    code=newmemo;
    set_code_length(length+1);
}
