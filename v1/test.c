
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void byte_array_drop_8 (char *s, int byte_array[])
{
    for(int i=0; i < strlen(s); i++ )
    {
        for(int j=0; j < 7; j++)
        {
            byte_array[i * 7+j] = ( s[i] >> 7 - j ) & 1;
        }
    }
}


void shift_array(int arr[], int len, int shift)
{
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
        for(int i=0; i < len - abs(shift); i++)
            arr[i] = temp[i + abs(shift)];
    
        for(int i=len-abs(shift); i < len; i++)
            arr[i] = temp[i - abs(shift)];
    };
}

void expand_array_4_to_6(int arr_in[], int len_in, int arr_out[])
{
    for(int i=0; i<len_in / 4; i++) {
        for(int j=0; j<4; j++)
            arr_out[i * 6 + j] = arr_in[i * 4 + j];
        
        arr_out[i * 6 + 4] = arr_in[i * 4];
        arr_out[i * 6 + 5] = arr_in[i * 4 + 3];
    }
}

void scramble_bits(int arr_in[], int len_in, int map[4][16], int arr_out[])
{
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

/********************************************************/

int main(int argc, char* argv[])
{
    char *param1 = argv[1];
	char *ps = argv[2];

	int S1[4][16] = {
        /* S1 */
        {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
        {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
        {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
        {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}
    };	
	

	
    switch(atoi(param1))
    {
        case 1: // String to bit array, drop 8th bit 
        {
            int ba[strlen(ps) * 7];
            
            printf("Byte array w/0 8th byte\n");
            printf("IN: %s ", ps);
            
            for(int i=0; i < strlen(ps); i++)
                printf("%d ", ps[i]);
            
            byte_array_drop_8(ps, ba);
            
            printf("\nOUT: ");
            for(int i=0; i < strlen(ps) * 7; i++)
                printf("%i ", ba[i]);
        
            printf("\n");
            return 0;
        }
        
        case 2: // Shift array
        {
            int a[] = { 1,2,3,4,5 };
            printf("\nint a[] = { 1,2,3,4,5 }");

            printf("\nshift_array(a, 5, 1): ");
            shift_array(a, 5, 1);
            for(int i=0; i<5; i++)
                printf("%i ", a[i]);
                
            printf("\nshift_array(a, 5, -2): ");
            shift_array(a, 5, -2);
            for(int i=0; i<5; i++)
                printf("%i ", a[i]);
        }
    
        case 3: // Expand array, add 2 elements after each 4
        {
            int a_in[32];
            int a_out[48];
            
            printf("Expand array, add 2 elements after each 4\n");
            printf("int a_in[] = { ");
            for(int i=0; i<32; i++) {
                a_in[i] = i+1;
                printf("%i ", a_in[i]);
            };
            printf("}\n");
            
            printf("expand_array_4_to_6(a_in, 32, a_out); a_out:\n");

            expand_array_4_to_6(a_in, 32, a_out);

            for(int i=0; i<48; i++)
                printf("%i ", a_out[i]);
            
        }
        
        case 4: // Scramble bits
        {
            int a_in[48];
            int a_out[32];
            
            printf("Scramble bits\n");
            printf("int a_in[] = { ");
            for(int i=0; i<48; i+=2) {
                a_in[i] = 1;
                a_in[i+1] = 0;
                printf("%i %i ", a_in[i], a_in[i+1]);
            };
            printf("}\n");
            
            printf("scramble_bits(a_in, 48, S1, a_out); a_out:\n");

            scramble_bits(a_in, 48, S1, a_out);

            for(int i=0; i<32; i++)
                printf("%i ", a_out[i]);
        }
    }
}
