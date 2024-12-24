#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <capstone/capstone.h>

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

    char magic[4] = {0x7F, 'E', 'L', 'F'};
    if (memcmp(magic, ptr, 4) != 0) {
        printf("not an ELF file\n");
        return 0;
    }

    int value = (unsigned char)ptr[24];
    CodeSection codeSections[] = {
        {32,8},
        {48, 16}, 
    };
    size_t numSections = sizeof(codeSections) / sizeof(CodeSection);

    csh handle;
    cs_insn *insn;

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
    if(c>=6){
        return 1;
    }
    else{
        return 0;
    }
}