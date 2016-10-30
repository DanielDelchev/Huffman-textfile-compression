#include "Stack.h"

/**
 *@brief deffault constructor of an empty Stack
 *@date 20 01 2016
 */
Stack::Stack():top_of_stack(NULL){
}

/**
 *@brief constructor of a Stack with only one Box on its top with Vertex "given"
 *@date 20 01 2016
 *@see Box
 *@param given - the Vertex to be included in the single Box in the Stack
 */
Stack::Stack(const Vertex& given):top_of_stack(NULL){
    top_of_stack=new Box;
    top_of_stack->vertex_within=given;
    top_of_stack->previous_box=NULL;
}
/**
 *@brief private destroy function used in the destructor of the Stack class
 *@date 20 01 2016
 *@see ~Stack()
 */
void Stack::destroy(){
    Box* pointer=top_of_stack;
    while(top_of_stack!=NULL){
        top_of_stack=top_of_stack->previous_box;
        delete pointer;
        pointer=top_of_stack;
    }
}
/**
 *@brief virtual destructor for the Stack
 *@date 20 01 2016
 *@see destroy()
 */
Stack::~Stack(){
    destroy();
}


/**
 *@brief copy constructor for the Stack
 *@date 20 01 2016
 *@param given - the Stack we are copying
 *@see copy(const Stack& given)
 */
Stack::Stack(const Stack& given):top_of_stack(NULL){
    copy(given);
}

/**
 *@brief operator= for the Stack
 *@date 20 01 2016
 *@param given - the rvalue of the assignment
 *@see copy(const Stack& given)
 *@see destroy()
 */
Stack& Stack::operator=(const Stack& given){
    if (this!=&given){
        destroy();
        copy(given);
    }
    return *this;
}

/**
 *@brief cheks if the Stack is empty(if top==NULL)
 *@date 20 01 2016
 */
bool Stack::empty()const{
    return top_of_stack==NULL;
}

/**
 *@brief copy function used in copy constructor and in operator=
 *@date 20 01 2016
 *@param given - the Stack we are copying
 *@see operator=(const Stack& given)
 *@see Stack(const Stack& given)
 */
void Stack::copy(const Stack& given){
    if (given.empty()){//if there is nothing to copy we just return an empty stack
        top_of_stack=NULL;
    }
    else{
        Box* pointer=given.top_of_stack; //we assign a pointer to the top box of the stack we currently want to copy
        Box* last_copied_box=NULL; //this points to the last copied box
        Box* box_to_add=NULL;  //we build elements here at this adress
        top_of_stack=new Box;//we generate a new box to be the top of the stack we are creating
        top_of_stack->vertex_within=pointer->vertex_within;//copies the vertex
        top_of_stack->previous_box=last_copied_box;//currently NULL
        last_copied_box=top_of_stack;//assignes the last used box
        pointer=pointer->previous_box;//gets us the new box we have to copy

//we first add a copy of the top, then we add a copy of the box underneath the top and assign it to point to top and so on until there are no more boxes to copy
        while(pointer!=NULL){
            box_to_add=new Box;//we generate a new box
            box_to_add->vertex_within=pointer->vertex_within;//we assign it value for the vertex
            last_copied_box->previous_box=box_to_add;//we assign the box we had built before this iteration to point in the box we are now building
            last_copied_box=box_to_add;// the last copied box is now the one we have just added
            pointer=pointer->previous_box;//we get to the new box we have to copy
        }
        last_copied_box->previous_box=NULL; //after the cycle ends we have copied the bottom box of the stack
                                            //there are no boxes under the bottom box, so we assign its pointer to point to NULL
    }
}

/**
 *@brief gives us the Vertex contained in the Box at the top of the stack
 *@date 20 01 2016
 *@see Box
 *@see Vertex
 *@return the Vertex contained in the Box at the top of the Stack
 */
Vertex Stack::top()const{
    return top_of_stack->vertex_within;
}

/**
 *@brief gives us the Vertex contained in the Box at the top of the stack and removes that Box
 *@date 20 01 2016
 *@see Box
 *@see Vertex
 *@return the Vertex contained in the Box we 've just gotten rid of
 */
Vertex Stack::pop(){
    if (empty()==true){
        cout<<"Stack is empty!Cannot pop!"<<endl;
        return Vertex();
    }
    Vertex copy_of_top=top();
    Box* pointer_to_top_box=top_of_stack;
    top_of_stack=top_of_stack->previous_box;
    delete pointer_to_top_box;
    return copy_of_top;
}

/**
 *@brief puts a Box containing the Vertex given as parameter at the top of the Stack
 *@date 20 01 2016
 *@param
 *@see Box
 *@see Vertex
 *@return void
 */
void Stack::push(const Vertex& given){
    Box* future_top=new Box;
    future_top->vertex_within=given;
    future_top->previous_box=top_of_stack;
    top_of_stack=future_top;
}

/**
 *@brief pints a copy of the Stack in the console and destroys that copy
 *@date 20 01 2016
 *@return void
 */
void Stack::print_stack()const{
    Stack copy_of_stack=*this;
    if (copy_of_stack.empty()==true){
        cout<<"Stack is empty"<<endl;
        return;
    }
    while(!copy_of_stack.empty()){
        cout<<copy_of_stack.pop();
    }
    cout<<endl;
}
