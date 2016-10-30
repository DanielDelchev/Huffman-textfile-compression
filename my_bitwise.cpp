#include "my_bitwise.h"
#include <iostream>
PackedByte::PackedByte(){};

/**
 *@brief Constructor of the class using an unsigned integer (0-255)
         The integer is transformed into binary (using std::bitset<8> )and the bits from that
         binary representation of the number are being assigned to the
         bits of the byte.
 *@param given - the integer from which the PackedByte object will be constructed
 *@date 20 01 2016
 */
PackedByte::PackedByte(short unsigned int given){//receive an int
    bitset<BITS_IN_BYTE> temp ( (unsigned long long) given);//turn it into a bitset ,constructor requires unsgined long long
    for (int i=BITS_IN_BYTE-1;i>=0;i--){
        bitset<BITS_IN_BYTE>::reference p=temp[i];//utmost right to left! <-
        unsigned int current=i;
        (p!=0) ? (set_bit(BITS_IN_BYTE-1-current)):(reset_bit(BITS_IN_BYTE-1-current));//utmost left to right ->  //assign the bitset to the byte
    }
}

//128(decimal)=10000000 (binary)

/**
 *@brief Setter for the n-th bit of the byte to become 0 (false);
 *@date 20 01 2016
 *@param given - the position at which 0 (false) is to be assigned to the bit
 */
void PackedByte::reset_bit(unsigned int given){//0 is the utmost left , 7 the utmost right
//shifting the 1 of the 10000000  (128) enough times so that it is in the same position as the bit of the PackedByte we want to assign 1 to
//then we perfom a logical denial to reverse the bits so that at the position we want to assign 0 to we have 0 and all other positions are 1
//then we perform a logical and over the mask and the byte.This way all the bits in positions other than the one we want to assign 0 to
//stay the same. The position we want to assign 0 to is sure to become 0 because both 0%1=0 and 0%0=0
    int mask = ~(128>>given);
    byte = byte&mask;
}
/**
 *@brief Setter for the n-th bit of the byte to become 1 (true);
 *@date 20 01 2016
 *@param given - the position at which 1(true) is to be assigned to the bit
 */
void PackedByte::set_bit(unsigned int given){//0 is the utmost left , 7 the utmost right
//shifting the 1 of the 10000000  (128) enough times so that it is in the same position as the bit of the PackedByte we want to assign 1 to
//then we perform a logical or over the mask and the byte so that every position other than the one we want to assign 1 to will stay the same bit as before
//and the position to which we want to assign 1 will become 1 because the mask has 1 at that position
    int mask = (128>>given);
    byte = byte|mask;
}

/**
 *@brief Getter for the n-th bit of the PackedByte object.
 *@param given - the poition of the bit that we want to get (0 is the utmost left , 7 the utmost right)
 *@date 20 01 2016
 */
bool PackedByte::get_bit(unsigned int given)const{//0 is the utmost left , 7 the utmost right
//shifting the 1 of the 10000000  (128) enough times so that it is in the same position as the bit of the PackedByte we want to get
//then we perform a logical and over the two if at the given position in the byte there is a "1" 1 will be result of the operation,otherwise 0 since
//all other positions will be 0
    return ((bool) (byte & (128>>given)));
}

/**
 *@brief operator<< for the class (prints out all the bits of the byte in the console)
 *@date 20 01 2016
 *@see PackedByte::get_bit(unsigned int given)const
 */
ostream& operator<<(ostream& os,const PackedByte& given){
    for (unsigned int i=0;i<BITS_IN_BYTE;i++){
        os<<(given.get_bit(i));
    }
    os<<endl;
    return os;
}
