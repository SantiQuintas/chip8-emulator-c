#ifndef CHIP8_H
#define CHIP8_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

//Codigos DECODE
#define saveDirInPC 0x1
#define saveNextDirInPC 0x2
#define skipIfVxEq 0x3
#define skipIfVxNotEq 0x4
#define skipIfVxEqVy 0x5
#define saveInVx 0x6
#define addInVx 0x7
#define opInVxVy 0x8
#define skipIfVxNotEqVy 0x9
#define saveDirInI 0xA
#define saveAddDirV0InPC 0xB
#define drawPixels 0xD
#define clearScreen 0x0E0
#define retPCFromSP 0x0EE


//Manejo de EXITOS/ERRORES
#define EXITO 0
#define ERR_MEM -1
#define ERR_INS -2
#define ERR_STK -3
#define ERR_ARCH -4

//OTRAS MACROS
#define vf 15
#define inicioFuente 0x50
#define finFuente 0x9F

//CHIP8 STRUCT
typedef struct {
    uint8_t memoria[4096];
    uint8_t regV0VF[16];
    uint16_t regI;
    uint16_t pc;
    uint16_t stack[16];
    uint8_t sp;
    uint8_t pantalla[32][64];
    uint8_t teclas[16];
    uint8_t delayTimer;
    uint8_t soundTimer;
} Chip8;

//PRIMITIVAS
void chip8Init(Chip8* c);
int chip8Fetch(Chip8* c);
int chip8Decode(Chip8* c);
void chip8Disminuir(Chip8* c);
int chip8CargarRom(Chip8* c, char* rutaArchivo);

#endif //CHIP8_H