#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


char transform[128] = {215, 119, 245, 133, 134, 202, 56, 57, 182, 68, 102, 149, 118, 232, 169, 140, 152, 168, 96, 110, 131, 161, 114, 13, 198, 26, 127, 167, 229, 84, 111, 121, 187, 164, 18, 239, 165, 2, 227, 80, 125, 104, 238, 246, 197, 192, 36, 156, 74, 93, 67, 25, 221, 157, 240, 87, 184, 70, 170, 81, 52, 64, 190, 92, 186, 174, 247, 61, 158, 19, 185, 191, 163, 11, 142, 101, 54, 237, 194, 144, 99, 53, 171, 129, 122, 154, 69, 39, 243, 179, 230, 151, 226, 0, 46, 209, 48, 63, 31, 86, 188, 225, 211, 8, 82, 94, 23, 199, 248, 34, 176, 203, 6, 126, 147, 71, 4, 130, 162, 98, 41, 106, 228, 148, 15, 159, 32, 89};

int main(){
    char input[256];
    int i = 0;
    read(0, input, 30);

    int len = strlen(input);
    for(int i = 0; i < len; i++){
        input[i] = input[i] ^ transform[input[i]];
    }

    getchar();
}