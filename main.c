#include "chip8.h"

int main(void)
{
    Chip8 chip8;
    chip8Init(&chip8);
    
    chip8.memoria[512] = 0x23;
    chip8.memoria[513] = 0x00;

    chip8.memoria[768] = 0x00;
    chip8.memoria[769] = 0xEE;

    chip8Decode(&chip8);
    printf("\n%d", chip8.pc);
    printf("\n%d", chip8.sp);

    chip8Decode(&chip8);
    printf("\n%d", chip8.pc);
    printf("\n%d", chip8.sp);
}