/******************************************************************************************
*Title: Data structure
*Author: Moshé
*Reviewer: 
*Description:
*Status: in developpment
*****************************************************************************************/
#include <stdio.h> /* printf */
#include <assert.h> /* assert */
#include <limits.h> /* CHAR_BIT */
#include "bitsarr.h"

#define NO_OF_BITS (CHAR_BIT * sizeof(bitsarr_t))
#define MASK1 1lu
#define B2(n) n, n + 1, n + 1, n + 2
#define B4(n) B2(n), B2(n + 1), B2(n + 1), B2(n + 2)
#define B6(n) B4(n), B4(n + 1), B4(n + 1), B4(n + 2)
#define COUNT_BITS B6(0), B6(1), B6(1), B6(2)
#define UNUSED __attribute__((unused))

bitsarr_t BitsArrSetAll(UNUSED bitsarr_t bit_array)
{
	return 0xffffffffffffffff;
}

bitsarr_t BitsArrResetAll(UNUSED bitsarr_t bit_array)
{	 			
	return 0x0000000000000000;
}

bitsarr_t BitsArrSetOn(bitsarr_t bit_array, size_t index)
{
	assert(index < 64);

	return (bit_array | MASK1 << index);
}

bitsarr_t BitsArrSetOff(bitsarr_t bit_array, size_t index)
{
	assert(index < 64);

	bit_array &= ~(MASK1 << index);
	return bit_array;	
}

bitsarr_t BitsArrSetBit(bitsarr_t bit_array, size_t index, int boolean_value)
{
	assert(index < 64);

	if (boolean_value)
	{
		bit_array = (bit_array | MASK1 << index);	
		return bit_array;
	}
	else
	{
		bit_array &= ~(MASK1 << index);
		return bit_array;
	}	
}

int BitsArrGetVal(bitsarr_t bit_array, size_t index)
{
	assert(index < 64);	
	
	if (bit_array & (MASK1 << index))
	{
		return 1;
	}
	else
	{
		return 0; 
	}
	
}

size_t BitsArrCountBitsOn(bitsarr_t bit_array)
{
	size_t i = 0;
	size_t count = 0;
	
	assert(i < 64);
	
	for (i = 0; i < NO_OF_BITS; i++)
	{
		if (bit_array & (MASK1 << i))
		{
			++count;
		}
	}
	
	return count;
}

size_t BitsArrCountBitsOff(bitsarr_t bit_array)
{
	return (NO_OF_BITS - BitsArrCountBitsOn(bit_array));
}

char *BitsArrToString(bitsarr_t bit_array, char *dest)
{
    size_t i = 0;
    size_t j = NO_OF_BITS - 1;
    
   	assert(i < 64);
    
    for (; i < NO_OF_BITS; i++, j--)
    {
        dest[j] = BitsArrGetVal(bit_array, i) + '0';
    }
    
    return dest;
      
}

bitsarr_t BitsArrMirror(bitsarr_t bit_array)
{
    bitsarr_t reverse_num = 0; 
    size_t i = 0; 
        
    for (i = 0; i < NO_OF_BITS; i++) 
    { 
        if ((bit_array & (MASK1 << i))) 
        {
           reverse_num |= MASK1 << ((NO_OF_BITS - MASK1) - i);   
        }
   } 
   
    return reverse_num; 
}

bitsarr_t BitsArrFlip(bitsarr_t bit_array, size_t index)
{
	assert(index < 64);
	return bit_array ^ (MASK1 << index);
}

bitsarr_t BitsArrRotationLeft(bitsarr_t bit_array, size_t num_rotation)
{
	bitsarr_t tmp = 0;	
	
	num_rotation %= NO_OF_BITS; 
	tmp = bit_array >> (NO_OF_BITS - num_rotation); 
 
	return bit_array << num_rotation % NO_OF_BITS | tmp; 
}

bitsarr_t BitsArrRotationRight(bitsarr_t bit_array, size_t num_rotation)
{
	bitsarr_t tmp = 0;	
		
	num_rotation %= NO_OF_BITS; 
	tmp = bit_array << (NO_OF_BITS - num_rotation); 
 
	return bit_array >> num_rotation % NO_OF_BITS | tmp; 
}

