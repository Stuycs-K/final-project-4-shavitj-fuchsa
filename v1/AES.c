#include <stdio.h>
#include <stdlib.h>

void keyExpansion(char masterKey[16]){

    char * keyexpansion[4][4];
    keyexpansion[0][0] = "tumor";
    printf("%s,\n",keyexpansion[0][0]);
    
}

int main(){
    keyExpansion("aa");
}