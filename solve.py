from pwn import *
from base64 import b64encode
from subprocess import run

# run("nasm -f bin solve.asm -o solve.bin", shell=True, check=True)
# script_path = './chal.py'
p = process("./val")
# gdb.attach(p)
print("1")
data = open("./tini", "rb").read()
# print(data)
p.sendline(data)
print("2")

# # p.sendlineafter(b": ", b"/bin/sh")
p.interactive()