bitsarr_t BitsArrMirrorLUT(bitsarr_t bit_array)
{
	size_t i = 0;
	
	bitsarr_t ret_bitarr = 0;
	
	unsigned char *holder = (unsigned char *)&bit_array;

	static const unsigned char mirror_byte_LUT[256] =
	{0x00, 0x80, 0x40, 0xc0, 0x20, 0xa0, 0x60, 0xe0,
	0x10, 0x90, 0x50, 0xd0, 0x30, 0xb0, 0x70, 0xf0,
	0x08, 0x88, 0x48, 0xc8, 0x28, 0xa8, 0x68, 0xe8,
	0x18, 0x98, 0x58, 0xd8, 0x38, 0xb8, 0x78, 0xf8,
	0x04, 0x84, 0x44, 0xc4, 0x24, 0xa4, 0x64, 0xe4,
	0x14, 0x94, 0x54, 0xd4, 0x34, 0xb4, 0x74, 0xf4,
	0x0c, 0x8c, 0x4c, 0xcc, 0x2c, 0xac, 0x6c, 0xec,
	0x1c, 0x9c, 0x5c, 0xdc, 0x3c, 0xbc, 0x7c, 0xfc,
	0x02, 0x82, 0x42, 0xc2, 0x22, 0xa2, 0x62, 0xe2,
	0x12, 0x92, 0x52, 0xd2, 0x32, 0xb2, 0x72, 0xf2,
	0x0a, 0x8a, 0x4a, 0xca, 0x2a, 0xaa, 0x6a, 0xea,
	0x1a, 0x9a, 0x5a, 0xda, 0x3a, 0xba, 0x7a, 0xfa,
	0x06, 0x86, 0x46, 0xc6, 0x26, 0xa6, 0x66, 0xe6,
	0x16, 0x96, 0x56, 0xd6, 0x36, 0xb6, 0x76, 0xf6,
	0x0e, 0x8e, 0x4e, 0xce, 0x2e, 0xae, 0x6e, 0xee,
	0x1e, 0x9e, 0x5e, 0xde, 0x3e, 0xbe, 0x7e, 0xfe,
	0x01, 0x81, 0x41, 0xc1, 0x21, 0xa1, 0x61, 0xe1,
	0x11, 0x91, 0x51, 0xd1, 0x31, 0xb1, 0x71, 0xf1,
	0x09, 0x89, 0x49, 0xc9, 0x29, 0xa9, 0x69, 0xe9,
	0x19, 0x99, 0x59, 0xd9, 0x39, 0xb9, 0x79, 0xf9,
	0x05, 0x85, 0x45, 0xc5, 0x25, 0xa5, 0x65, 0xe5,
	0x15, 0x95, 0x55, 0xd5, 0x35, 0xb5, 0x75, 0xf5,
	0x0d, 0x8d, 0x4d, 0xcd, 0x2d, 0xad, 0x6d, 0xed,
	0x1d, 0x9d, 0x5d, 0xdd, 0x3d, 0xbd, 0x7d, 0xfd,
	0x03, 0x83, 0x43, 0xc3, 0x23, 0xa3, 0x63, 0xe3,
	0x13, 0x93, 0x53, 0xd3, 0x33, 0xb3, 0x73, 0xf3,
	0x0b, 0x8b, 0x4b, 0xcb, 0x2b, 0xab, 0x6b, 0xeb,
	0x1b, 0x9b, 0x5b, 0xdb, 0x3b, 0xbb, 0x7b, 0xfb,
	0x07, 0x87, 0x47, 0xc7, 0x27, 0xa7, 0x67, 0xe7,
	0x17, 0x97, 0x57, 0xd7, 0x37, 0xb7, 0x77, 0xf7,
	0x0f, 0x8f, 0x4f, 0xcf, 0x2f, 0xaf, 0x6f, 0xef,
	0x1f, 0x9f, 0x5f, 0xdf, 0x3f, 0xbf, 0x7f, 0xff
	};

	for (i = 0; i < MASK1; ++i)
	{
		ret_bitarr <<= MASK1;
		ret_bitarr |= mirror_byte_LUT[holder[i]];
	}
	return ret_bitarr;

	return 0;

}	

bitsarr_t BitsArrSetOnLUT(bitsarr_t bit_array, size_t index)
{
	size_t i = 0, count = 0;
	unsigned char *holder = (unsigned char*)&bit_array;
	static const size_t count_bits_LUT[256] = {COUNT_BITS};
	
	assert(index <= NO_OF_BITS);
	
	for (; CHAR_BIT > i; ++i)
	{
		count += count_bits_LUT[holder[i]];
	}
	return count;
	
	return bit_array;
}
	





