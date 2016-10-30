#ifndef TABLE_H_INCLUDED
#define TABLE_H_INCLUDED
#include "Vertex.h"


const int utter_limit=300; /**< 300 is utter limit for the size of the Table ,256 is maximum number of possible chars (extended ASCII)*/

/**
 *@brief This class represents the frequency table used to build the Huffmann tree.
         Its purpose is to count how many times each letter is found in the input string,
         create a Vertex for each such letter, and store them in a Vertex array.
         It is inheited by the Tree class for later use.
 *@see Tree
 *@date 20 01 2016
 */
class Table{
public:

    void write_down_table(const char* to)const;
    void read_table(const char* from);

    Table();
    Table(char* given);
    Table(const char* from,const char* to=NULL);
    Table(string result,const char* to=NULL);

    Table(const Table& given);
    virtual ~Table();
    Table& operator=(const Table& given);

    friend istream& operator>>(istream& is,Table& given);
    friend ostream& operator<<(ostream& os,const Table& given);


    Vertex* get_start()const;//gets the beginning of the leaves array
    int get_count()const;
    int get_current_limit()const;
    void sort_ascending();
    void sort_descending();
    Vertex* find_max()const;
    Vertex* find_min()const;

    void add_vertex(const Vertex& given);
    void remove_vertex(const Vertex& given);
    bool found_vertex(char)const;//finds if a specific letter is in the message
    Vertex* find_vertex(char)const;//finds if a specific letter is in the message, and how many times it occurs,returns a Vertex* or NULL

    bool empty()const{return count==0;}
    bool full()const{return count==utter_limit;}

private:
    void set_current_limit(int given);     /**< setter for the current limit (capacity) of the Vertex array */
    void set_count(int given);     /**< setter for the current count (size) of the Vertex array */
    void increase_current_limit();     /**< increases the limit (capacity) of the Vertex array */
    Vertex* resize(Vertex* given_leaves_array,int given_count);      /**< resizing function for the Vertex array */
    void destroy();     /**< destroy function used in the destructor of the class */
    void copy(const Table& given);     /**< copy function used in operator= and copy constructor of the class */
    int count;     /**< The number of Vertecies in the Table */
    Vertex* leaves_array;     /**< The Vertex* array used to store the Vertecies (dynamic memory for the array is handled manually) */
    int current_limit;    /**< The current limit (capacity) of the array */
};

//functions for Vertex arrays that are not part of class Table or Tree
Vertex* find_max_outclass(Vertex* given,int counter);
Vertex* find_first_unmarked_outclass(Vertex* given,int counter);
Vertex* find_unmarked_min_outclass(Vertex* given,int counter);
Vertex* find_vertex_outclass(Vertex* given,int counter,char given_letter);
bool found_vertex_outclass(Vertex* given,int counter,char given_letter);
bool unmarked_not_found(Vertex* given,int counter);
void sort_ascending_outclass(Vertex* given,int counter);

#endif // TABLE_H_INCLUDED
