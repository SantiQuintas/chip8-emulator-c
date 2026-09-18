#include "chip8.h"
#include <SDL2/SDL.h>

int main(int argc, char *argv[])
{
    Chip8 chip8;
    chip8Init(&chip8);

    int ret = chip8CargarRom(&chip8, "Pong.ch8");
    if(ret != EXITO)
        printf("ERROR AL ABRIR EL ARCHIVO\n");
    else
    {   
        if (SDL_Init(SDL_INIT_VIDEO) != 0) 
        {
            printf("Error al inicializar SDL: %s\n", SDL_GetError());
            return 1;
        }

        SDL_Window *ventana = SDL_CreateWindow(
            "CHIP-8",
            SDL_WINDOWPOS_UNDEFINED, 
            SDL_WINDOWPOS_UNDEFINED, 
            640,
            320,
            SDL_WINDOW_SHOWN
        );
        if(!ventana)
        {
            SDL_Quit();
            return 1;
         }
                
        SDL_Renderer *render = SDL_CreateRenderer(
            ventana,
            -1,
             SDL_RENDERER_ACCELERATED
        );
        if(!render)
        {
            SDL_Quit();
            return 1;
        }
                
        int activo = 1;
        SDL_Event evento;
        float acum = 0;
        while(activo)
        {   
            uint32_t tiempoAnt = SDL_GetTicks();
            uint32_t tiempoDelta = SDL_GetTicks()-tiempoAnt;
            acum+=tiempoDelta;
            while(acum >= 16.67)
            {
                chip8Disminuir(&chip8);
                acum-=16.67;
            }
            while (SDL_PollEvent(&evento))
            {
                if (evento.type == SDL_QUIT) 
                {
                    activo = 0;
                }
                if(evento.type == SDL_KEYDOWN || evento.type == SDL_KEYUP)
            {
                switch(evento.key.keysym.sym)
                {
                    case SDLK_0:
                        chip8.teclas[0] = evento.type == SDL_KEYDOWN ? 1 : 0;
                    break;
                    case SDLK_1:
                        chip8.teclas[1] = evento.type == SDL_KEYDOWN ? 1 : 0;
                    break;
                    case SDLK_2:
                        chip8.teclas[2] = evento.type == SDL_KEYDOWN ? 1 : 0;
                    break;
                    case SDLK_3:
                        chip8.teclas[3] = evento.type == SDL_KEYDOWN ? 1 : 0;
                    break;
                    case SDLK_4:
                        chip8.teclas[4] = evento.type == SDL_KEYDOWN ? 1 : 0;
                    break;
                    case SDLK_5:
                        chip8.teclas[5] = evento.type == SDL_KEYDOWN ? 1 : 0;
                    break;
                    case SDLK_6:
                        chip8.teclas[6] = evento.type == SDL_KEYDOWN ? 1 : 0;
                    break;
                    case SDLK_7:
                        chip8.teclas[7] = evento.type == SDL_KEYDOWN ? 1 : 0;
                    break;
                    case SDLK_8:
                        chip8.teclas[8] = evento.type == SDL_KEYDOWN ? 1 : 0;
                    break;
                    case SDLK_9:
                        chip8.teclas[9] = evento.type == SDL_KEYDOWN ? 1 : 0;
                    break;
                    case SDLK_a:
                        chip8.teclas[10] = evento.type == SDL_KEYDOWN ? 1 : 0;
                    break;
                    case SDLK_b:
                        chip8.teclas[11] = evento.type == SDL_KEYDOWN ? 1 : 0;
                    break;
                    case SDLK_c:
                        chip8.teclas[12] = evento.type == SDL_KEYDOWN ? 1 : 0;
                    break;
                    case SDLK_d:
                        chip8.teclas[13] = evento.type == SDL_KEYDOWN ? 1 : 0;
                    break;
                    case SDLK_e:
                        chip8.teclas[14] = evento.type == SDL_KEYDOWN ? 1 : 0;
                    break;
                    case SDLK_f:
                        chip8.teclas[15] = evento.type == SDL_KEYDOWN ? 1 : 0;
                    break;                     
                    default:


                    }
                }
            }

  
            int decode = chip8Decode(&chip8);
            if(decode != EXITO)
            {
                printf("ERROR DE INSTRUCCION\n");
                activo = 0;
            }
            SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
            SDL_RenderClear(render);
            for(int f=0 ; f < 32; f++)
            {
                for(int c=0 ; c < 64; c++)
                {
                    if(chip8.pantalla[f][c])
                    {
                        SDL_Rect rect = {c*10,f*10,10,10};
                        SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
                        SDL_RenderFillRect(render, &rect);
                    }
                  
                }
            }

            
            
            
            SDL_RenderPresent(render);
        }
        SDL_DestroyRenderer(render);
        SDL_DestroyWindow(ventana);
        SDL_Quit();

    }
    
    

    return EXITO;
}