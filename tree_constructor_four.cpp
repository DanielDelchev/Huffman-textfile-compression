#include "tree.h"

/**
 *@brief This constructor uses a binary file containing an already built Table
         First the Table from the file is being read into a table, and then a
         Tree is being built from the table, and that tree is assigned to the *this.
         The resulting Tree is only good for Decompressing!
 *@see Tree::Tree(const Table& given)
 *@see Operator=(const Tree& given)
 *@param filename - the name of the file from which a Table object is read.
 *@date 20 01 2016
*/
Tree::Tree(const char* filename):Table::Table(),root(NULL),compressed_message(NULL),compressed_decimal_message(NULL){
    Table temporary;
    temporary.read_table(filename);
    *this = (Tree(temporary));
}
