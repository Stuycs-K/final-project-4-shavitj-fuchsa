#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

void encode(char *filename, char *keyfile){
    int filefd = open(filename, O_RDWR);
    if(filefd < 1){
        printf("text file%s\n",strerror(errno));  
        exit(1);  
    }
    // key has to be 16 charectars long
    int keyfd = open(keyfile, O_RDONLY);
     if(keyfd < 1){
        printf("key file %s\n",strerror(errno));  
        exit(1);  
    }
    char key[128];
    int arg = read(keyfd, key, 16 * sizeof(int));
    printf("the bytes read %d")
    
}

int main(){
    encode("file", "key");
}