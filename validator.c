#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <capstone/capstone.h>
#include <sys/mman.h>

static inline void check(int result, const char *expr) {
    if (result < 0) {
        perror(expr);
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


typedef struct {
    size_t offset;
    size_t size;
} CodeSection;

void slice_string(const char *src, const CodeSection *section, char *dest) {
    for (size_t i = 0; i < section->size; i++) {
        dest[i] = src[section->offset + i];
    }
}

int validate(char *ptr, size_t len) {
    if (len >= 70) {
        puts("too big");
        return 0;
    }
    int value = (unsigned char)ptr[24];
    printf("0x%x\n", value);
    // Verify ELF magic number
    char magic[4] = {0x7F, 'E', 'L', 'F'};
    if (memcmp(magic, ptr, 4) != 0) {
        printf("not an ELF file\n");
        return 0;
    }

    // Define code sections
    // Define possible code offsets and sizes
    CodeSection codeSections[] = {
        {32,8}, // Example: offset = 24, size = 20 bytes
        {46, len-46}, // Example: offset = 44, size = 10 bytes
        // Add more sections as needed
    };
    size_t numSections = sizeof(codeSections) / sizeof(CodeSection);

    // Validate all sections
    csh handle;
    cs_insn *insn;
    int ret = 1;

    if (cs_open(CS_ARCH_X86, CS_MODE_32, &handle) != CS_ERR_OK) {
        return 0;
    }
    int c=0;
    for (size_t i = 0; i < numSections; i++) {
        CodeSection section = codeSections[i];
        char code[section.size];
        slice_string(ptr, &section, code);

        size_t count = cs_disasm(handle, code, section.size, 0, 0, &insn);
        if (count > 0) {
            for (size_t j = 0; j < count; j++) {
                printf("0x%"PRIx64":\t%s\t\t%s\n", insn[j].address, insn[j].mnemonic, insn[j].op_str);
                
                if (insn[j].mnemonic[0] == 'j' && insn[j].mnemonic[1] == 'm' ) {
                    c++;
                }
                else if(strcmp(insn[j].mnemonic, "int") == 0 && strcmp(insn[j].op_str, "0x80") == 0){
                    c=0;
                    break;
                }
            }
            cs_free(insn, count);
        } else {
            return 0;
        }
    }

    cs_close(&handle);
    if(c>=6 && c<=8){
        return 1;
    }
    else{
        return 0;
    }
}

// gcc -o val validator.c -Wimplicit-function-declaration -lcapstone

int main(int argc, char * const argv[], char * const envp[])  {
    init();
    banner();
    char elf[0x100];
    puts("So wanna play golf but with only jump shots!!!");
    puts("You have to craft a 32 bit ELF binary which has only jump instructions, and the binary should be less than 80 bytes ");
    puts("Here give it a try :");
    size_t n = read(0, elf, 0x100);
    printf("read %d bytes from stdin\n", n);
    if (n>80){
        puts("too big");
        exit(1);
    }
    if (!validate(elf, n)) {
       printf("no cheating :/\n");
       exit(1); 
    }
    int fd=memfd_create("jmp", 0);
    check(write(fd, elf, n), "write");       
    check(fexecve(fd, argv, envp), "fexecve");
}
      