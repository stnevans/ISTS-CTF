#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

#include <sys/mman.h>

#define PAGE_SIZE 4096
void runCode(uint8_t code[]){
    typedef uint64_t( * func)(void);
    uint64_t(*funcPtr)();
    funcPtr = code;

    (*funcPtr)();
}

uint8_t byte1[] = {0xc8,0x0f,0x0f};
uint8_t byte2[] = {0x80,0x34,0x05};

void filterCode(uint8_t code[]){
    for(int i = 0; i < 256; i++){
        //No syscalls
        if(code[i] == 0xff){
            code[i] = 0x90;
        }
        for(int j = 0; j < 3; j++){
            if(code[i] == byte1[j]){
                if(code[i+1] == byte2[j]){
                    code[i] = 0x90;
                    i++;
                    code[i] = 0x90;
                }
            }
        }

    }
}

void inputCode(uint8_t code[]){
    fgets(code, 256, stdin);
}

char * my_fgets(char buffer[], int max_size){
    int i = 0;
    for(; i < max_size; i++){
        buffer[i] = getc(stdin);
        if(buffer[i] == '\n'){
            break;
        }
    }
    if(i < max_size){
        buffer[++i] = 0;
    }
    return buffer;
}

char number_buffer[20];
int main(){
    setvbuf(stdout, NULL, _IONBF, 0);

    alarm(30);
    unsigned long int  __attribute__((no_reorder)) test;
    char __attribute__((no_reorder)) input[8];

    uint8_t * code = mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    puts("What's your favorite number?");
    memset(input, 0, sizeof(input));
    test = strtoul(fgets(number_buffer, sizeof(number_buffer), stdin), NULL, 10);
    printf("%llu. Good choice.\nWeclome to jit-v2\n", test);

    while(1){
        puts("Either run or input your code. Just don't use any sketchy instructions.");
        my_fgets(input, sizeof(input));
        filterCode(code);
        if(strstr(input, "input")){
            puts("Give us your input.");
            inputCode(code);
        }
        if(strstr(input, "run")){
            puts("Running your code.");
            runCode(code);
        }

        if(strstr(input, "end")){
            break;
        }
    }
    printf("Cya\n");
}
