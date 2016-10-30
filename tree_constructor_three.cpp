#include "NodeTree.h"

/**
  *@brief This is the constructor used in the current version of the project and is the fragment of the program
          where the compression of the input message and writing down of the compressed message and Huffmann tree.
          It comrpesses the message into a bool message and turns that bool message into a compressed message of
          integers the same way other constructors for the class do.This constructor reads the input string from a
          textfile processes it and wites down the bool form of the compressed message into a binary file. It also
          writes down aserializable and desirializable form of the Huffmann tree into a binary file for later use.
          First the input string is read from the textfile in a buffer of 8KB so as to account for intervals and
          newlines and a result string is being built from the buffer at each iteration of the reading.After the string
          has been read , the Table of frequency is built.Then from the leaves in the Table, the Huffmann tree gets built.
          After that the codes to the leaves get assigned.Then the compressed bool message gets build,and from it the
          compressed int message is built.From the compressed integer (decimal) message PackedBytes are formed and written
          in a binaryfile.At the final stage from the Tree a NodeTree is formed (a serializable and deserializable form of the Tree)
          and written down in a binary file.
  *@param from - the name of text file from which the input string will be read.
  *@param code_to - name of the binary file in which the bool compressed form of the message will be written down in
  *@param tree_to - name of the binary file in which a NodeTree (a serializable form of the Huffmann  tree) will be written down in
  *@param bool_code_to - name of the file where the bool compressed form of the string will be put (if null then it will not be written down)
  *@param int_code_to - name of the file where the integer compressed form of the string will be put (if null then it will not be written down)
  *@see Node
  *@see NodeTree
  *@see PackedByte
  *@date 20  01 2016
*/

