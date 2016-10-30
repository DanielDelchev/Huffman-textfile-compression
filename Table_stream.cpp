#include "Table.h"

/**
 *@brief This function writes down the Table in a binary file.
         First the count(size) of the is written.
         After that all the vertices are written.
         Vertices can be written directly like that (despite containing pointers)
         because at this point the codes of all of them are NULL.
         In the end the (limit) capacity of the Table is take down.
         This function used to be used when the Node and NodeTree classes
         were not yet available and serializatio and desirialization of the Huffmann
         tree was not anticipated.Currently it is not in use.Yet it is completely functional.
 *@param given - the name of the file in which the Table will be written down.
 *@date 20 01 2016
 *@return void
 */
void Table::write_down_table(const char* given)const{
    fstream fs(given,ios::trunc|ios::binary|ios::out);
    fs.write((const char*)& this->count,sizeof(int));//writes down count
    for (int i=0;i<count;i++){
        fs.write((const char*)& (*(leaves_array+i)),sizeof(Vertex));//writes down all vertecies
    }  //vertices can be written directly like that because at this point the codes of all of them is NULL
    fs.write((const char*)& this->current_limit,sizeof(int));//writes down current_limit
    fs.close();
}
/**
 *@brief Reads a Table from a file and assigns its info to the object that called the function.
         Fist the count (size) is read and assigned to the current object.Then count Vertex are
         read into a temporary Vertex which is then added to the table with
         the function add_vertex(const Vertex* given).Lastly the limit(capacity)
         is read and also assigned to the current object
         This function used to be used when the Node and NodeTree classes
         were not yet available and serializatio and desirialization of the Huffmann
         tree was not anticipated.Currently it is not in use.Yet it is completely functional.
 *@param given - the name of the file in which the Table will be read from.
 *@date 20 01 2016
 *@return void
 */
void Table::read_table(const char* given){
    fstream fs(given,ios::binary|ios::in);
    int counter;
    fs.read((char*)& counter,sizeof(int));//reads the count
    Vertex buffer;
    for (int i=0;i<counter;i++){//read a vertex and add it to the table
        fs.read((char*)& (buffer),sizeof(Vertex));
        add_vertex(buffer);
    }
    fs.read((char*)& (this->current_limit),sizeof(int));//reads the current_limit
    fs.close();
}


/**
 *@brief This constructor reads a string from a text file , builds the table in the same manner
         that it would built it if the input came from the console (creates a new Vertex
         for each new letter met in the string and puts that Vertex in the Table, if the Vertex
         has already been added then only its repetititons get increased) and writes down the
         just built Table into a binary file (if asked to do so ).The reading from the textfile
         into a string is performed with 8KB buffer so as to account for intervals and newlines
         therefore it is presumed that no line in the file will be longer than 8KB.
         Currently the function is not in use.Yet it is completely functional.
 *@param to - the name of the file we would like to write down the Table built from the string
 *@param from - the name of a file containing the string we want to compress with the Huffmann tree
 *@see find_vertex(char letter)
 *@see find_vertex(char letter)
 *@see write_down_table(const char* given);
 *@date 20 01 2016
 */
Table::Table(const char* from,const char* to):count(0),leaves_array(NULL){
    const int MAX=8192; //(8KB buffer)
    leaves_array=new Vertex[50];
    current_limit=50;

    fstream input(from,ios::in);
    char temporary_char;
    Vertex temporary;
    string result;
    char delim = (char)(10); //"\n"
    char temp[MAX];
    while(input.good()){
        input.getline(temp,MAX,delim);                //assuming no line is more than MAX characters
        result += temp;
        if (input.good()){                            //if not the last line, add newline
            result += "\n";
        }
    }
    input.close();

    int key_counter=0;
    string::iterator current=result.begin();
    string::iterator ending=result.end();
    for (;current!=ending;++current){
            temporary_char=(*current);
        if(!found_vertex(temporary_char)){
            temporary.set_Node_ID((++key_counter));
            temporary.set_letter(temporary_char);
            temporary.set_repetitions(1);
            temporary.set_code(NULL,0);
            temporary.set_code_length(0);
            temporary.set_left_successor(NULL);
            temporary.set_right_successor(NULL);
            add_vertex(temporary);
        }
        else {
                find_vertex(temporary_char)->increase_repetitions();
        }
    }
    if (to!=NULL){
        write_down_table(to);
    }
}




/**
 *@brief This constructor is similliar to the one that reads the string from a textfile.
         This one processes the string in the same way, only this constructor needs to be
         given the string as an argument rather than read it from a file.This is vital
         in the Tree constructor that reads a string from a file, so as not to read
         a huge string twice.

 *@param to - the name of the file we would like to write down the Table built from the string
 *@param string - the string we would like to build the Table from
 *@see Tree(const char* from,const char* code_to,const char* tree_to,const char* bool_code_to,const char* int_code_to)
 *@see Table(const char* from,const char* from to)
 *@see find_vertex(char letter)
 *@see add_vertex(const Vertex& given)
 *@see write_down_table(const char* given);
 *@date 20 01 2016
 */
Table::Table(string result,const char* to):count(0),leaves_array(NULL){
    leaves_array=new Vertex[50];
    current_limit=50;

    char temporary_char;
    Vertex temporary;
    int key_counter=0;
    string::iterator current=result.begin();
    string::iterator ending=result.end();
    for (;current!=ending;++current){
            temporary_char=(*current);
        if(!found_vertex(temporary_char)){
            temporary.set_Node_ID((++key_counter));
            temporary.set_letter(temporary_char);
            temporary.set_repetitions(1);
            temporary.set_code(NULL,0);
            temporary.set_code_length(0);
            temporary.set_left_successor(NULL);
            temporary.set_right_successor(NULL);
            add_vertex(temporary);
        }
        else {
                find_vertex(temporary_char)->increase_repetitions();
        }
    }
    if (to!=NULL){
        write_down_table(to);
    }
}
