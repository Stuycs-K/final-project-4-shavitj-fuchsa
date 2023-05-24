#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE 16

void ecb_encrypt(char *plaintext, char *key, char *ciphertext) {
    // Perform ECB encryption using the provided key

    // Implement your own logic for ECB encryption here
    // This code is for demonstration purposes only and should not be used for secure encryption

    // Example: XOR the plaintext with the key
    for (int i = 0; i < BLOCK_SIZE; i++) {
        ciphertext[i] = plaintext[i] ^ key[i];
    }
}

int main() {
    char key[BLOCK_SIZE + 1];  // +1 for null terminator
    printf("Enter the key (16 characters): ");
    scanf("%16s", key);

    char filename[100];
    printf("Enter the filename to read the text from: ");
    scanf("%99s", filename);

    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *plaintext = (char *)malloc(file_size + 1);
    fread(plaintext, 1, file_size, file);
    plaintext[file_size] = '\0';

    fclose(file);

    int num_blocks = (file_size + BLOCK_SIZE - 1) / BLOCK_SIZE;

    char *ciphertext = (char *)malloc(num_blocks * BLOCK_SIZE + 1);
    ciphertext[num_blocks * BLOCK_SIZE] = '\0';

    for (int i = 0; i < num_blocks; i++) {
        char *current_plaintext = plaintext + (i * BLOCK_SIZE);
        char *current_ciphertext = ciphertext + (i * BLOCK_SIZE);

        if (i == num_blocks - 1 && file_size % BLOCK_SIZE != 0) {
            // Padding the last block if it's not a multiple of BLOCK_SIZE
            memset(current_plaintext + (file_size % BLOCK_SIZE), 0, BLOCK_SIZE - (file_size % BLOCK_SIZE));
        }

        ecb_encrypt(current_plaintext, key, current_ciphertext);
    }

    FILE *newfile = fopen("newfile", "wb");
    if (newfile == NULL) {
        printf("Error creating the new file.\n");
        return 1;
    }

    fwrite(ciphertext, 1, num_blocks * BLOCK_SIZE, newfile);

    fclose(newfile);

    printf("Encryption completed. Encrypted text written to 'newfile'.\n");

    free(plaintext);
    free(ciphertext);

    return 0;
}
h>
void encode(char *filename, char *keyfile, char *newfile){
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
    char key[16];
    int arg = read(keyfd, key, 16);
    printf("the bytes read %d\n",arg );
    

    
    
    
}

int main(){
    encode("file", "key", "newfile");
}