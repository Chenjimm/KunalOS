NASM      := nasm
GCC       := i686-elf-gcc
LD        := i686-elf-ld
OBJCOPY   := i686-elf-objcopy
QEMU      := qemu-system-i386

# 16-bit absolute relocations are safe here: the boot code is linked at 0x7C00.
NASMFLAGS := -f elf32 -Wall -w-reloc-abs-word
LDFLAGS   := -m elf_i386 -T linker.ld

OBJS      := boot.o stage2.o
BOOT_ELF  := boot.elf
BOOT_BIN  := boot.bin
IMAGE     := os.img

# boot.s reads 127 sectors starting at LBA 1, so the image needs
# 1 + 127 = 128 sectors (64 KiB).
IMAGE_SECTORS := 128

.PHONY: all run debug clean

all: $(IMAGE)

%.o: %.s
	$(NASM) $(NASMFLAGS) $< -o $@

$(BOOT_ELF): $(OBJS) linker.ld
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

$(BOOT_BIN): $(BOOT_ELF)
	$(OBJCOPY) -O binary $< $@

$(IMAGE): $(BOOT_BIN)
	dd if=/dev/zero of=$@ bs=512 count=$(IMAGE_SECTORS)
	dd if=$(BOOT_BIN) of=$@ conv=notrunc
	@echo "built $@"

run: $(IMAGE)
	$(QEMU) -drive format=raw,file=$(IMAGE)

debug: $(IMAGE)
	$(QEMU) -drive format=raw,file=$(IMAGE) -s -S

clean:
	rm -f $(OBJS) $(BOOT_ELF) $(BOOT_BIN) $(IMAGE)
