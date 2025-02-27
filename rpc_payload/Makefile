SRCDIR=source
RGNDIR=../source
SRCS=$(wildcard source/*.c)
OBJS=$(SRCS:.c=.o)

ADDEFS=-I$(RGNDIR)
CFLAGS=-Wall -Os -std=gnu99 -nostdlib -fno-builtin
LDFLAGS=-T linker.x -nostartfiles -nostdlib -nodefaultlibs

all: output/rpcp.bin

%.o: %.c
	psp-gcc -S -o $@.asm $< $(CFLAGS) $(ADDEFS)
	psp-gcc -c -o $@ $< $(CFLAGS) $(ADDEFS)

%.ao: %.s
	psp-gcc -c -o $@ $< $(CFLAGS) $(ADDEFS)

rpcp.elf: $(OBJS)
	psp-gcc -o $@ $^ $(LDFLAGS)

rpcp.bin: rpcp.elf
	psp-objcopy -O binary $< $@

output/rpcp.bin: rpcp.bin
	-rm source/*.o
	-rm source/*.ao
	-rm -rf output
	mkdir output
	mkdir output/asm
	mv source/*.asm output/asm/
	mv rpcp.elf output/rpcp.elf
	mv rpcp.bin output/rpcp.bin

clean: 
	-rm source/*.o
	-rm source/*.ao
	-rm source/*.asm
	-rm -rf output