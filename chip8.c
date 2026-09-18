#include "chip8.h"


void chip8Init(Chip8* c)
{   
    srand(time(NULL));
    memset(c, 0, sizeof(*c));
    c->pc=0x200;
    //DIGITO 0
    c->memoria[inicioFuente] = 0xF0;
    c->memoria[inicioFuente+1] = 0x90;
    c->memoria[inicioFuente+2] = 0x90;
    c->memoria[inicioFuente+3] = 0x90;
    c->memoria[inicioFuente+4] = 0xF0;

    //DIGITO 1
    c->memoria[inicioFuente+5] = 0x20;
    c->memoria[inicioFuente+6] = 0x60;
    c->memoria[inicioFuente+7] = 0x20;
    c->memoria[inicioFuente+8] = 0x20;
    c->memoria[inicioFuente+9] = 0x70;

    //DIGITO 2
    c->memoria[inicioFuente+10] = 0xF0;
    c->memoria[inicioFuente+11] = 0x10;
    c->memoria[inicioFuente+12] = 0xF0;
    c->memoria[inicioFuente+13] = 0x80;
    c->memoria[inicioFuente+14] = 0xF0;

    //DIGITO 3
    c->memoria[inicioFuente+15] = 0xF0;
    c->memoria[inicioFuente+16] = 0x10;
    c->memoria[inicioFuente+17] = 0xF0;
    c->memoria[inicioFuente+18] = 0x10;
    c->memoria[inicioFuente+19] = 0xF0;

    //DIGITO 4
    c->memoria[inicioFuente+20] = 0x90;
    c->memoria[inicioFuente+21] = 0x90;
    c->memoria[inicioFuente+22] = 0xF0;
    c->memoria[inicioFuente+23] = 0x10;
    c->memoria[inicioFuente+24] = 0x10;

    //DIGITO 5
    c->memoria[inicioFuente+25] = 0xf0;
    c->memoria[inicioFuente+26] = 0x80;
    c->memoria[inicioFuente+27] = 0xF0;
    c->memoria[inicioFuente+28] = 0x10;
    c->memoria[inicioFuente+29] = 0xf0;

    //DIGITO 6
    c->memoria[inicioFuente+30] = 0xf0;
    c->memoria[inicioFuente+31] = 0x80;
    c->memoria[inicioFuente+32] = 0xF0;
    c->memoria[inicioFuente+33] = 0x90;
    c->memoria[inicioFuente+34] = 0xf0;

    //DIGITO 7
    c->memoria[inicioFuente+35] = 0xf0;
    c->memoria[inicioFuente+36] = 0x10;
    c->memoria[inicioFuente+37] = 0x20;
    c->memoria[inicioFuente+38] = 0x40;
    c->memoria[inicioFuente+39] = 0x40;

    //DIGITO 8
    c->memoria[inicioFuente+40] = 0xf0;
    c->memoria[inicioFuente+41] = 0x90;
    c->memoria[inicioFuente+42] = 0xf0;
    c->memoria[inicioFuente+43] = 0x90;
    c->memoria[inicioFuente+44] = 0xf0;

    //DIGITO 9
    c->memoria[inicioFuente+45] = 0xf0;
    c->memoria[inicioFuente+46] = 0x90;
    c->memoria[inicioFuente+47] = 0xf0;
    c->memoria[inicioFuente+48] = 0x10;
    c->memoria[inicioFuente+49] = 0xf0;

    //DIGITO A
    c->memoria[inicioFuente+50] = 0xf0;
    c->memoria[inicioFuente+51] = 0x90;
    c->memoria[inicioFuente+52] = 0xf0;
    c->memoria[inicioFuente+53] = 0x90;
    c->memoria[inicioFuente+54] = 0x90;   

    //DIGITO B
    c->memoria[inicioFuente+55] = 0xe0;
    c->memoria[inicioFuente+56] = 0x90;
    c->memoria[inicioFuente+57] = 0xe0;
    c->memoria[inicioFuente+58] = 0x90;
    c->memoria[inicioFuente+59] = 0xe0;   

    //DIGITO C
    c->memoria[inicioFuente+60] = 0xf0;
    c->memoria[inicioFuente+61] = 0x80;
    c->memoria[inicioFuente+62] = 0x80;
    c->memoria[inicioFuente+63] = 0x80;
    c->memoria[inicioFuente+64] = 0xf0;  
    
    //DIGITO D
    c->memoria[inicioFuente+65] = 0xe0;
    c->memoria[inicioFuente+66] = 0x90;
    c->memoria[inicioFuente+67] = 0x90;
    c->memoria[inicioFuente+68] = 0x90;
    c->memoria[inicioFuente+69] = 0xe0;   

    //DIGITO E
    c->memoria[inicioFuente+70] = 0xf0;
    c->memoria[inicioFuente+71] = 0x80;
    c->memoria[inicioFuente+72] = 0xf0;
    c->memoria[inicioFuente+73] = 0x80;
    c->memoria[inicioFuente+74] = 0xf0;   

    //DIGITO F
    c->memoria[inicioFuente+75] = 0xf0;
    c->memoria[inicioFuente+76] = 0x80;
    c->memoria[inicioFuente+77] = 0xf0;
    c->memoria[inicioFuente+78] = 0x80;
    c->memoria[inicioFuente+79] = 0x80;   
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
void chip8Disminuir(Chip8* c)
{
    if(c->delayTimer > 0)
        c->delayTimer--;
    if(c->soundTimer > 0)
        c->soundTimer--;
}

int chip8CargarRom(Chip8* c, char* rutaArchivo)
{
    FILE * rom = fopen(rutaArchivo, "rb"); //no indicaste en lectura o escritura
    if(!rom)
        return ERR_ARCH;

    fseek(rom, 0L, SEEK_END);

    size_t tam = ftell(rom);
    
    fseek(rom, 0L, SEEK_SET);
    if(0x200 + tam > 4096)
    {
        fclose(rom);
        return ERR_MEM;
    }
    
    if(fread(&c->memoria[0x200], sizeof(char), tam, rom ) != tam)
    {
        fclose(rom);
        return ERR_ARCH;
    }
        
    fclose(rom);
    return EXITO;
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
        case 0x0: 
            switch(dir)
            {
                case clearScreen:
                    memset(c->pantalla, 0, sizeof(c->pantalla));
                    c->pc+=2;
                    break;
                case retPCFromSP:  
                    if(c->sp==0)
                        return ERR_STK; 
                    c->sp--;
                    c->pc = c->stack[c->sp];
                    break;
                default:
                    return ERR_INS;
            }

            
            break;
        case saveDirInPC: // guardar dir en pc
            c->pc=dir;
            break;
        case saveNextDirInPC:
            if(c->sp >= 16)
                return ERR_STK;
            
            c->stack[c->sp] = c->pc+2;
            c->sp++;
            c->pc=dir;
            break;
        case skipIfVxEq:// saltear prox ins si ==
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
        case skipIfVxNotEq:// saltear prox ins si !=
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
        
        case skipIfVxEqVy:
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
        case saveInVx:
            {
                uint16_t pos = dir>>8;
                pos &= 0xf;
                uint8_t dato = dir&0xff;
                c->regV0VF[pos] = dato;
                c->pc+=2;
            }
            break;
        case addInVx: 
            {
                uint16_t pos = dir>>8;
                pos &= 0xf;
                uint8_t dato = dir&0xff;
                c->regV0VF[pos] += dato;
                c->pc+=2;
            }
            break;
        case opInVxVy: 
            {   
                uint16_t x = dir>>8;
                x &= 0xf;
                uint8_t y = dir&0xf0;
                y>>=4;
                int operacion = dir & 0x00f;
                switch(operacion)
                {   
                    case 0x0: //GUARDAR VY EN VX
                            c->regV0VF[x] = c->regV0VF[y];
                        break;
                    case 0x1://GUARDAR VX OR VY EN VX
                            c->regV0VF[x] |= c->regV0VF[y];
                        break;
                    case 0x2://GUARDAR VX AND VY EN VX
                            c->regV0VF[x] &= c->regV0VF[y];
                        break;
                    case 0x3://GUARDAR VX XOR VY EN VX
                            c->regV0VF[x] ^= c->regV0VF[y];
                        break;
                    case 0x4://GUARDAR VX + VY EN VX Y CARRY EN VF
                        {
                            uint16_t suma = c->regV0VF[x] + c->regV0VF[y];
                            c->regV0VF[x] = suma;
                            if(suma>255)
                                c->regV0VF[vf] = 1;
                            else
                                c->regV0VF[vf] = 0;
                        }
                        break;
                    case 0x5://GUARDAR VX - VY EN VX Y BORROW EN VF
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
                    case 0x6: //GUARDAR VX CORRIDO UN BIT A LA DERECHA, BIT CORRIDO EN VF
                        {
                            uint16_t bitCorrido = c->regV0VF[x] & 1;
                            c->regV0VF[x]>>=1;
                            c->regV0VF[vf] = bitCorrido;
                        }
                        break;
                    case 0x7: //GUARDAR VY - VX EN VX Y BORROW EN VF
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
                    case 0xE: //GUARDAR VX CORRIDO UN BIT A LA IZQUIERDA, BIT CORRIDO EN VF
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
        case skipIfVxNotEqVy: 
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
        case saveDirInI:
            c->regI = dir;
            c->pc+=2;
            break;
        case saveAddDirV0InPC:
            c->pc = dir + c->regV0VF[0];
            break;
        case drawPixels:
            {
                uint16_t x = dir>>8;
                x &= 0xf;
                uint8_t y = dir&0xf0;
                y>>=4;
                int filas = dir & 0x00f;
                int colision=0;
                if((c->regI + filas -1) > 4095)
                    return ERR_MEM;

                for(int i=0; i<filas ; i++)
                {
                    
                    for(int j=0; j<8 ; j++)
                        {
                            int pantallaX = (c->regV0VF[x] + j) % 64;
                            int pantallaY = (c->regV0VF[y] + i) % 32;

                            int escribir = (c->memoria[c->regI + i] >> (7-j)) & 1;
                            
                            if(c->pantalla[pantallaY][pantallaX] && escribir)
                                colision = 1;
                              
                            c->pantalla[pantallaY][pantallaX] ^= escribir;
                        }
                        
                }
                c->regV0VF[vf] = colision;  
                c->pc += 2;
            }

            break;

            case 0xC: //RAND NUMBER
                {   
                    int x = (dir>>8);
                    int nn = dir & 0xFF;
                    c->regV0VF[x] = (rand()%256) & nn;
                    c->pc+=2;
                }   

            break;
            
            case 0xE: //READ KEY
                {   
                    int x = (dir>>8);
                    int ins = dir&0XFF;
                    switch(ins)
                    {   
                        case 0xA1:
                        {
                                int pos = c->regV0VF[x];
                                if(pos>15)
                                    return ERR_INS;
                                c->pc+= c->teclas[pos] ? 2 : 4;
                        }
                        break;
                        case 0x9E:
                            {
                                int pos = c->regV0VF[x];
                                if(pos>15)
                                    return ERR_INS;
                                c->pc+= c->teclas[pos] ? 4 : 2;
                            }
                        break;
                        default:
                            return ERR_INS;
                    }
                }   

            break;
        case 0xf:
                    int x = (dir>>8);
                    int ins = dir&0XFF;
                    switch (ins)
                    {
                        case 0x07:
                        {
                            c->regV0VF[x] = c->delayTimer;
                            c->pc+=2;
                        }
                        break;
                        case 0x0A:
                        {
                            int encontrado=-1;
                            for(int i=9; i<16 ; i++)
                            {
                                if(c->teclas[i])
                                    encontrado=i;
                            }
                            if(encontrado != -1)
                            {
                                c->regV0VF[x] = encontrado;
                                c->pc+=2;
                            }
                        }
                        break;
                        case 0x15:
                        {
                            c->delayTimer = c->regV0VF[x];
                            c->pc+=2;
                        }
                        break;
                        case 0x18:
                        {
                            c->soundTimer = c->regV0VF[x];
                            c->pc+=2;
                        }
                        break;
                        case 0x1E:
                        {
                            c->regI += c->regV0VF[x];
                            c->pc+=2;
                        }
                        break;
                        case 0x29:
                        {   
                            if(c->regV0VF[x]>=0 && c->regV0VF[x]<=15)
                            {
                                c->regI = inicioFuente + c->regV0VF[x] * 5;
                                c->pc+=2;
                            }
                            else
                            {
                                return ERR_INS;
                            }

                            
                            
                        }
                        break;
                        case 0x33:
                        {
                            //Asumi que el orden es como el que dijiste
                            int uni = c->regV0VF[x]%10;
                            int dec = (c->regV0VF[x]%100) / 10;
                            int cen = (c->regV0VF[x]/100);
                            if(c->regI+2>4095)
                                return ERR_MEM;

                            c->memoria[c->regI] = cen;
                            c->memoria[c->regI+1] = dec;                            
                            c->memoria[c->regI+2] = uni;
                            c->pc+=2;
                        }
                        break;
                        case 0x55:
                        {
                            if(c->regI+x >4095)
                                return ERR_MEM;

                            for(int i=0; i<x+1; i++) // asumi que vx tambien es copiado
                            {
                                c->memoria[c->regI+i] = c->regV0VF[i];
                            }
                            c->pc+=2;
                        }
                        break;
                        case 0x65:
                        {
                            if(c->regI+x >4095)
                                return ERR_MEM;
                            for(int i=0; i<x+1; i++) // asumi que vx tambien es copiado
                            {
                                c->regV0VF[i] = c->memoria[c->regI+i];
                            }
                            c->pc+=2;            
                        }
                        break;
                        default:
                            return ERR_INS;
                    }
                break;
        default: 
            return ERR_INS;

    }

    return EXITO;

}