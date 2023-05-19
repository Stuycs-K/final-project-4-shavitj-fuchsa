#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>

void encode(char *filename){
    int fd = open(filename, O_RDONLY);
    if(fd < 1){
        printf("%s\n",strerror(errno));  
        exit(1);  
    }
}

int main(){
    encode("fdile");
}