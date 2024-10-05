SRCDIR = source
SRCS = $(wildcard source/*.c)
OBJS = $(SRCS:.c=.o) source/boot.ao

CFLAGS = -Wall -Os -std=gnu99 -nostdlib -fno-builtin
LDFLAGS = -T linker.x -nostartfiles -nostdlib -nodefaultlibs

all: output/regina.bin

%.o: %.c
	psp-gcc -S -o $@.asm $< $(CFLAGS)
	psp-gcc -c -o $@ $< $(CFLAGS)

%.ao: %.s
	psp-gcc -c -o $@ $< $(CFLAGS)

regina.elf: $(OBJS)
	psp-gcc -o $@ $^ $(LDFLAGS)

regina.bin: regina.elf
	psp-objcopy -O binary $< $@

output/regina.bin: regina.bin
	-rm source/*.o
	-rm source/*.ao
	-rm -rf output
	mkdir output
	mkdir output/asm
	mv source/*.asm output/asm/
	mv regina.elf output/regina.elf
	mv regina.bin output/regina.bin

clean: 
	-rm source/*.o
	-rm source/*.ao
	-rm source/*.asm
	-rm -rf output