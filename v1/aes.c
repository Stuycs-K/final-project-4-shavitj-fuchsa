#include <stdio.h>
#include <stdlib.h>

int key_arr[4][4];

void shift_array(int arr[], int len, int shift){

    int temp[len];

    for(int i=0; i < len; i++){
        temp[i] = arr[i];
    }

    if(shift > 0) {

        for(int i=0; i < shift; i++)
            arr[i] = temp[len-i-1];

        for(int i=shift; i < len; i++){
            arr[i] = temp[i-shift];
        }
    }

    else if(shift < 0) {

        for(int i=0; i < len - abs(shift); i++){
            arr[i] = temp[i + abs(shift)];
        }

        for(int i=len-abs(shift); i < len; i++){
            arr[i] = temp[i - abs(shift)];
        }
    }

}

create_key_table(){
    
}
int main(){

}