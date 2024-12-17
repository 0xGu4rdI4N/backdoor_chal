from capstone import Cs, CS_ARCH_X86, CS_MODE_32


# Function to disassemble raw ELF payload
def disassemble_raw_binary(raw_payload):
    md = Cs(CS_ARCH_X86, CS_MODE_32)  # Create a Capstone disassembler for 32-bit x86
    for instruction in md.disasm(raw_payload, 0x08048000):  # Base address as starting ELF entry point
        print(f"0x{instruction.address:x}:\t{instruction.mnemonic}\t{instruction.op_str}")


# Load the entire ELF payload (binary file) as raw bytes
with open("shell", "rb") as f:
    raw_payload = f.read()

# Disassemble the payload
disassemble_raw_binary(raw_payload)
