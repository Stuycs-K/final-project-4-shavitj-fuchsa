#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>
#include "tables.h"

int roundnum[] = {
 1   
 };



void convertCharArrayToBits(char charArray[], int intArray[]) {
    int i, j;

    for (i = 0, j = 0; i < 8; i++, j += 8) {
        char c = charArray[i];

        for (int k = 7; k >= 0; k--) {
            intArray[j + k] = (c >> k) & 1;
        }
    }
}

//scarmbles the bits of the block of cipher
 void initial_text_permutation(int * plaintext_bits, int * permutation_bits){
        for(int i = 0; i < 64; i++){
            int index = initial_message_permutation[i];
            permutation_bits[i] = plaintext_bits[index];
        }
    }


// shifts and int array a certain amount of spaces
// negative numbers to shfit to the lefts
void shift_array(int arr[], int len, int shift){

    int temp[len];

    for(int i=0; i < len; i++)

        temp[i] = arr[i];

    if(shift > 0) {

        for(int i=0; i < shift; i++)

            arr[i] = temp[len-i-1];

   
        for(int i=shift; i < len; i++)

            arr[i] = temp[i-shift];

    }

    else if(shift < 0) {

        for(int i=0; i < len - abs(shift); i++){

            arr[i] = temp[i + abs(shift)];

        }
        for(int i=len-abs(shift); i < len; i++){

            arr[i] = temp[i - abs(shift)];
        }
    };

}

void combineArrays(int* array1, int* array2, int* combinedArray) {
    int i;

    for (i = 0; i < 28; i++) {
        combinedArray[i] = array1[i];
    }

    for (i = 0; i < 28; i++) {
        combinedArray[i + 28] = array2[i];
    }
}

// removes every 8th bit
//key will be a length of 8 bytes where every char will either have avalue of 0 or 1
// key is a string of 8 charectars
// each value of the int array represetns the value of the bits
void deleteEvery8thBit(unsigned char* input, unsigned int* output) {
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
    
    
    
}

// creates a key 48 bit key given a 56 bit key
// key_48 must be size 48 
// key_56 must be size 56
void select_48_of_56_bits(int * key_56, int * key_48){
    for(int i = 0; i < 48; i++){
        int index = sub_key_56_to_48[i];
        key_48[i] = key_56[index];
    }
}


// splits 64 bit text into left side of 32 bits and right side of 32 bits
void split_text_in_2(int *text_64, int *lpt_32, int *rpt_32){
    for(int i = 0; i<32; i++){
        lpt_32[i] = text_64[i];
        rpt_32[i] = text_64[i + 32];
    }
}

// splits 58 bit key into left side of 28 bits and right side of 28 bits
void split_key_in_2(int *key_56, int *lkey_28, int *rkey_28){
    for(int i = 0; i<28; i++){
        lkey_28[i] = key_56[i];
        rkey_28[i] = key_56[i + 28];
    }
}

// takes an array of size 4 and add the 1st and 4th values to the end to make an array of 6
void expand_array_4_to_6(int arr_in[], int len_in, int arr_out[]){
    for(int i=0; i<len_in / 4; i++) {
        for(int j=0; j<4; j++)
            arr_out[i * 6 + j] = arr_in[i * 4 + j];
        
        arr_out[i * 6 + 4] = arr_in[i * 4];
        arr_out[i * 6 + 5] = arr_in[i * 4 + 3];
    }
}

// expands the rpt from 32 bits to 48 bits
// adds 4 bits from rpt_32 to expanded_48 and then add bits 1 and 4 to the end
void expand_rpt(int *rpt_32, int *expanded_48){
    int shift = 0;
    for(int i = 0; i<32; i+=4){
        expanded_48[i + shift] = rpt_32[i];
        expanded_48[i + shift + 1] = rpt_32[i + 1];
        expanded_48[i + shift + 2] = rpt_32[i + 2];
        expanded_48[i + shift + 3] = rpt_32[i + 3];
        expanded_48[i + shift + 4] = rpt_32[i];
        expanded_48[i + shift + 5] = rpt_32[i + 3];
        shift += 2;
    }
}

// This might be the correct way to do it??? 
// This is correct
void expansion_rpt(int *rpt_32, int *expanded_48){
    for(int i = 0; i < 48; i++){
        int index = expand[i];
        expanded_48[i] = rpt_32[index];
    }
}

void sbox_substiution(int *arr_in, int len_in, int map[4][16], int *arr_out){
    for(int k=0; k<len_in / 6; k++) {
        int i = k * 6;
        int i_row = arr_in[i] * 2 + arr_in[i+5]; // 1st and 6th bits compose row number
        int i_col = 0; 
        
        for(int j=1; j<5; j++) 
            i_col += arr_in[i+j] * pow(2, 4-j); // 2-5 bits compose col number

        int n = map[i_row][i_col];
        
        i = k * 4;
        for(int j=0; j<4; j++)
            arr_out[i+j] = (n >> (3-j)) & 1;
    }
}

int main(){
    char *initial_key = malloc(8);
    char *plaintext = malloc(8);
    plaintext = "12345678";
    initial_key = "12345678";

    // text arrays
    int *plain_bits_64 = malloc(64 * sizeof(int));
    int *first_permutation_64 = malloc(64 * sizeof(int));
    int *lpt_32 = malloc(32 * sizeof(int));
    int *rpt_32 = malloc(32 * sizeof(int));
    int *expanded_48 = malloc(48 * sizeof(int));
    int *xor_holder_48 = malloc(48 * sizeof(int));

    //key arrays
    int *key_64 = malloc(64 * sizeof(int));
    int *key_56 = malloc(56 * sizeof(int));
    int *key_48 = malloc(48 * sizeof(int));
    int *lkey_28 = malloc(28 * sizeof(int));
    int *rkey_28 = malloc(28 * sizeof(int));

    // text operations
    convertCharArrayToBits(plaintext, plain_bits_64);
    initial_text_permutation(plain_bits_64, first_permutation_64);
    split_text_in_2(first_permutation_64, lpt_32, rpt_32);

    // key operations
    convertCharArrayToBits(initial_key, key_64);
    deleteEvery8thBit(initial_key, key_56);

    for(int round = 1; round <= 16; round++){
        // controls how much to do a left shift
        int shift = -2;
        if(round = 1 | 2 | 9 | 16){
            shift = -1;
        }

        split_key_in_2(key_56, lkey_28, rkey_28);
        shift_array(lkey_28, 28, shift);
        shift_array(rkey_28, 28, shift);
        combineArrays(lkey_28, rkey_28, key_56);
        select_48_of_56_bits(key_56, key_48);        
        // key is read to be used for encryption

        // rpt is xored by key
        expansion_rpt(rpt_32, expanded_48);
        for (int i = 0; i < 48; i++){
            xor_holder_48[i] = expanded_48[i] ^ key_48[i];
        }
        
        // substiution boxes function goes here
        for (int i = 0; i < 8; i++){
            
        }
    }

    return 0;
}