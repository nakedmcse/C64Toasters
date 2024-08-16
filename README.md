# C64Toasters
Commodore 64 Version of Flying Toasters Screensaver.

Built to use PETSCII representations of the taosters, with animation
and parallax effect between the near and far toasters.

## Configuration
The maximum number of toasters in each layer can be adjusted by editing this define:

C64Toasters.c:
```C
#define MAXTOASTERS 4
```

## Building
This uses make and requires both VICE and CC65 to be installed in order to compile.

Build the prg file, which can be loaded into VICE using the smart attach -> autostart feature:
```bash
make
```

Compile the prg file to a D64 disk file:
```bash
make
make disk
```
