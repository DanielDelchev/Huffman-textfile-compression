#include "Table.h"

/**
 *@brief Deffault constructor for the class.Generates an empty Table with initial capacity of 50 vertecies that can be expanded later on up untill 300 .
 *@date 20 01 2016
 */
Table::Table():count(0),leaves_array(NULL){
    leaves_array=new Vertex[50];
    current_limit=50;
};

/**
 *@brief Private destroy function used in the class destructor
 *@see ~Table();
 *@date 20 01 2016
 *@return void
 */
void Table::destroy(){
    delete [] leaves_array;
}

/**
 *@brief Virtual destructor for the class
 *@see destroy();
 *@date 20 01 2016
 */
Table::~Table(){
    destroy();
}

/**
 *@brief Getter for the array of Vertices (all of which will be leaves in the Huffmann tree)
 *@see Vertex
 *@date 20 01 2016
 *@return Pointer to the beginning of the Vertex array
 */
Vertex* Table::get_start()const{
    return leaves_array;
}
/**
 *@brief Getter for the count (size) of the array of Vertices
 *@see Vertex
 *@date 20 01 2016
 *@return the current size of the Table
 */
int Table::get_count()const{
    return count;
}

/**
 *@brief Getter for the current limit (capacity) of the array of Vertices
 *@see Vertex
 *@date 20 01 2016
 *@return the current capacity of the Table
 */
int Table::get_current_limit()const{
    return current_limit;
}

/**
 *@brief Private copy function used in operator= and copy constructor of the class
 *@date 20 01 2016
 *@param given - the Table to be copied
 *@see Table(const Table& given)
 *@see Table& operator= (const Table& given)
 *@return void
 */
void Table::copy(const Table& given){
    current_limit=given.get_current_limit();
    count=given.get_count();
    Vertex* newmemo=new Vertex[current_limit];
    leaves_array=newmemo;
    for (int i=0;i<count;i++){
        leaves_array[i]=*(given.get_start()+i);
    }
}
/**
 *@brief Copy constructo of the class
 *@param given - the table to be copied
 *@date 20 01 2016
 *@see copy()
 */
Table::Table(const Table& given):leaves_array(NULL){
    copy(given);
}

/**
 *@brief operator= for the class
 *@date 20 01 2016
 *@param given - the rvalue of the assignment
 *@see copy()
 *@see destroy()
 */
Table& Table::operator=(const Table& given){
    if (this!=&given){
        destroy();
        copy(given);
    }
    return *this;
}

/**
 *@brief Increases the current limit (capacity) of the Table with 50
 *@date 20 01 2016
 *@return void
 */
void Table::increase_current_limit(){
    current_limit+=50;
}
/**
 *@brief setter for the current limit of the Table
 *@param given - the new current limit
 *@date 20 01 2016
 *@return void
 */
void Table::set_current_limit(int given){
    current_limit=given;
}
/**
 *@brief setter for the current count (size) of the Table
 *@param given - the new current count
 *@date 20 01 2016
 *@return void
 */
void Table::set_count(int given){
    count=given;
}

/**
 *@brief Adds a new Vertex to the table
 *@param given - the Vertex to be added
 *@date 20 01 2016
 *@see resize()
 *@return void
 */
void Table::add_vertex(const Vertex& given){
    if (count==utter_limit){//if no more can be added
        cout<<"Leaves array  too full!"<<endl;
        return;
    }
    else if(count==current_limit){//if table needs to be extended
        leaves_array=resize(leaves_array,count);
    }
    //we just add a Vertex and increase the count
    leaves_array[count]=given;
    count++;
}
/**
 *@brief private function resizing the array of Vertices (memory reallocation is performed)
 *@param given_leaves_array - the array to be resized
 *@param given_count -  the size of that array
 *@date 20 01 2016
 *@return a new Vertex array with the same count and content but with bigger capacity (limit)
 */
Vertex* Table::resize(Vertex* given_leaves_array,int given_count){
    Vertex* newmemo=new Vertex[current_limit+50];
    for (int i=0;i<given_count;i++){
        newmemo[i]=given_leaves_array[i];
    }
    increase_current_limit();
    delete [] leaves_array;
    return newmemo;
}

/**
 *@brief operator << for the class
 *@date 20 01 2016
 */
ostream& operator<<(ostream& os,const Table& given){
    os<<"Current count:"<<given.get_count();
    os<<" ,Current limit:"<<given.get_current_limit();
    os<<" ,Utter limit:"<<utter_limit;
    os<<" ,Number of leaves:"<<given.get_count()<<endl;
    for (int i=0;i<given.get_count();i++){
        os<<"Vertex "<<i<<":"<<*(given.get_start()+i);
    }
    return os;
}

