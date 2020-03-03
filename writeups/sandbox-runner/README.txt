The intended solution:
The function @ 0xa63 reads character in byte by byte into a buffer up to a given max_len.
Basically:
for(; i < max_size; i++){
    buffer[i] = getc(stdin);
    if(buffer[i]=='\n') break
}
with some additional constraints. It's roughly a bad version of fgets();
This means that the return value of it doesn't have to be null terminated.

The main function first reads a number, then calls the fgets-like function to fill a buffer, filters the current code, and then decides whether to run or input code.
The idea was to implement it so that, if you could put "inputrun" in the buffer, it would do both, but the buffer would be smaller than the length of "inputrun".
However, the favorite number variable is stored directly next to this potentially non-null terminated buffer in memory. 
Meaning if you set the favorite number to something with "run in it, the main function will both input and run code.
As the filterCode step is done at the top of the loop, you don't have to worry about the filter, which filters various instructions such as: syscall, sysenter, and anything with ff in it. It converts the bytes to nops(\x90).
So the solution contains sending a special number with "run" in it, the string "input", and then shellcode.

The simpler solution:
Input loader shellcode that doesn't have any of the blacklisted bytes. 
Because the memory is mapped RWX, you can write a loader that decodes shellcode to an address later in the RWX region, then just jump to that address.

The even easier solution:
"inputrun" is actually of length 8, and the buffer is of size 8, meaning you can actually just send "inputrun". Given that this is the case, you can just send "inputrun", and then shellcode.

Other random thoughts:
Even if the memory was RX, you could probably bypass the intended by using ROP to hit a syscall.
Even though sandbox-runner doesn't have the syscall instruction, you could find a pointer to somewhere in libc in various ways, and return to a syscall instruction in there.
To fix that I'd probably also have to blacklist c3(ret).
