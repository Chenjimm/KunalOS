NASM      := nasm
GCC       := i686-elf-gcc
LD        := i686-elf-ld
OBJCOPY   := i686-elf-objcopy
QEMU      := qemu-system-i386

ROOT      := ..

NASMFLAGS := -f elf32 -Wall -w-reloc-abs-word
LDFLAGS   := -m elf_i386 -T linker.ld
GCCFLAGS  := -m32 -ffreestanding -fno-pic -fno-stack-protector -fno-builtin -nostdinc -c

OBJS      := boot.o stage2.o kernel.o
BOOT_ELF  := boot.elf
BOOT_BIN  := boot.bin
IMAGE     := os.img

IMAGE_SECTORS := 127

.PHONY: all run debug clean

all: $(IMAGE)

boot.o: $(ROOT)/boot/boot.s
	$(NASM) $(NASMFLAGS) $< -o $@

stage2.o: $(ROOT)/boot/stage2.s
	$(NASM) $(NASMFLAGS) $< -o $@

kernel.o: $(ROOT)/kernel/kernel.c
	$(GCC) $(GCCFLAGS) $< -o $@

$(BOOT_ELF): $(OBJS) linker.ld
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

$(BOOT_BIN): $(BOOT_ELF)
	$(OBJCOPY) -O binary $< $@

$(IMAGE): $(BOOT_BIN)
	dd if=/dev/zero of=$@ bs=512 count=$(IMAGE_SECTORS)
	dd if=$(BOOT_BIN) of=$@ conv=notrunc
	@echo "built $@"

run: $(IMAGE)
	$(QEMU) --display cocoa,zoom-to-fit=on -full-screen -drive format=raw,file=$(IMAGE)

debug: $(IMAGE)
	$(QEMU) -drive format=raw,file=$(IMAGE) -s -S

clean:
	rm -f $(OBJS) $(BOOT_ELF) $(BOOT_BIN) $(IMAGE)
