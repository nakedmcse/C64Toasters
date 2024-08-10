all: C64Toasters.c
	gcc -O3 -o C64Toasters C64Toasters.c

c64:
	cl65 -O -o C64Toasters.prg C64Toasters.c

disk:
	c1541 -format C64Toasters,id d64 C64Toasters.d64 -attach C64Toasters.d64 -write C64Toasters.prg

clean:
	rm -f C64Toasters.prg