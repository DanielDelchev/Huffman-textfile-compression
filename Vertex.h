#ifndef VERTEX_H_INCLUDED
#define VERTEX_H_INCLUDED

#include <iomanip>
#include <iostream>
#include <cstring>
#include "windows.h"
#include <cmath>
#include <fstream>
using namespace std;

/**
 *@brief Objects of the Vertex class are used to build the Huffmann Tree in the Tree class.
         A Vertex contains data for the Vertex itself, pointer to left successor and pointer to right successor
         in constrast to the objects of the Node class which contain no pointers and therefore
         can be serialized easily.Objects of this class are used to build the frequency table, the Huffmann tree
         and the serializable Nodes used for the serialiszble NodeTree.This class is in the basis of the structure of
         the program.
 *@see Tree
 *@see Node
 *@date 20 01 2016
 */
class Vertex{
public:
    //getters
    Vertex* get_left_successor()const;
    Vertex* get_right_successor()const;
    char get_letter()const;
    unsigned long int get_repetitions()const;
    bool* get_code()const;
    int get_code_length()const;
    bool is_marked()const;
    char get_special_ID()const;
    int get_Node_ID()const;
    //setters
    void set_left_successor(Vertex* given);
    void set_right_successor(Vertex* given);
    void set_letter(const char& given);
    void set_repetitions(const unsigned long int& given);
    void set_code(const bool* given,const int& length);
    void set_code_length(const int& given);
    void set_marked(bool given);
    void set_special_ID(char given);
    void set_Node_ID(int given);
    //great 4
    virtual ~Vertex();
    Vertex();
    Vertex(const Vertex& given);//as a result the object HAS THE EXACT SAME SUCCESSORS given has got
    Vertex& operator=(const Vertex& given);// as a result the object HAS THE EXACT SAME SUCCESSORS given has got
    void copy(const Vertex& given);// copies the EXACT SAME successors "given" has got */
    void destroy();

    //operators & functions
    friend  ostream& operator<<(ostream& os,const Vertex& given);
    bool operator==(const Vertex& given)const;
    bool operator>(const Vertex& given)const;
    bool operator>=(const Vertex& given)const;
    bool operator<(const Vertex& given)const;
    bool operator<=(const Vertex& given)const;
    bool special_comparison(const Vertex& given)const;
    void increase_repetitions(){repetitions+=1;}
    void add_bit_to_code(const bool& given);
private:
    Vertex* left_successor;     /**< pointer to the left successor of the Vertex */
    Vertex* right_successor;     /**< pointer to the right successor of the Vertex */
    char letter;     /**< if it is not a vertex it will be initilized with 'Ù' (invalid char) */
    unsigned long int repetitions;     /**< repetitions of the character of the Vertex in the string */
    bool* code;   /**< the beginning of a bool array representing the code of the Vertex */
    int code_length;   /**< the length of the bool array */
    bool marked;     /**< bool used to check if the Vertex has been marked (used in traversing, building trees and other situations)*/
    char special_ID;   /**< tells us if this vertex is a right (R) successor or left (L) successor of its parent */
    int Node_ID;    /**< allows distingushing between non-leaf vertices */
};



#endif // VERTEX_H_INCLUDED