/**
 *@brief finds a Vetex in the Table using its letter for the search key
 *@param given - the letter of the Vertex we are searching for
 *@date 20 01 2016
 *@return Pointe to the Vertex with letter "given" in the Table or NULL if no such Vertex was found
 */
Vertex* Table::find_vertex(char given)const{//can find only leaves
    for (int i=0;i<count;i++){
        if ((leaves_array+i)->get_letter()==given){
            return (leaves_array+i);
        }
    }
    return NULL;
}
/**
 *@brief finds if a Vetex with letter "given" is in the Table
 *@param given - the letter of the Vertex we are searching for
 *@date 20 01 2016
 *@return true if such Vertex was found , false otherwise
 */
bool Table::found_vertex(char given)const{//can find only leaves
    bool found=false;
    for (int i=0;i<count;i++){
        if ((leaves_array+i)->get_letter()==given){
            found=true;
        }
    }
    return found;
}

/**
 *@brief removes a Verrtex from the Table by removing it from the array and "pulling" it to the left with 1 position
 *@param given - the Vertex we want to remove
 *@date 20 01 2016
 *@return void
 */
void Table::remove_vertex(const Vertex& given){
    if (!found_vertex(given.get_letter())){
        return;
    }

    else {  int position=0;
            for (int i=0;i<count;i++){
                if(given==(*(leaves_array+i))){
                    position=i;
                }
            }
            for (int i=position;i<count-1;i++){
                leaves_array[i]=leaves_array[i+1];
            }
            count--;
        }
}

/**
 *@brief sorts the Table (the Vertex array) in an ascending manner (by repetitions)
 *@date 20 01 2016
 *@return void
 */
void Table::sort_ascending(){
    for (int i=0;i<count-1;i++){
    int min_pos=i;
        for (int j=i+1;j<count;j++){
            if (leaves_array[j]<leaves_array[min_pos]){
                min_pos=j;
            }
        }
        swap(leaves_array[i],leaves_array[min_pos]);
    }
}

/**
 *@brief sorts the Table (the Vertex array) in an descending manner (by repetitions)
 *@date 20 01 2016
 *@return void
 */
void Table::sort_descending(){
    for (int i=0;i<count-1;i++){
    int max_pos=i;
        for (int j=i+1;j<count;j++){
            if (leaves_array[j]>leaves_array[max_pos]){
                max_pos=j;
            }
        }
        swap(leaves_array[i],leaves_array[max_pos]);
    }
}
/**
 *@brief sorts the Vertex in the table with the most repetitions (if there are more than 1 such vertices ,one of them is returned)
 *@date 20 01 2016
 *@return Pointer to the Vertex from the Table ,that has most repetitions , or NULL if the Table is empty
 */
Vertex* Table::find_max()const{
    if(this->empty()){
        return NULL;
    }
    int max_pos=0;
    for (int i=0;i<count;i++){
        if (leaves_array[i]>leaves_array[max_pos]){
            max_pos=i;
        }
    }
    return &leaves_array[max_pos];
}

/**
 *@brief sorts the Vertex in the table with the most repetitions (if there are more than 1 such vertices ,one of them is returned)
 *@date 20 01 2016
 *@return Pointer to the Vertex from the Table ,that has most repetitions , or NULL if the Table is empty
 */
Vertex* Table::find_min()const{
    if(this->empty()){
        return NULL;
    }
    int min_pos=0;
    for (int i=0;i<count;i++){
        if (leaves_array[i]<leaves_array[min_pos]){
            min_pos=i;
        }
    }
    return &leaves_array[min_pos];
}


/**
 *@brief Table constructor
         that goes through the char string char by char and cheks if there already
         is a Vertex with the corresponding letter if no, then a new Vertex is added
         to the Table, if yes then the repetitions of that Vertex is increased
 *@date 20 01 2016
 *@param given - a char string
 */
Table::Table(char* given):count(0),leaves_array(NULL),current_limit(50){
    int key_counter=0;
    Vertex* newmemo=new Vertex[50];
    leaves_array=newmemo;
    Vertex temporary;
    int length=strlen(given);
    for (int i=0;i<length;i++){
        if(!found_vertex(given[i])){
            temporary.set_Node_ID((++key_counter));//it is important that no Vertex here gets an ID of zero
            temporary.set_letter(given[i]);
            temporary.set_repetitions(1);
            temporary.set_code(NULL,0);
            temporary.set_code_length(0);
            temporary.set_left_successor(NULL);
            temporary.set_right_successor(NULL);
            add_vertex(temporary);
        }
        else {
                find_vertex(given[i])->increase_repetitions();
        }
    }
}

