#include <capstone/capstone.h>
#include <stdio.h>
#include <inttypes.h>

int main() {
    csh handle;                             // Capstone handle
    cs_insn *insn;                          // Capstone instruction array
    const uint8_t code[] = {                // Example x86 machine code
        0xb0,0x0b,                              
        0xbb, 0x40, 0x00, 0x20 , 0x00   ,                  
        0xcd, 0x80
    };
    size_t code_size = sizeof(code);        // Size of machine code
    uint64_t address = 0x1000;              // Base address of code

    // Initialize Capstone for x86_64
    if (cs_open(CS_ARCH_X86, CS_MODE_32, &handle) != CS_ERR_OK) {
        printf("Failed to initialize Capstone\n");
        return -1;
    }

    // Disassemble the machine code
    size_t count = cs_disasm(handle, code, code_size, address, 0, &insn);
    if (count > 0) {
        for (size_t i = 0; i < count; i++) {
            printf("0x%"PRIx64":\t%s\t\t%s\n",
                   insn[i].address, insn[i].mnemonic, insn[i].op_str);
        }
        cs_free(insn, count);               // Free the instruction array
    } else {
        printf("Failed to disassemble given code!\n");
    }

    cs_close(&handle);                      // Close Capstone handle
    return 0;
}
