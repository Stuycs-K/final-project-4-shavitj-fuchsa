#include <stdio.h>

void keyExpansion(const char* masterKey, char* roundKeys, int keySize) {
    int numWords = keySize / 8;
    int numRounds = numWords + 6;

    for (int i = 0; i < numWords; i++)
        roundKeys[i] = masterKey[i];

    int wordIndex = numWords;
    int rconIndex = 1;

    while (wordIndex < (numRounds + 1) * 4) {
        char temp = roundKeys[wordIndex - 1];

        if (wordIndex % numWords == 0) {
            temp = ((temp << 8) | (temp >> 24));

            char s = ((char)Sbox[(temp >> 24) & 255] << 24) |
                     ((char)Sbox[(temp >> 16) & 255] << 16) |
                     ((char)Sbox[(temp >> 8) & 255] << 8) |
                     (char)Sbox[temp & 255];

            temp = s ^ (Rcon[rconIndex++] << 24);
        } 
        else if (numWords > 6 && wordIndex % numWords == 4) {
            temp = ((temp << 8) | (temp >> 24));

            char s = ((char)Sbox[(temp >> 24) & 255] << 24) |
                     ((char)Sbox[(temp >> 16) & 255] << 16) |
                     ((char)Sbox[(temp >> 8) & 255] << 8) |
                     (char)Sbox[temp & 255];

            temp = s;
        }

        roundKeys[wordIndex] = roundKeys[wordIndex - numWords] ^ temp;

        wordIndex++;
    }
}

int main() {
    // Example usage
    char masterKey[16] = "3227650416482833";
    char roundKeys[44];  // For 128-bit key

    keyExpansion(masterKey, roundKeys, 128);

    // Print round keys as ASCII characters
    for (int i = 0; i < 44; i++) {
        printf("Round Key %d: %c%c%c%c\n", i,
            roundKeys[i * 4],
            roundKeys[i * 4 + 1],
            roundKeys[i * 4 + 2],
            roundKeys[i * 4 + 3]);
    }

    return 0;
}
