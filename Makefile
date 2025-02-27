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
	echo ".rgn_linker : {" > output/rgn_linker.x && readelf -sW regina.elf | awk '{if ($$5 == "GLOBAL" && ($$4 == "FUNC" || $$4 == "OBJECT")) printf("\t%s = 0x%s;\n", $$8, $$2)}' >> output/rgn_linker.x && echo "}" >> output/rgn_linker.x
	mv source/*.asm output/asm/
	mv regina.elf output/regina.elf
	mv regina.bin output/regina.bin

clean: 
	-rm source/*.o
	-rm source/*.ao
	-rm source/*.asm
	-rm -rf output