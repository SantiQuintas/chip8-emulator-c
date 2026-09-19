#include "chip8.h"
#include <SDL2/SDL.h>

#define ERR_ARG -4
#define ERR_VID -5
#define ERR_AUD -6
typedef struct{
    Chip8 *chip8;
    float fase;
} audioState;

void callBack(void* userdata, Uint8* stream, int len);

int main(int argc, char *argv[])
{
    Chip8 chip8;
    chip8Init(&chip8);
    if(argc < 2)
    {
        printf("ARGUMENTOS INVALIDOS");
        return ERR_ARG;
    }
        
    
    int ret = chip8CargarRom(&chip8, argv[1]);
    if(ret != EXITO)
        printf("ERROR AL ABRIR EL ARCHIVO\n");
    else
    {   
        if (SDL_Init(SDL_INIT_VIDEO) != 0) 
        {
            printf("Error al inicializar Video: %s\n", SDL_GetError());
            return ERR_VID;
        }

        if (SDL_Init(SDL_INIT_AUDIO) != 0) 
        {
            printf("Error al inicializar Audio: %s\n", SDL_GetError());
            return ERR_AUD;
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


        SDL_RenderSetVSync(render, 1);

        if(!render)
        {
            SDL_Quit();
            return 1;
        }
        SDL_AudioSpec audio = {0};
        audioState state;
        state.chip8 = &chip8;
        state.fase = 0.0;

        audio.freq = 44100;
        audio.format = AUDIO_F32SYS;
        audio.channels = 1;
        audio.samples=512;
        audio.userdata = &state;
        audio.callback = callBack;
        

        int activo =  1;
        SDL_Event evento;
        float acumT = 0;
        float acumI = 0;
        uint32_t tiempoAnt = SDL_GetTicks();
        uint32_t tiempoDelta;
        SDL_AudioDeviceID id = SDL_OpenAudioDevice(NULL, 0, &audio, &audio, 0);
        if(!id)
            puts("ERROR AL ABRIR EL DISPOSITIVO DE AUDIO");

        SDL_PauseAudioDevice(id, 0);

        while(activo)
        {   
            tiempoDelta= SDL_GetTicks()-tiempoAnt;
            tiempoAnt = SDL_GetTicks();

            acumT+=tiempoDelta;
            acumI+=tiempoDelta;
            

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

            while(acumI >= factorInstruccion)
            {
                int decode = chip8Decode(&chip8);
                 if(decode != EXITO)
                {
                    printf("ERROR DE INSTRUCCION\n");
                    activo = 0;
                }
                acumI-= factorInstruccion;
            }
            
            while(acumT >= factorTemporizador)
            {
                chip8Disminuir(&chip8);
                acumT-=factorTemporizador;
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


void callBack(void* userdata, Uint8* stream, int len)
{
    audioState *audioS = (audioState*) userdata;
    float *sF = (float*) stream;
    int cantMuestras = len/sizeof(float);

    if(audioS->chip8->soundTimer > 0 )
    {
        for(int i=0; i<cantMuestras; i++)
        {   
            if(audioS->fase < 0.5)
                sF[i] = 0.025;
            else
                sF[i] = -0.025;

            audioS->fase += 440.0f / 44100.0f;
            if (audioS->fase >= 1.0f)
                audioS->fase--;
        }
    }
    else
    {
        for(int i=0; i<cantMuestras; i++)
        {
            sF[i] = 0.0;
        }
    }
}