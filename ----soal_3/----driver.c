#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: ./driver -c [Command] -i [Info]\n");
        return 1;
    }

    char* command = argv[2];
    char* info = argv[3];

    printf("[Driver] [%s]: [%s] [%s]\n", __DATE__, command, info);

    // Assuming communication with paddock.c happens here
    
    return 0;
}