Tree::Tree(const char* from,const char* code_to,const char* tree_to,const char* bool_code_to,const char* int_code_to):
    Table::Table(),root(NULL),compressed_message(NULL),compressed_decimal_message(NULL){
    const int MAX=8192; //(8KB buffer)
    fstream input(from,ios::in);
    string result;
    input.seekg(0,ios::end);
    unsigned long long int msg_length=input.tellg();
    result.reserve(msg_length);//allocating in advance
    input.seekg(0,ios::beg);//returning to start of file
    char delim = (char)(10); //"\n"
    char temp[MAX];
    while(input.good()){
        input.getline(temp,MAX,delim);                //assuming no line is more than MAX characters
        result+=temp;
        if (input.good()){                            //if not the last line, add newline
            result+="\n";
        }
    }
    input.close();
    Table::operator=(Table(result));//build the Table from the already read string
    unsigned long long int lg=0;
    for (int i=0;i<get_count();i++){//see how many times each letter is repeated in the input message, the sum of that is the length of the input message
        lg+=(get_start()+i)->get_repetitions();
    }
    message_length=lg;
    compressed_message_length=0;
    compressed_decimal_message_length=0;
    if((message_length==0)||((get_start()->get_letter())=='\0')){ //if the input strign is empty
        root=NULL;
        return;
    }

    //with the help of this array the tree will be built, after that the array will be deleted
    int counter=get_count();
    Vertex* all_vertices_temporary=new Vertex [3*counter]; //all vertices <= 2* leaves
    for(int i=0;i<counter;i++){
        all_vertices_temporary[i]=*(get_start()+i);
    }
    sort_ascending_outclass(all_vertices_temporary,counter);//not necessarily to sort
    int marked_vertices=0;//this counter counts how many vertices from the array have been marked as used

    int key_counter=Table::get_count();
    while(!(counter==marked_vertices+1)){//when counter==used_vertices+1 the only vertex with no parent is the root itself
        Vertex to_be_added; //we generate a generic vertex
        to_be_added.set_Node_ID((++key_counter));
        to_be_added.set_left_successor(NULL);
        to_be_added.set_right_successor(NULL);
        to_be_added.set_repetitions(0);
        to_be_added.set_letter('Ù');
        to_be_added.set_code(NULL,0);
        to_be_added.set_code_length(0);
        to_be_added.set_marked(false);
        to_be_added.set_right_successor(find_unmarked_min_outclass(all_vertices_temporary,counter));//we assign its right successor to be the minimum vertex that has not been used yet
        to_be_added.get_right_successor()->set_special_ID('R');// stands for Right successor
        int right_repetitions=(find_unmarked_min_outclass(all_vertices_temporary,counter))->get_repetitions();//memorizing right repetitions
        (find_unmarked_min_outclass(all_vertices_temporary,counter))->set_marked(true);//we mark the just used vertex as used
        to_be_added.set_marked(true);//we mark the generic vertex as used so as not to include it in the search for the next minimum unused vertex
        to_be_added.set_left_successor(find_unmarked_min_outclass(all_vertices_temporary,counter));//we assign a left successor
        to_be_added.get_left_successor()->set_special_ID('L');//L stands for Left successor
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
    //after this the three Vertecies and the Vertecies in the Table are at different adresses!!
    if(get_count()==1){//the case when the root is the only leaf
        get_start()->add_bit_to_code(false);
    }
    else//when the root is not the only vertex of the tree
    {

        for (int i=0;i<get_count();i++){
            Stack reversed_path(*root);//create a Stack with only 1 element - the root of the tree
            reversed_path=find_reversed_path_to_leaf(reversed_path,*(get_start()+i));//this stack contains the vertices of the path from the root to the leaf we want //the root is in the bottom of the stack, the leaf on top of the stack
            Stack proper_path;
            while (reversed_path.empty()==false){//now proper path contains the proper path , root at the top leaf at the bottom
                proper_path.push(reversed_path.pop());
            }
            //finding whether the Vetex at the top is left or right successor to its parent so we know wether to add 1 or 0 for the code at this step
            Vertex step_one=proper_path.pop();//successor
            while (proper_path.empty()==false){//this builds the code into the leaf in the table
                Vertex step_two=proper_path.pop();//parent
                if (step_one.get_left_successor()->special_comparison(step_two)==true){//if step_two is left successor to step_one add 0 in code
                    (get_start()+i)->add_bit_to_code(false);
                }
                else {//otherwise if step_two is right_sucessor to step_one add 1 in code
                        (get_start()+i)->add_bit_to_code(true);
                }
                step_one=step_two; //prepare for next iteration

            }
                refresh_tree(root);//this restores the markers to false for the next iteration
                //when finding paths to leaves marking of vertices is used, here we refresh all vertices in tree
                //for the next iteration
        }
    }
//at this point the Tree has been built and the codes to all letters of the message is assigned to the coresponding Vertices with those letter in the Table
    for (int i=0;i<get_count();i++){//calculating the lenght of the bool compressed message to be generated (sum of repetitions*code_length for all vertices)
        compressed_message_length+=((get_start()+i)->get_code_length())*((get_start()+i)->get_repetitions());
    }
    compressed_message=new bool [compressed_message_length];// allocates enough memory in advance
    Vertex temporary_vertex;
    unsigned long long int bytes_already_assigned=0;//remembers how many bools have been copied correctly already
    for (unsigned long long int i=0;i<message_length;i++){
        char finder=result[i];//for each letter of the input string
        temporary_vertex=*(find_vertex(finder));//finds the vertex with the corresponding letter
        int code_to_add_length=temporary_vertex.get_code_length();//we need to assign that many bools of the code on this iteration
        for (int i=0;i<code_to_add_length;i++){
            *(get_compressed_message()+i+bytes_already_assigned)=*(temporary_vertex.get_code()+i);   //we do the assigning
        }
        bytes_already_assigned+=code_to_add_length;  //we increase the count of already signed bools for the next iteration
    }
//now that we have the table, the tree, and the codes of the letters in the table, and the compressed bool message, we build the
//compressed message from integers (0-255) we store it in a short unsigned int array

    unsigned long long int length_for_decimal=(compressed_message_length/8);//The compressed integer message is sure to have at least that many integers
    short unsigned int remnant=compressed_message_length%8; //for the last integer there might be less than 8 bools of code
    if (remnant!=0){
        length_for_decimal+=1;//+1 to lenght , if remnant is not zero
    }
    compressed_decimal_message=new short unsigned int[length_for_decimal+1];//one extra number at the end is for the remnant,which we need to store to be able to convert the int compressed message back into bools
        //in the extra number we store the lenght of the remnant (even if the length is zero)
    if (remnant!=0){
        for (unsigned long long int i=0;i<length_for_decimal-1;i++){
            //using convert_to_bools function with first parameter position in bool array, second the count of bools to be used in the conversion from bools to int
            *(compressed_decimal_message+i)=convert_bools_to_int((compressed_message+(i*BITS_IN_BYTE)),BITS_IN_BYTE);
            compressed_decimal_message_length+=1;
        }
        //lastly do one more iteration only not for 8 bools but for remnant bools
        *(compressed_decimal_message+compressed_decimal_message_length)=convert_bools_to_int((compressed_message+(compressed_decimal_message_length*BITS_IN_BYTE)),remnant);
        compressed_decimal_message_length+=1;
        //at the end also write down the remnant so we could restore the bool message from the int message correctly
        *(compressed_decimal_message+compressed_decimal_message_length)=remnant;
        compressed_decimal_message_length+=1;
    }

    else{//if remnant is 0
        for (unsigned long long int i=0;i<length_for_decimal;i++){
            *(compressed_decimal_message+i)=convert_bools_to_int((compressed_message+(i*BITS_IN_BYTE)),BITS_IN_BYTE);
            compressed_decimal_message_length+=1;
        }
        *(compressed_decimal_message+compressed_decimal_message_length)=0;// remnant is 0 in this case
        compressed_decimal_message_length+=1;
    }
    input.close();//closing file (if it hasn t been close already)

    if (bool_code_to!=NULL){//if specified to in parameters, the bool compressed message is written down in a textfile with the specified name
        fstream fs1(bool_code_to,ios::out|ios::trunc);
        int counter_newline=0;
        for (unsigned long long int i=0;i<compressed_message_length;i++){
            fs1<<*(compressed_message+i);
            ++counter_newline;
            if (i!=0 && (i+1)%BITS_IN_BYTE==0){
                fs1<<" ";
            }
            const int line_length=88;
            if(counter_newline!=0 && i!=0 && (counter_newline)%line_length==0){//so as not to print too long lines
                fs1<<"\n";
            }
        }
        fs1.close();
    }


    if (int_code_to!=NULL){//also if specified to do so in parameters, the int compressed message is writted down in a textfile with the specified name
        fstream fs2(int_code_to,ios::out|ios::trunc);
        for (unsigned long long int i=0;i<compressed_decimal_message_length;i++){
            fs2<<*(compressed_decimal_message+i)<<" ";
            const int line_length2=50;
            if(i!=0 && i%line_length2==0){
                fs2<<"\n";
            }
        }
        fs2.close();
    }


    //PackedByte is a byte in which we write 8 bools and writes down that one byte instead of those 8 bools in 8 sepeate bytes so as to safe space
    //see PackedByte class for more info
    fstream fs3(code_to,ios::binary|ios::trunc|ios::out);//writes down the PackedBytes in a binaryfile
    int leftover = compressed_message_length%BITS_IN_BYTE;//the amount of bites left for the last byte
    unsigned long long int PackedBytesCount = (compressed_message_length/BITS_IN_BYTE);//the count of PackedBytes that is sure to be
    if (leftover!=0){//add one more PackedByte if there are leftovers (less than 8 bits at the end for the last PackedByte)
        PackedBytesCount+=1;
    }

    fs3.write((const char*)& message_length,sizeof(unsigned long long int));//write down length of the input string message(starting message)
    fs3.write((const char*)& PackedBytesCount,sizeof(unsigned long long int));//write down count of Packed Bytes
    fs3.write((const char*)& leftover,sizeof(int));//write down leftover (shows how many bits of the LAST byte should be restored when deserializing (counting right to left))

    for (unsigned long long int i=0;i<PackedBytesCount;i++){
        PackedByte to_write(*(compressed_decimal_message+i)); //constructs a PackedByte from an integer of the compressed decimal message (see constructor for PackedByte)
        fs3.write((const char*)& to_write,sizeof(PackedByte));//writes down that PackedByte into the binary file
    }
    fs3.close();

    NodeTree writable_tree(*this);//creates a serializable and deserializable NodeTree
    writable_tree.write_node_tree(tree_to);//writes down the NodeTree in a binary file

}