/**
 *@brief Operator >> for the Class , this used to be used to build a Table
         from a string input in the console.Since it is useful only for short strings
         its purpose is only for betatesting. P.S. no more than 1050 chars can be read from the console using this operator.
 *@date 20 01 2016
 */
istream& operator>>(istream& is,Table& given){
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
        Table temporary(newmemo);
        given=temporary;
    }
    else if (length>=50){
        Table temporary(newmemo2);
        given=temporary;
        delete [] newmemo;
    }
    return is;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//OUTCLASS FUNTCIONS FOR VERTEX ARRAYS

/**
 *@brief looks for a Vertex with a specific lettter in an array of vertices
 *@date 20 01 2016
 *@param given - Pointer to the first Vetex in some array
 *@param counter - the size of that array
 *@param given_letter - the letter of the Vertex we are searching for
 *@return Pointer to the Vertex in the array , or NULL if that Vertex has not been found
 */
Vertex* find_vertex_outclass(Vertex* given,int counter,char given_letter){
    for (int i=0;i<counter;i++){
        if ((given+i)->get_letter()==given_letter){
            return (given+i);
        }
    }
    return NULL;
}

/**
 *@brief looks for a Vertex with a specific lettter in an array of vertices
 *@date 20 01 2016
 *@param given - Pointer to the first Vetex in some array
 *@param counter - the size of that array
 *@param given_letter - the letter of the Vertex we are searching for
 *@return true if the vertex has been found, false otherwise
 */
bool found_vertex_outclass(Vertex* given,int counter,char given_letter){
    bool found=false;
    for (int i=0;i<counter;i++){
        if ((given+i)->get_letter()==given_letter){
            found=true;
        }
    }
    return found;
}
/**
 *@brief sorts a Vertex array
 *@date 20 01 2016
 *@param given - Pointer to the first Vetex in some array
 *@param counter - the size of that array
 *@return void
 */
void sort_ascending_outclass(Vertex* given,int counter){
    for (int i=0;i<counter-1;i++){
    int min_pos=i;
        for (int j=i+1;j<counter;j++){
            if (given[j]<given[min_pos]){
                min_pos=j;
            }
        }
        swap(given[i],given[min_pos]);
    }
}

/**
 *@brief looks for a the Vertex with a the most repetitions in an array of Vertices
 *@date 20 01 2016
 *@param given - Pointer to the first Vetex in some array
 *@param counter - the size of that array
 *@return Pointer to the position of the Vertex with most repetitions , or NULL if the array is empty
 */
Vertex* find_max_outclass(Vertex* given,int counter){
    if(counter==0){
        return NULL;
    }
    int max_pos=0;
    for (int i=0;i<counter;i++){
        if (given[i]>given[max_pos]){
            max_pos=i;
        }
    }
    return &given[max_pos];
}

/**
 *@brief looks for a the Vertex with a the least repetitions in an array of Vertices
 *@date 20 01 2016
 *@param given - Pointer to the first Vetex in some array
 *@param counter - the size of that array
 *@return Pointer to the position of the Vertex with least repetitions , or NULL if the array is empty
 */
Vertex* find_unmarked_min_outclass(Vertex* given,int counter){//това би трябвало да намира минимален елемент който не е включен в дърво (не е наследник на никой друг връх)
    if(counter==0||unmarked_not_found(given,counter)){
        return NULL;
    }
    int min_pos=0;//we first find the first position in the array where a non-marked vertex exists , to use it for comparison in the next cycle
    bool not_found_yet=true;
    for (int i=0;((i<counter)&&(not_found_yet));i++){
        if( ((given+i)->is_marked())==false) {
            min_pos=i;
            not_found_yet=false;
        }
    }

    for (int i=0;i<counter;i++){//this finds the unmarked Vertex with the least repetitions
        //if the given[i] vertex has not been marked as used and it's less than the current minimal vertex
        //assign the minimal element to be given[i]
        if ((((given+i)->is_marked())==false)&&(((given+i)->get_repetitions())<(given[min_pos].get_repetitions()))){
            min_pos=i;
        }
    }
    return &given[min_pos];
}

/**
 *@brief looks for an unmarked Vertex in an array of Vertices
 *@date 20 01 2016
 *@param given - Pointer to the first Vetex in some array
 *@param counter - the size of that array
 *@return true if no such unmarked Vertex is found, false otherwise
 */
bool unmarked_not_found(Vertex* given,int counter){
    bool not_found=true;
    for (int i=0;i<counter;i++){
        if (((given+i)->is_marked())==false){
            not_found=false;
        }
    }
    return not_found;
}
