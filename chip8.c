#include "chip8.h"


void chip8Init(Chip8* c)
{   
    memset(c, 0, sizeof(*c));
    c->pc=0x200;
}

int chip8Fetch(Chip8* c)
{
    if(c->pc >= 4095)
    {
        return ERR_MEM;
    }
    uint8_t ins1 = c->memoria[c->pc];
    uint8_t ins2 = c->memoria[c->pc+1];
    uint16_t insCompleta = (ins1<<8) | ins2;
    return insCompleta;
}

int chip8Decode(Chip8* c)
{
    int linea = chip8Fetch(c);
    if(linea <= ERR_MEM)
        return linea;

    uint8_t instruccion = linea>>12 ;
    uint16_t dir = linea & 0x0fff;
    switch(instruccion)
    { 
        case 0x0: // guardar dir en pc
            switch(dir)
            {
                case 0x0E0:
                    memset(c->pantalla, 0, sizeof(c->pantalla));
                    c->pc+=2;
                    break;
                case 0x0EE:  
                    if(c->sp==0)
                        return ERR_STK; 
                    c->sp--;
                    c->pc = c->stack[c->sp];
                    break;
                default:
                    return ERR_INS;
            }

            
            break;
        case 0x1: // guardar dir en pc
            c->pc=dir;
            break;
        case 0x2: // guardar dir en pc
            if(c->sp >= 16)
                return ERR_STK;
            
            c->stack[c->sp] = c->pc+2;
            c->sp++;
            c->pc=dir;
            break;
        case 0x3:// saltear prox ins si ==
            {
                uint16_t pos = dir>>8;
                pos &= 0xf;
                uint8_t dato = dir&0xff;
                if(c->regV0VF[pos] == dato)
                    c->pc+=4;
                else
                    c->pc+=2;
            }
            break;
        case 0x4:// saltear prox ins si !=
            {
                uint16_t pos = dir>>8;
                pos &= 0xf;
                uint8_t dato = dir&0xff;
                if(c->regV0VF[pos] == dato)
                     c->pc+=2;    

                else
                    c->pc+=4;                  
            }

            break;
        
        case 0x5:
            {
                if((dir & 0x00f) != 0)
                    return ERR_INS;
                

                uint16_t x = dir>>8;
                x &= 0xf;
                uint8_t y = dir&0xf0;
                y>>=4;
                if(c->regV0VF[x] == c->regV0VF[y])
                    c->pc+=4;      
                else
                    c->pc+=2;    
                
            }
            break;
        case 0x6:
            {
                uint16_t pos = dir>>8;
                pos &= 0xf;
                uint8_t dato = dir&0xff;
                c->regV0VF[pos] = dato;
                c->pc+=2;
            }
            break;
        case 0x7: 
            {
                uint16_t pos = dir>>8;
                pos &= 0xf;
                uint8_t dato = dir&0xff;
                c->regV0VF[pos] += dato;
                c->pc+=2;
            }
            break;
        case 0x8: 
            {   
                uint16_t x = dir>>8;
                x &= 0xf;
                uint8_t y = dir&0xf0;
                y>>=4;
                int operacion = dir & 0x00f;
                switch(operacion)
                {   
                    case 0x0:
                            c->regV0VF[x] = c->regV0VF[y];
                        break;
                    case 0x1:
                            c->regV0VF[x] |= c->regV0VF[y];
                        break;
                    case 0x2:
                            c->regV0VF[x] &= c->regV0VF[y];
                        break;
                    case 0x3:
                            c->regV0VF[x] ^= c->regV0VF[y];
                        break;
                    case 0x4:
                        {
                            uint16_t suma = c->regV0VF[x] + c->regV0VF[y];
                            c->regV0VF[x] = suma;
                            if(suma>255)
                                c->regV0VF[vf] = 1;
                            else
                                c->regV0VF[vf] = 0;
                        }
                        break;
                    case 0x5:
                        {
                            uint16_t resta = c->regV0VF[x] - c->regV0VF[y];
                            uint16_t notBr = c->regV0VF[x] >= c->regV0VF[y];
                            c->regV0VF[x] = resta;
                            if(notBr)
                                c->regV0VF[vf] = 1;
                            else
                                c->regV0VF[vf] = 0;

                            
                        }
                        break;
                    case 0x6:
                        {
                            uint16_t bitCorrido = c->regV0VF[x] & 1;
                            c->regV0VF[x]>>=1;
                            c->regV0VF[vf] = bitCorrido;
                        }
                        break;
                    case 0x7:
                        {
                            uint16_t resta =  c->regV0VF[y] - c->regV0VF[x];
                            uint16_t br = c->regV0VF[x] > c->regV0VF[y];
                            c->regV0VF[x] = resta;
                            if(br)
                                c->regV0VF[vf] = 0;
                            else
                                c->regV0VF[vf] = 1;
                        }
                        break;
                    case 0xE:
                        {
                            uint16_t bitCorrido = c->regV0VF[x]>>7;
                            c->regV0VF[x]<<=1;
                            c->regV0VF[vf] = bitCorrido;
                        }
                        break;
                    default:
                        return ERR_INS;
                }
                c->pc+=2;

            }
            break;
        case 0x9: 
            {
                if((dir & 0x00f) != 0)
                    return ERR_INS;
                

                uint16_t x = dir>>8;
                x &= 0xf;
                uint8_t y = dir&0xf0;
                y>>=4;
                if(c->regV0VF[x] != c->regV0VF[y])
                    c->pc+=4;      
                else
                    c->pc+=2;    
            }
            break;
        case 0xA:
            c->regI = dir;
            c->pc+=2;
            break;
        case 0xB:
            c->pc = dir + c->regV0VF[0];
            break;
        case 0xD:
            {
                uint16_t x = dir>>8;
                x &= 0xf;
                uint8_t y = dir&0xf0;
                y>>=4;
                int filas = dir & 0x00f;
                
                for(int i=0; i<filas ; i++)
                {
                    
                    for(int j=0; j<8 ; j++)
                        {   
                            int escribir = (c->memoria[c->regI + i] >> 7-j) & 1;
                            c->pantalla[c->regV0VF[y] + i][c->regV0VF[x]+j] ^= escribir;
                        }
                        
                }
            }
            break;
        default: 
            return ERR_INS;

    }

    return EXITO;

}