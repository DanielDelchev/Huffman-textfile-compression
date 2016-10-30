#include "NodeTree.h"


/**
 *@brief This project is an implementation of the Huffmann algorythm for compression without loss of data.
         This version of the project allows compression of strings read from a text file.The compressed code
         is stoerd in a binary file, and the Tree needed for the decompression is stored in another binary file.
         The compression achieved is of nearly 56% . The Table class in the project represents the Frequency table
         The Tree class represents the Huffmann Tree needed for the compression. The NodeTree is another form of the
         Huffmann tree which allows serialization and desirialization.
         For more specification on the classes and functions used see the provided HTML doccumentation extracted with doxygen.
         To compress some string create a "InputMessage.txt" file in the project directory ,
         paste the string in the file and run the program.
 *@date 20 01 2016
*/


void ShortExample(){
    const char InputMessage[]="InputMessage.txt";
    const char TreeData[]="TreeData.dat";
    const char CodeData[]="CodeData.dat";
    const char Decompressed[]="Decompressed.txt";
    const char Bools_to[]="BoolCode.txt";
    const char Ints_to[]="IntCode.txt";
    cout<<"compressing!"<<endl;
    Tree compress_tree(InputMessage,CodeData,TreeData,Bools_to,Ints_to);
    cout<<"Compression benefit: "<<compress_tree.calculate_compression_benefit_bools()<<endl;
    cout<<"done compressing!"<<endl;
    cout<<"frequency table:"<<endl;
    compress_tree.print_table();
    cout<<"tree relations:"<<endl;
    compress_tree.print_tree(compress_tree.get_root());
    cout<<"decompressing!"<<endl;

//this function is used here so that the NodeTree can be printet for the example, there is a short function for the following lines otherwise
    fstream fs(CodeData,ios::binary|ios::in);
    unsigned long long int decompressed_message_length=0;
    unsigned long long int PackedBytesCount=0;
    int leftovers = 0;

    fs.read( (char*)& decompressed_message_length,sizeof(unsigned long long int));
    fs.read( (char*)& PackedBytesCount,sizeof(unsigned long long int));
    fs.read( (char*)& leftovers,sizeof(int));

    unsigned long long int bool_compressed_length=BITS_IN_BYTE*PackedBytesCount;
    if (leftovers!=0){
        bool_compressed_length-=BITS_IN_BYTE;
        bool_compressed_length+=leftovers;
    }

    bool* bool_compressed = new bool [bool_compressed_length];

    PackedByte* packed=new PackedByte[PackedBytesCount];
    for (unsigned long long int i=0;i<PackedBytesCount;i++){
        fs.read( (char*)& packed[i],sizeof(PackedByte));
    }
    fs.close();


    if(leftovers == 0){
        for (unsigned long long int i=0;i<PackedBytesCount;i++){
            for (int j=0;j<BITS_IN_BYTE;j++){
                *(bool_compressed + (i*BITS_IN_BYTE) +j)= packed[i].get_bit(j);
            }
        }
    }

    else if (leftovers!=0){
        for (unsigned long long int i=0;i<PackedBytesCount-1;i++){
            for (int j=0;j<BITS_IN_BYTE;j++){
                *(bool_compressed + (i*BITS_IN_BYTE) +j)= packed[i].get_bit(j);
            }
        }

        for (int f=0;f<leftovers;f++){
            *(bool_compressed + (PackedBytesCount-1)*BITS_IN_BYTE +f) = packed[PackedBytesCount-1].get_bit(BITS_IN_BYTE-leftovers+f);
        }
    }


    NodeTree decompressing_tree(TreeData);

    const bool* pointer=bool_compressed;
    char receiver;
    fstream fs2(Decompressed,ios::trunc|ios::out);
    for (unsigned long long int i=0;i<decompressed_message_length;i++){
        receiver=decompressing_tree.decompress_letter(pointer);
        fs2<<receiver;
    }
    fs2.close();
    cout<<"done decompressing!"<<endl;
    cout<<"serializable/desirializable NodeTree (for decompression):"<<endl;
    cout<<decompressing_tree;
}

void NormalExample(){
    const char InputMessage[]="InputMessage.txt";
    const char TreeData[]="TreeData.dat";
    const char CodeData[]="CodeData.dat";
    const char Decompressed[]="Decompressed.txt";
    const char Bools_to[]="BoolCode.txt";
    const char Ints_to[]="IntCode.txt";
    cout<<"compressing!"<<endl;
    Compress(InputMessage,CodeData,TreeData,Bools_to,Ints_to);//last two can be omitted, then int and bool codes will not be written in textfiles
    cout<<"done compressing!"<<endl;
    cout<<"decompressing!"<<endl;
    Decompress(TreeData,CodeData,Decompressed);
    cout<<"done decompressing!"<<endl;
}

//Open Task Manager run this test and check if memory used is constant
void MemoryTest(){
    //when compressing and decompressing
    //Tree and NodeTree are the structures that are created
    //all other classes//structures are created/used/inherited by Tree and NodeTree
    const char InputMessage[]="InputMessage.txt";
    const char TreeData[]="TreeData.dat";
    const char CodeData[]="CodeData.dat";
    const char Decompressed[]="Decompressed.txt";
    const char Bools_to[]="BoolCode.txt";
    const char Ints_to[]="IntCode.txt";
    while (true){
    cout<<"Memory leak test running!"<<endl;
    Tree compress_tree(InputMessage,CodeData,TreeData,Bools_to,Ints_to);
    NodeTree decompressing_tree(TreeData);
    }
}

int main()
{
    system("color 02");

    //ShortExample();
    //NormalExample();
    //MemoryTest();
    return 0;
}
