![BIT8](https://chip-8.vercel.app/og_image.png)
# EMULADOR CHIP8 EN C
Emulador de CHIP8 creado en el lenguaje de programacion C, con el fin de practicar y ampliar
mis capacidades.

## Requisitos
### GCC
Necesario para poder compilar el programa
### SDL2
Necesario para poder crear la ventana de la rom, renderizar los graficos, detectar eventos de teclado
y reproducir el audio del juego. Instalar SDL2 y agregarlo a la carpeta del repositorio, copiando SDL2.dll en el mismo lugar que se encuentra chip8.exe (SDL2.dll esta en SDL2-devel-2.32.10-mingw\SDL2-2.32.10\x86_64-w64-mingw32\bin\SDL2.dll)
## Compilacion
Para compilar se puede ejecutar el comando
```
 gcc main.c chip8.c -o chip8.exe -I ".\SDL2-devel-2.32.10-mingw\SDL2-2.32.10\x86_64-w64-mingw32\include" -L ".\SDL2-devel-2.32.10-mingw\SDL2-2.32.10\x86_64-w64-mingw32\lib" -lmingw32 -lSDL2main -lSDL2
```
## Ejecucion
>Asegurarse de que SDL2.dll esta en la misma carpeta que chip8.exe, de no ser asi copiarlo (instrucciones en Requisitos -> SDL2)
Para ejecutar el programa compilado por terminal, utilice el siguiente comando
```
.\chip8.exe nombrejuego.ch8
```
## Controles de Teclado
El emulador mapea directamente los controles de CHIP8 a los mismas teclas en el teclado QWERTY.
Los controles van de 0 a 9, y de A a F.

## ROM de Prueba
Yo para comprobar que el emulador funcionaba correctamente, descargue una ROM de pong Single Player (pong.ch8)
y la inclui dentro de la carpeta donde esta el ejecutable. Para correr esta ROM use el comando:
```
.\chip8.exe pong.ch8
```
## Caracteristicas Implementadas
- Instrucciones CHIP-8 Estandar
- Renderizado 64×32
- Teclado
- Timers
- Carga de ROM
- Beep