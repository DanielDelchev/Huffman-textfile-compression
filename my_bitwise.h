#ifndef MY_BITWISE_H_INCLUDED
#define MY_BITWISE_H_INCLUDED
#include <bitset>
const int BITS_IN_BYTE=8;
using namespace std;

/**
 *@brief Since we cannot direclty access bits.We cannot write down Bools in a single bit,instead the Bool is being written
         in a Byte, and the Byte is being written down.To avoid this, and write down Bools in such a way that each bool
         would only take up 1 bit of memory-space instead of a whole byte,a special structure is needed.
         Objects of the PackedByte class are merely unsigned chars(1 byte=8bits).For the class we have operation
         which can access the nth bit, change the n-th bit to 1 , or change the n-th bit to 0.That way we can store
         8 bools in a single Byte, write it down ,and later when we read it we can access each of those bools in the form
         of bits of the Byte.There is a constructor for the class which receives an integer 0-255 and transforms it into a
         byte (unsgined char) by representing that integer as a number in base 2.
 *@date 20 01 2016
 */
class PackedByte{
public:
    PackedByte();
    PackedByte(short unsigned int int_code_memeber);

    void set_bit(unsigned int pos);
    void reset_bit(unsigned int pos);
    bool get_bit(unsigned int pos)const;

    friend ostream& operator<<(ostream& os,const PackedByte& given);

private:
    unsigned char byte;/**< An unsigned char representing the Byte in which we store bools in the form of bits of the byte */
};

#endif // MY_BITWISE_H_INCLUDED
