#include <stdio.h>
#include <string.h>
#include <openssl/des.h>

unsigned char key[24] = "MYSECRETKEY12345678901234";

// Adjust the IV size to match the block size (8 bytes)
unsigned char iv[8] = "INITVEC00";

void encrypt3DESCBC(unsigned char *input, unsigned char *output, int input_length, unsigned char *key, unsigned char *iv) {
    DES_cblock iv_schedule;
    DES_key_schedule schedule1, schedule2, schedule3;

    DES_set_key_unchecked((DES_cblock *)key, &schedule1);
    DES_set_key_unchecked((DES_cblock *)(key + 8), &schedule2);
    DES_set_key_unchecked((DES_cblock *)(key + 16), &schedule3);

    memcpy(iv_schedule, iv, 8);

    for (int i = 0; i < input_length; i += 8) {
        DES_ncbc_encrypt(input + i, output + i, 8, &schedule1, &iv_schedule, DES_ENCRYPT);
        DES_ncbc_encrypt(output + i, output + i, 8, &schedule2, &iv_schedule, DES_DECRYPT);
        DES_ncbc_encrypt(output + i, output + i, 8, &schedule3, &iv_schedule, DES_ENCRYPT);
    }
}

int main() {
    unsigned char plaintext[] = "PLAINTEXT1234567890";
    int input_length = strlen((char *)plaintext);

    // Adjust the size to accommodate padding
    int ciphertext_size = ((input_length / 8) + 1) * 8;
    unsigned char ciphertext[ciphertext_size];

    encrypt3DESCBC(plaintext, ciphertext, input_length, key, iv);

    printf("Plaintext: %s\n", plaintext);
    printf("Ciphertext: ");
    for (int i = 0; i < ciphertext_size; i++) {
        printf("%02X ", ciphertext[i]);
    }
    printf("\n");

    return 0;
}
