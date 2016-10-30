#include "Tree.h"
//For console only, now work with files

//This constructor is not used in the current version of the project
/**
 *@brief This constructor is used when working with the console.It is not appropriate when working
         with long strings.All four non-deffault constructors work in a similliar way.The only differences
         between them being - how they get their string input, and wheter they use files.Look at three_constructor_three(...)
         it is the one used in the project and builds the compressed message in the same way it is build here.
 *@see three_constructor_three(...)
 *@param - given - a char string representing the input message to be compressed
 *@date 20 01 2016
*/
Tree::Tree(char* given):Table(given),root(NULL),compressed_message(NULL),compressed_decimal_message(NULL){
    message_length=strlen(given);
    compressed_message_length=0;
    compressed_decimal_message_length=0;
    if((given==NULL)||((*given)=='\0')){
        root=NULL;
        return;
    }

    //genereating array of leaves
    int counter=get_count();
    Vertex* all_vertices_temporary=new Vertex [3*counter]; //all vertices <= 2* leaves
    for(int i=0;i<counter;i++){
        all_vertices_temporary[i]=*(get_start()+i);
    }
    sort_ascending_outclass(all_vertices_temporary,counter);
    int marked_vertices=0;

    int key_counter=Table::get_count();
    while(!(counter==marked_vertices+1)){//when counter==used_vertices+1 the only vertex with no parent is the root itself
        Vertex to_be_added; //we generate a generic vertex//MUST SET ID HERE TOO
        to_be_added.set_Node_ID((++key_counter));
        to_be_added.set_left_successor(NULL);
        to_be_added.set_right_successor(NULL);
        to_be_added.set_repetitions(0);
        to_be_added.set_letter('Ù');
        to_be_added.set_code(NULL,0);
        to_be_added.set_code_length(0);
        to_be_added.set_marked(false);
        to_be_added.set_right_successor(find_unmarked_min_outclass(all_vertices_temporary,counter));//we assign its right successor to be the minimum vertex that has not been used yet
        to_be_added.get_right_successor()->set_special_ID('R');
        int right_repetitions=(find_unmarked_min_outclass(all_vertices_temporary,counter))->get_repetitions();//memorizing right repetitions
        (find_unmarked_min_outclass(all_vertices_temporary,counter))->set_marked(true);//we mark the just used vertex as used
        to_be_added.set_marked(true);//we mark the generic vertex as used so as not to include it in the search for the next minimum unused vertex
        to_be_added.set_left_successor(find_unmarked_min_outclass(all_vertices_temporary,counter));//we assign a left successor
        to_be_added.get_left_successor()->set_special_ID('L');
        int left_repetitions=(find_unmarked_min_outclass(all_vertices_temporary,counter))->get_repetitions();//memorizing left repetitions
        (find_unmarked_min_outclass(all_vertices_temporary,counter))->set_marked(true);//we mark the just found vertex as used
        to_be_added.set_marked(false);//the generic vertex has finally been built and we can mark it as unused and can use it in the next cycle
        int sum=left_repetitions+right_repetitions;//generating repetitions for the new vertex
        to_be_added.set_repetitions(sum);
        if((counter+1)==(marked_vertices+2)+1){//if it is the last iteration this is the root, give it NODE_ID 0
            to_be_added.set_Node_ID(0);
        }
        all_vertices_temporary[counter]=to_be_added;
        counter+=1;
        marked_vertices+=2;//we ve just added 2 vertices, when (all vertices=used vertices+1) we stop the cycle
    }

    //after we 've finished finding all the vertecies for the tree,we unmark all of them
    //for future needs;
    for (int i=0;i<counter;i++){
        (all_vertices_temporary+i)->set_marked(false);
    }
    //we copy the tree we ve just built in the array in the root
    root=copy_tree((find_max_outclass(all_vertices_temporary,counter)));
    //now we delete the array because we have the tree
    delete [] all_vertices_temporary;
    //gotta copy this later to the table constructor
    if(get_count()==1){//the case when the root is the only leaf
        get_start()->add_bit_to_code(false);
    }
    else//when the root is not the only vertex of the tree
    {

        for (int i=0;i<get_count();i++){
            Stack reversed_path(*root);
            reversed_path=find_reversed_path_to_leaf(reversed_path,*(get_start()+i));//this stack contains the vertices of the path from the root to the leaf we want //the root is in the bottom of the stack, the leaf on top of the stack
            Stack proper_path;
            while (reversed_path.empty()==false){//now proper path contains the proper path , root at the top leaf at the bottom
                proper_path.push(reversed_path.pop());
            }

            Vertex step_one=proper_path.pop();
            while (proper_path.empty()==false){//this builds the code into the leaf in the table
                Vertex step_two=proper_path.pop();
                if (step_one.get_left_successor()->special_comparison(step_two)==true){//special comparrisson also takes into account of the Vertices are both left/right sucessors to their parents or not
                    (get_start()+i)->add_bit_to_code(false);
                }
                else {
                        (get_start()+i)->add_bit_to_code(true);
                }
                step_one=step_two;

            }
                refresh_tree(root);//this restores the markers to false for the next iteration
        }
    }
    for (int i=0;i<get_count();i++){
        compressed_message_length+=((get_start()+i)->get_code_length())*((get_start()+i)->get_repetitions());
    }
    compressed_message=new bool [compressed_message_length];// allocates enough memory in advance
    Vertex temporary_vertex;
    int bytes_already_assigned=0;//remembers how many bools have been copied correctly already
    for (unsigned long long int i=0;i<message_length;i++){
        temporary_vertex=*(find_vertex(*(given+i)));//finds the vertex with the corresponding letter
        int code_to_add_length=temporary_vertex.get_code_length();//we need to assign that many bools of the code on this iteration
        for (int i=0;i<code_to_add_length;i++){
            *(get_compressed_message()+i+bytes_already_assigned)=*(temporary_vertex.get_code()+i);   //we do the assigning
        }
        bytes_already_assigned+=code_to_add_length;          //we increase the count of already signed bools for the next iteration
    }

//now that we have the table, the tree, and the codes of the letters in the table, and the compressed bool message, we build the
//compressed message from integers (0-255) we store it in a short unsigned int array

    unsigned long long int length_for_decimal=(compressed_message_length/BITS_IN_BYTE);//count of integers in the code
    short unsigned int remnant=compressed_message_length%BITS_IN_BYTE;
    if (remnant!=0){
        length_for_decimal+=1;//adding one bit if there are less than 8 bools at the end of the bool message
    }
    compressed_decimal_message=new short unsigned int[length_for_decimal+1];//one extra number at the end is for the remnant,which we need to convert back to bools
        //the remnant shows how many bools are at the end of the message (compressed_message_length % 8);
    if (remnant!=0){
        for (unsigned long long int i=0;i<length_for_decimal-1;i++){
            *(compressed_decimal_message+i)=convert_bools_to_int((compressed_message+(i*BITS_IN_BYTE)),BITS_IN_BYTE);
            compressed_decimal_message_length+=1;
        }
        *(compressed_decimal_message+compressed_decimal_message_length)=convert_bools_to_int((compressed_message+(compressed_decimal_message_length*BITS_IN_BYTE)),remnant);
        compressed_decimal_message_length+=1;//last integer could be generated from less than 8 bools
        *(compressed_decimal_message+compressed_decimal_message_length)=remnant;//writing down how many bools were used to generate the last int at the enf after the code
        compressed_decimal_message_length+=1;
    }

    else{//if last integer was also generated from 8 bools , still write remnant 0 at the end
        for (unsigned long long int i=0;i<length_for_decimal;i++){
            *(compressed_decimal_message+i)=convert_bools_to_int((compressed_message+(i*BITS_IN_BYTE)),BITS_IN_BYTE);
            compressed_decimal_message_length+=1;
        }
        *(compressed_decimal_message+compressed_decimal_message_length)=0;// remnant is 0
        compressed_decimal_message_length+=1;
    }
}
