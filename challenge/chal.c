#include "validator.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <capstone/capstone.h>
#include <sys/mman.h>

static inline void check(int result, const char *expr) {
    if (result < 0) {
        perror("nope, can't spawn a shell");
        exit(1);
    }
}

int init() {
    setvbuf(stdin, NULL, 2, 0);
    setvbuf(stdout, NULL, 2, 0);
}


void banner() {
    printf("  ██████╗   ██████╗ ██╗     ███████╗\n");
    printf(" ██╔════╝  ██╔═══██╗██║     ██╔════╝\n");
    printf(" ██║  ███╗ ██║   ██║██║     █████╗  \n");
    printf(" ██║   ██║ ██║   ██║██║     ██╔══╝  \n");
    printf(" ╚██████╔╝ ╚██████╔╝███████╗██║\n");
    printf("  ╚═════╝   ╚═════╝ ╚══════╝╚═╝\n");
}

// gcc -o val validator.c -Wimplicit-function-declaration -lcapstone

int main(int argc, char * const argv[], char * const envp[])  {
    init();
    banner();
    char elf[0x100];
    puts("Welcome Oo brave one!!");
    puts("I shall run whatever you give me , but there's some conditions:");
    puts("It should be a 32 bit executable but I can only run jmp instructions.");
    puts("One more thing, I am on a little diet so file should be less than 70 bytes");
    puts("Here give it a try :");
    size_t n = read(0, elf, 0x100);
    if (n > 0 && elf[n - 1] == '\n') {
    elf[n - 1] = '\0';
    n -= 1; 
    }
    printf("read %d bytes from stdin\n", n);
    if (!validate(elf, n)) {
       printf("nope, can't spawn a shell\n");
       exit(1); 
    }
    int fd=memfd_create("jmp", 0);
    check(write(fd, elf, n), "write");       
    check(fexecve(fd, argv, envp), "fexecve");
}
      