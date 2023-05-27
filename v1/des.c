#include <stdio.h>
#include <stdlib.h>

// void bytes_to_bits(const unsigned char* bytes, unsigned int* bits) {
//     for (int i = 0; i < 8; i++) {
//         for (int j = 0; j < 8; j++) {
//             unsigned char byte = bytes[i];
//             unsigned char bit = (byte >> j) & 1;
//             int index = (i * 8) + j;
//             bits[index] = bit;
//         }
//     }
// }

// removes every 8th bit
//key will be a lenth of 8 bytes where every char will either have avalue of 0 or 1
void deleteEvery8thBit(const unsigned char* input, unsigned int* output) {
    int temparr[64];
    for (int i = 0; i < 8; i++) {
        unsigned char byte = input[i];
        for (int j = 7; j >= 0; j--) {
            unsigned char bit = (byte >> j) & 1;
            int index = (i * 8) + (7 - j);
            temparr[index] = bit;
        }
    }
    int c = 0;
    for(int b = 0; b<8; b++){
        for(int a = 0; a<7; a++){
            output[c] = temparr[b * 8 + a];
            c++;
        }
    }
    // for (int i = 0; i < 56; i++) {
    //     int srcIndex = i + (i / 7);
    //     int bitIndex = i % 8;
    //     unsigned int srcByte = bits[srcIndex];
    //     output[i] = (srcByte >> bitIndex) & 1;
    // }
}


// gives 56 bit key
// void initial_key_permutation(char* key){ 
//     unsigned int array[64];
//     bytes_to_bits(key, array);
//     unsigned char modifiedkey[56];
//     deleteEvery8thByte(array, modifiedkey);
//     return modifiedkey;
// }



int main(){
    int *arr = malloc(56 * sizeof(int));
    char *it = "87654321";
    deleteEvery8thBit("87654321", arr);
    for(int i = 0; i < 8; i++){
        printf("char: %u\n",it[i]);
    }
    for(int i = 0; i < 56; i++){
        printf("char: %u\n", arr[i]);
    }
}