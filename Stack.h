#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED
#include "Vertex.h"

/**
 *@brief Elements held in the Stack class.Holds a Vertex and a pointer to the previous Box.
 *@see Stack
 *@see Vertex
 *@date 20 01 2016
 */
struct Box{
    Vertex vertex_within;
    Box* previous_box;
};


/** @brief Stack data structure, with standart implementation used to store Box objects
  * @date 20 01 2016
  * @see Box
  * @see Vertex
  */
class Stack{
public:
    Stack();
    Stack(const Vertex& given);
    Stack(const Stack& given);
    Stack& operator=(const Stack& given);
    virtual ~Stack();

    void push(Vertex const& given);
    Vertex pop();
    Vertex top()const;
    bool empty()const;
    void print_stack()const;
private:
    void copy(const Stack& given);  /**< copy function used in the copy constructor of the class */
    void destroy();      /**< destroy function used in the destructor of the class*/
    Box* top_of_stack;  /**< pointer to the Box at the top of the Stack */
};


#endif // STACK_H_INCLUDED
