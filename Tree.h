#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED
#include "Table.h"
#include "Stack.h"
#include "my_bitwise.h"

/**
 *@brief This class builds the Huffmann Tree for the compression.It inherits a Table containing the leaves of the tree
         the Tree is built from the bottom-up,after that codes are assigned to all leaves in the table, then the string
         is compressed using the codes.If specified to do so by the constructor used, the Tree is transformed in a
         form  appropriate for serialization and is written down in a binary file.The compressed string into code is also
         written down in a binary file.That way after the program is closed, the string can still be restored later on
         when needed.
 *@date 20 01 2016
 */
class Tree:public Table{
public:
    Tree();//deffault constructor
    Tree(char* given);//Builds the tree (and the table it inherits) from a char string.No file work here.
    Tree(const Table& given); //builds the tree from an already built Table object
    Tree(const char* filename);//reads a Table from "filename" and bulds a Tree from that table
    Tree (const char* from,const char* code_to,const char* tree_to,const char* bool_code_to=NULL,const char* int_code_to=NULL);//builds the tree from a textfile
    Tree(const Tree& given);
    virtual ~Tree();
    Tree& operator=(const Tree& given);

    friend istream& operator>>(istream& is,Tree& given);
    friend ostream& operator<<(ostream& os,const Tree& given);

    void print_table()const;
    void print_compressed_message()const;
    void print_compressed_decimal_message()const;

    Vertex* get_root()const;
    bool* get_compressed_message()const;
    short unsigned int* get_compressed_decimal_message()const;
    unsigned long long int get_compressed_message_length()const;
    unsigned long long int get_message_length()const;
    unsigned long long int get_compressed_decimal_message_length()const;

    char decompress_letter(const bool*& given)const;
    void decompress_bool_message(const bool* const given,const unsigned long long int& decompressed_length,const char* decompress_to)const;
    void decompress_decimal_message(const short unsigned int* const given,const unsigned long long int& expected_bool_arr_length,const unsigned long long int& given_int_arr_length,const unsigned long long int& decompressed_length,const char* decompress_to)const;
    void decompress_file(const char* filename_form,const char* filename_to)const;

    short unsigned int convert_bools_to_int(const bool* const given,int given_length)const;//only returns the int that 8 bools make, does not alter anything by itself

    void convert_int_to_bools(bool* const buffer,const short unsigned int& given,unsigned long long int given_length)const;//converts an int piece of code to a bool piece of code with length = "given_length"
    void transmute(bool* receiver, const short unsigned int* const given,const unsigned long long int& length)const;//transmute a int array of code to bool array

    void print_tree(Vertex* given)const;
    double calculate_compression_benefit_bools()const;
    double calculate_compression_benefit_integers()const;

private:
    void set_message_length(unsigned long long int given);/**< Setter for the input (unaltered) message length */
    void set_compressed_message_length(unsigned long long int given);/**< Setter for the compressed (bool) message length */
    void set_compressed_decimal_message_length(unsigned long long int given);/**< Setter for the compressed (decimal) message length */
    Vertex* copy_tree(Vertex* given);/**< Copies the tree  */
    void destroy_tree(Vertex* given);/**< Destroys the tree  */
    void refresh_tree(Vertex* given);/**< This restores the markers of all the vertices in the tree to false. */
    bool found_leaf_in_tree(Vertex* root,const Vertex& sought)const; /**< Cheks if a specific leaf exists in the Tree  */
    Vertex* find_leaf_in_tree(Vertex* root,const Vertex& sought)const; /**< Finds a pointer to a specific Vertex in the Tree */
    Stack find_reversed_path_to_leaf(Stack& sought_path,const Vertex& given_leaf);/**< Finds the reverse path to a leaf (the path from the leaf to the root) */
    Stack find_path(Stack& sought_path,const Vertex& given_leaf);/**< This also finds the path but does not perform a check whether the specific Vertex exists */
    void copy(const Tree& given);/**< Copy function */
    void destroy(); /**< Destroy function */
    unsigned long long int message_length;/**< The length of the input message */ //It is stores so it can be compared to the lenght of the compressed message
    Vertex* root; /**< The root of the Huffmann tree */
    bool* compressed_message;/**< Keeps the compressed form of the intput string from which the Tree has been built. */
    unsigned long long int compressed_message_length; /**< Keeps the  lenght of the compressed bool message. */
    unsigned long long int compressed_decimal_message_length; /**< Keeps the compressed integer form of the input string from which the Tree has been built. */
    short unsigned int* compressed_decimal_message; /**< Keeps the  lenght of the compressed decimal message. */
};

void decompress_through_table(const char* TableData,const char* CodeData,const char* Decompressed);//not used in this version of the project
void Compress(const char* from,const char* code_to,const char* tree_to,const char* bool_code_to=NULL,const char* int_code_to=NULL);
#endif // TREE_H_INCLUDED
