#include <stdio.h>
#include <stdint.h>

#define BLOCK_SIZE_64  8
#define BLOCK_SIZE_128 16

void leftShiftOneBit(uint8_t *data, int size)
 {
    int i;
    uint8_t carry = 0;
    for (i = size - 1; i >= 0; i--)
	 {
        uint8_t nextCarry = (data[i] & 0x80) ? 1 : 0;
        data[i] = (data[i] << 1) | carry;
        carry = nextCarry;
    }
}

void xorBytes(uint8_t *a, uint8_t *b, int size)
 {
    for (int i = 0; i < size; i++) 
	{
        a[i] ^= b[i];
    }
}

void generateSubkeys(uint8_t *key, int keySize, uint8_t *subkeys) 
{
    uint8_t zeroBlock[BLOCK_SIZE_128] = {0};
    uint8_t result[BLOCK_SIZE_128];
    for (int i = 0; i < keySize; i++)
	 {
        result[i] = zeroBlock[i];
    }

    for (int i = 0; i < keySize; i++) 
	{

        leftShiftOneBit(result, keySize);

        if (result[0] & 0x80) 
		{ 

            if (keySize == BLOCK_SIZE_64) 
			{
                xorBytes(result, key, keySize);
            } else if (keySize == BLOCK_SIZE_128)
			 {

                uint8_t const128[BLOCK_SIZE_128] = {0x87, 0x0, 0x0, 0x0,
                                                      0x0,  0x0, 0x0, 0x0,
                                                      0x0,  0x0, 0x0, 0x0,
                                                      0x0,  0x0, 0x0, 0x0};
                xorBytes(result, const128, keySize);
            }
        }

        for (int j = 0; j < keySize; j++) 
		{
            subkeys[i * keySize + j] = result[j];
        }
    }
}

int main() 
{

    uint8_t key[BLOCK_SIZE_128] = {0};
    uint8_t subkeys[BLOCK_SIZE_128 * 2];

    generateSubkeys(key, BLOCK_SIZE_128, subkeys);

    printf("Subkeys:\n");
    for (int i = 0; i < BLOCK_SIZE_128 * 2; i++) 
	{
        printf("%02x ", subkeys[i]);
    }
    printf("\n");

    return 0;
}