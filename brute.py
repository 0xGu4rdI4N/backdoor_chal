from pwn import *

context.arch = 'i386'  # Set to 32-bit x86

# Desired target bytes to match
target_code = b'\xe9\xac\xba\xfe\xca'

# Base offset template
base_offset = 0xcafeba00  # High 24 bits fixed, last byte to brute-force

for last_byte in range(0x00, 0x100):  # Iterate over all possible values for the last byte
    # Construct the full offset with the current last byte
    full_offset = base_offset | last_byte  # Combine with the last byte

    # Generate the instruction
    try:
        instruction = f"jmp {hex(full_offset)}"
        bytecode = asm(instruction)  # Assemble the instruction

        # Check if the bytecode matches the target
        if bytecode == target_code:
            print(f"Match found!")
            print(f"Instruction: {instruction}")
            print(f"Bytecode: {bytecode.hex()}")
            break
    except PwnlibException as e:
        # Skip relocatable cases (if any)
        print(f"Error for offset {hex(full_offset)}: {e}")
