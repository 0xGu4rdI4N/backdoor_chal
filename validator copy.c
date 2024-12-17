#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <capstone/capstone.h>
#include <sys/mman.h>
#define try(expr) { \
    if (0 > (expr)) { \
        perror("failed to execute "#expr); \
        exit(1); \
    } \
}
int init() {
    setvbuf(stdin, NULL, 2, 0);
    setvbuf(stdout, NULL, 2, 0);
}
void slice_string(const char *src, size_t start, size_t length, char *dest) {
    for (size_t i = 0; i < length; i++) {
        dest[i] = src[start + i];
    }
}
int validate(char* ptr, size_t len) {
    char magic[4] = { 0x7F, 'E', 'L', 'F', };
    if (memcmp(magic, ptr, 4) != 0) {
        printf("not an ELF file :/\n");
        return -1;
    }



    unsigned char value = ptr[24];
    char code[25];
    slice_string(ptr, (int)value, len-(int)value, code);

    csh handle;
    cs_insn *insn;
    int ret = 1;
    
    if (cs_open(CS_ARCH_X86, CS_MODE_32, &handle) != CS_ERR_OK) {
        return 0;
    }
    size_t count = cs_disasm(handle, code, len-(int)value, 0, 0, &insn);
    size_t success_len = 0;

    if (count > 0) {
        for (size_t i = 0; i < count; i++) {
            printf("0x%"PRIx64":\t%s\t\t%s\n",
                   insn[i].address, insn[i].mnemonic, insn[i].op_str);
        }
        cs_free(insn, count);
    } else {
        return 0;
    }

    // cs_close(&handle);

    // ret &= len == success_len;
    // return ret;
}


int main(int argc, char * const argv[], char * const envp[])  {
    init();
    char elf[80];
    puts("So wanna play golf but with only jump shots!!!");
    puts("Here give it a try :");
    size_t n = read(0, elf, 80);
    if (!validate(elf, n)) {
       exit(1); 
    }
    int fd=memfd_create("jmp", 0);
    write(fd, elf, n);        
    try(fexecve(fd,  argv, envp));
}