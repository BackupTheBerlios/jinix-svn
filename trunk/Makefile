#
# Copyright (c) 2008, Jos Kuijpers <jos@kuijpersvof.nl>
#
# This file is part of Jinix.
# Jinix is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Jinix is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with Jinix.  If not, see <http://www.gnu.org/licenses/>.
#

SOURCES=arch/x86/boot/boot.o \
	arch/x86/kernel/descriptor_tables.o \
	arch/x86/kernel/interrups.o \
	arch/x86/kernel/gdt.o \
	arch/x86/kernel/idt.o \
	arch/x86/kernel/tss.o \
	arch/x86/kernel/irq.o \
	arch/x86/kernel/isr.o \
	kernel/main.o \
	drivers/vga.o \
	lib/system/in.o \
	lib/system/out.o \
	lib/system/panic.o \
	lib/string/memcpy.o \
	lib/string/memset.o \
	lib/string/memsetw.o \
	lib/string/strlen.o

CFLAGS=-nostdlib -nostdinc -I ./include -I ./lib/include -fno-builtin -fno-stack-protector
LDFLAGS=-Tlink.ld
ASFLAGS=-felf

include ./.config

all: 	
	@echo "Building kernel"
	@make -s alld
	@make -s image
	@echo "Cleaning..."
	@echo "Objects"
	@rm $(SOURCES)
	@echo "Done" 
	@echo "OS has been built!"

alld:	$(SOURCES) link

link:
	@echo "[LD] link.ld"
	ld $(LDFLAGS) -o jinix $(SOURCES)

image:
	@echo "Building floppy image..."
	@sudo losetup /dev/loop0 floppy.img
	@sudo mount /dev/loop0 /mnt
	
	@sudo cp jinix /mnt/kernel
	
	@sudo cp boot/grub/menu.lst /mnt/boot/grub/menu.lst
	
	@sudo umount /dev/loop0
	@sudo losetup -d /dev/loop0
	@echo "Done"

run:
	@echo "Running kernel..."
	@qemu -fda ./floppy.img -boot a -m 32 -std-vga -localtime
	@echo "Done"

.s.o:
	@echo "[NASM] $@"
	nasm $(ASFLAGS) $<
.c.o:
	@echo "[CC] $@"
	gcc -c $(CFLAGS) -o $@ $<
.a.o:
	@echo "[AS] $@"
	as $(ASFLAGS) -o $<