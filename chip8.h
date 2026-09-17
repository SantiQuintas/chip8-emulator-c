#ifndef CHIP8_H
#define CHIP8_H

#define EXITO 0
#define ERR_MEM -1
#define ERR_INS -2
#define ERR_STK -3

#define vf 15

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef struct {
    uint8_t memoria[4096];
    uint8_t regV0VF[16];
    uint16_t regI;
    uint16_t pc;
    uint16_t stack[16];
    uint8_t sp;
    uint8_t pantalla[32][64];
} Chip8;

void chip8Init(Chip8* c);
int chip8Fetch(Chip8* c);
int chip8Decode(Chip8* c);
#endif //CHIP8_H