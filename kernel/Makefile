CROSS   ?= riscv64-linux-gnu-
CC      := $(CROSS)gcc
LD      := $(CROSS)ld
OBJCOPY := $(CROSS)objcopy

CFLAGS  := -Wall -Wextra -O2 -ffreestanding -nostdlib -nostartfiles \
           -march=rv64imac -mabi=lp64
LDFLAGS := -T linker.ld -nostdlib

all: kernel.elf

kernel.elf: start.o kernel.o linker.ld
	$(CC) $(CFLAGS) -o $@ start.o kernel.o $(LDFLAGS)

start.o: start.S
	$(CC) $(CFLAGS) -c $< -o $@

kernel.o: kernel.c
	$(CC) $(CFLAGS) -c $< -o $@

run: kernel.elf
	qemu-system-riscv64 \
	-machine virt \
	-cpu rv64 \
	-m 128M \
	-nographic \
	-bios none \
	-kernel kernel.elf

clean:
	rm -f *.o kernel.elf

