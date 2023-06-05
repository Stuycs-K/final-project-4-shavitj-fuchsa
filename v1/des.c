#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>
#include "tables.h"


void convertCharArrayToBits(char charArray[8], int intArray[64]) {
    int i, j;
    for (i = 0; i < 8; i++) {

        char c = charArray[i];

        for (int k = 7; k >= 0; k--) {

            intArray[8*i + 7-k] = (c >> k) & 1;

        }

    }

}


//scarmbles the bits of the block of cipher
 void initial_text_permutation(int * plaintext_bits, int * permutation_bits){
        for(int i = 0; i < 64; i++){
            int index = initial_message_permutation[i];
            permutation_bits[i] = plaintext_bits[index-1];
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

void combineArrays(int* array1, int len_arr1, int* array2, int len_arr2, int* combinedArray){
    int i;

    for (i = 0; i < len_arr1; i++) {
        combinedArray[i] = array1[i];
    }

    for (i = 0; i < len_arr2; i++) {
        combinedArray[i + len_arr1] = array2[i];
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
        key_48[i] = key_56[index - 1];
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
        expanded_48[i] = rpt_32[index -1];
    }
}

void sbox_substiution(int *arr_in_48, int len_in, int *arr_out_32){
    for(int k=0; k<len_in / 6; k++) {
        int i = k * 6;
        int i_row = arr_in_48[i] * 2 + arr_in_48[i+5]; // 1st and 6th bits compose row number
        int i_col = 0; 
        
        for(int j=1; j<5; j++) 
            i_col += arr_in_48[i+j] * pow(2, 4-j); // 2-5 bits compose col number

        int n = S[k][i_row * 16 + i_col];
        
        i = k * 4;
        for(int j=0; j<4; j++)
            arr_out_32[i+j] = (n >> (3-j)) & 1;
    }
}

void substitute_via_table(int *arr_in, int len_in, int * table, int len_table, int *arr_out, int len_out){
    // if((len_in != len_out) | (len_in < len_table)){
    //     printf("lengths dont match\n");
    //     return;
    // }
    for(int i = 0; i < len_table; i++){
        int index = table[i];
        // printf("sub_table index %d\n", index);
        // printf("index %d\n",i);
        arr_out[i] = arr_in[index - 1];
    }
}

// convert int array to string
void convert_to_char_array(int *arr, char *charArr, int size_arr) {
    int i, j;
    for (i = 0, j = 0; i < size_arr; i += 8, j++) {
        char ch = 0;
        int k;
        for (k = 0; k < 8; k++) {
            ch |= (arr[i + k] << (7 - k));
        }
        charArr[j] = ch;
    }
}

void int_array_drop_8 (int arr_in[], int len_in, int arr_out[]){
    for(int i = 0, j = 0; i < len_in; i++, j++ )

    {

        if((i+1) % 8 == 0)

            j--;

        else

            arr_out[j] = arr_in[i];

    }

}


void printArray(int *arr, int size) {
    int i;
    for (i = 1; i <= size; i++) {
        printf("%d ", arr[i - 1]);
        if(i % 7 == 0){
            printf(" ");
        }
    }
    printf("\n");
}

//shift to the left
void leftCircularShift(int arr[], int length, int shift){
    shift = shift % length; // To handle cases where shift > n

    for (int i = 0; i < shift; i++){
        int temp = arr[0];
        for (int j = 0; j < length - 1; j++)
        {
            arr[j] = arr[j + 1];
        }
        arr[length - 1] = temp;
    }
}

int main(){
   
    char *plaintext = "12345656";
    char *initial_key = "abrfgffg";

    // text arrays
    int plain_bits_64[64];
    int first_permutation_64[64];
    int lpt_32[32];
    int rpt_32[32];
    int work_rpt_32[32];
    int expanded_48[48];
    int xor_holder_48[48];
    int after_sbox_32[32];
    int post_sbox_permuation_32[32];
    int final_64[64];


    //key arrays
    int key_64[64] ;
    int key_56[56] ;
    int key_48[48] ;
    int lkey_28[28]; 
    int rkey_28[28]; 

    // text operations
    convertCharArrayToBits(plaintext, plain_bits_64);
    // printArray(plain_bits_64, 64);
    initial_text_permutation(plain_bits_64, first_permutation_64);
    split_text_in_2(first_permutation_64, lpt_32, rpt_32);
    for(int i = 0; i<32; i++){
        work_rpt_32[i] = rpt_32[i];
    }
    // key operations
    convertCharArrayToBits(initial_key, key_64);
    int *temp = malloc(64 * sizeof(int));
    substitute_via_table(key_64, 64, first_key_perm_table, 56, key_56, 56);
    // printf("\n");
    

    for(int round = 1; round <= 16; round++){
        // controls how much to do a left shift
        int shift = 2;
        if(round == 1 | round == 2 | round == 9 | round == 16){
            shift = 1;
        }

        split_key_in_2(key_56, lkey_28, rkey_28);
        leftCircularShift(lkey_28, 28, shift);
        leftCircularShift(rkey_28, 28, shift);
        combineArrays(lkey_28, 28, rkey_28, 28, key_56);

            // for(int i = 1; i <= 56; i++ ){
            //     key_56[i - 1] = i;  
            // }
            
            // printArray(key_56, 56);

        select_48_of_56_bits(key_56, key_48);
        // printArray(key_48, 48);
   
        // key is read to be used for encryption

        // rpt is xored by key
        expansion_rpt(work_rpt_32, expanded_48);
        for(int i = 0; i < 48; i++){
            // xor_holder_48[i] = i;
            xor_holder_48[i] = (int) expanded_48[i] ^ key_48[i];
        }
        
        // substiution boxes function goes here
       
        sbox_substiution(xor_holder_48, 48, after_sbox_32);            
       
        // post sbox permutation
        substitute_via_table(after_sbox_32, 32, post_Sbox, 32, post_sbox_permuation_32, 32);
// 
        int temp1[32]; 
        // switch the rpt and lpt 
        for(int i = 0; i < 32; i++){
            temp1[i] = lpt_32[i] ^ post_sbox_permuation_32[i];
            work_rpt_32[i] = lpt_32[i];
            lpt_32[i] = post_sbox_permuation_32[i];
        }

    }

        printArray(lpt_32, 32);
                printArray(work_rpt_32, 32);

        combineArrays(work_rpt_32, 32, lpt_32, 32, final_64);
        int *a = malloc(64 * sizeof(int));
        substitute_via_table(final_64, 64, PI, 64, a, 64);
        char *charArr= malloc(8);
        convert_to_char_array(a, charArr, 64);
        int fd = open("file", O_WRONLY | O_CREAT, 0666);
        write(fd, charArr, sizeof(charArr));

    return 0;
}