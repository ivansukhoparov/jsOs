CROSS   ?= riscv64-linux-gnu-
CC      := $(CROSS)gcc
LD      := $(CROSS)ld
OBJCOPY := $(CROSS)objcopy

CFLAGS  := -Wall -Wextra -O2 -ffreestanding -nostdlib -nostartfiles \
           -march=rv64imac_zicsr -mabi=lp64 -mcmodel=medany \
         -fno-pic -fno-pie
LDFLAGS := -T linker.ld -nostdlib -fno-pie

SRCS = \
    kernel.c \
    kprint.c \
	arch/riscv/trap.c \
	panic.c

OBJS = $(SRCS:.c=.o)

all: kernel.elf

kernel.elf: start.o $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

start.o: start.S
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: kernel.elf
	qemu-system-riscv64 \
	-machine virt \
	-cpu rv64 \
	-m 128M \
	-nographic \
	-bios none \
	-kernel kernel.elf\
  -display none \
  -serial mon:stdio \
  -d guest_errors,int \
  -D qemu.log
clean:
	rm -f *.o kernel.elf *.log

