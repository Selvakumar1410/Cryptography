#include <stdio.h>
#include <string.h>
#include <ctype.h>

void vigenereCipher(char *plaintext, char *key) {
    int keyLength = strlen(key);
    int textLength = strlen(plaintext);

    for (int i = 0; i < textLength; i++) {
        if (isalpha(plaintext[i])) {
            char keyChar = toupper(key[i % keyLength]);
            char shift = keyChar - 'A';

            if (isupper(plaintext[i])) {
                plaintext[i] = (plaintext[i] - 'A' + shift) % 26 + 'A';
            } else {
                plaintext[i] = (plaintext[i] - 'a' + shift) % 26 + 'a';
            }
        }
    }
}

int main() {
    char plaintext[1000];
    char key[100];

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    printf("Enter the key: ");
    scanf("%s", key);

    size_t len = strlen(plaintext);
    if (len > 0 && plaintext[len - 1] == '\n') {
        plaintext[len - 1] = '\0';
    }

    vigenereCipher(plaintext, key);

    printf("Ciphertext: %s\n", plaintext);

    return 0;
}