#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#define BLOCK_SIZE 16

void encode(char *filename, char *keyfile, char *newfile) {
    int filefd = open(filename, O_RDONLY);
    if (filefd < 1) {
        printf("Error opening text file: %s\n", strerror(errno));
        exit(1);
    }

    int keyfd = open(keyfile, O_RDONLY);
    if (keyfd < 1) {
        printf("Error opening key file: %s\n", strerror(errno));
        exit(1);
    }

    int newfilefd = open(newfile, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    if (newfilefd < 1) {
        printf("Error creating/opening new file: %s\n", strerror(errno));
        exit(1);
    }

    char key[BLOCK_SIZE];
    int key_bytes_read = read(keyfd, key, BLOCK_SIZE);
    if (key_bytes_read < BLOCK_SIZE) {
        printf("Key file doesn't contain enough bytes\n");
        exit(1);
    }

    char plaintext[BLOCK_SIZE];
    char ciphertext[BLOCK_SIZE];

    ssize_t bytes_read;
    ssize_t bytes_written;

    while ((bytes_read = read(filefd, plaintext, BLOCK_SIZE)) > 0) {
        // Perform the encoding operation here
        // Modify the plaintext to obtain the ciphertext using the provided key

        // Example: XOR the plaintext with the key
        int i;
        for (i = 0; i < BLOCK_SIZE; i++) {
            ciphertext[i] = plaintext[i] ^ key[i];
        }

        bytes_written = write(newfilefd, ciphertext, bytes_read);
        if (bytes_written != bytes_read) {
            printf("Error writing to the new file: %s\n", strerror(errno));
            exit(1);
        }
    }

    if (bytes_read < 0) {
        printf("Error reading the text file: %s\n", strerror(errno));
        exit(1);
    }

    printf("Encoding completed successfully.\n");

    close(filefd);
    close(keyfd);
    close(newfilefd);
}

int main() {
    encode("file", "key", "newfile");
    return 0;
}
