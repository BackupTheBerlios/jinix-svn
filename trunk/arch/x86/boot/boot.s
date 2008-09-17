;
; Copyright (c) 2008, Jos Kuijpers <jos@kuijpersvof.nl>
;
; This file is part of Jinix.
; Jinix is free software: you can redistribute it and/or modify
; it under the terms of the GNU General Public License as published by
; the Free Software Foundation, either version 3 of the License, or
; (at your option) any later version.
;
; Jinix is distributed in the hope that it will be useful,
; but WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
; GNU General Public License for more details.
;
; You should have received a copy of the GNU General Public License
; along with Jinix.  If not, see <http://www.gnu.org/licenses/>.
;

MBOOT_PAGE_ALIGN		equ 1		; page aligning
MBOOT_MEM_INFO			equ 1<<1	; memory info
MBOOT_HEADER_MAGIC		equ 0x1BADB002	; magic number
MBOOT_HEADER_FLAGS		equ MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO
MBOOT_CHECKSUM			equ -(MBOOT_HEADER_MAGIC + MBOOT_HEADER_FLAGS)

SECTION .text
[BITS 32] 				; commands should run in 32 bit mode

[GLOBAL mBootHeader]
[GLOBAL start]
[EXTERN code] 				; address of text
[EXTERN bss] 				; address of bss and end of text
[EXTERN end] 				; end of last laodble section
[EXTERN kernel] 			; main C kernel function

mBootHeader:
	dd MBOOT_HEADER_MAGIC
	dd MBOOT_HEADER_FLAGS		; how grub should load your file/settings
	dd MBOOT_CHECKSUM		; check the other values

	dd mBootHeader
	dd code
	dd bss
	dd end
	dd start

STACKSIZE equ 0x4000 			;stacksize of 16kb

start:					; this is called as very first
	cli				; disable interrups
	xor ebp, ebp
	mov esp, stack+STACKSIZE	; set up the stack by moving new address to esp

	push eax 			; pass multiboot magic number <<<<<<<< TODO >>>>>>>> better?
	push ebx 			; pass multiboot info structure <<<<<<<< TODO >>>>>>>> better?

	call kernel			; call the kernel main C function
	jmp $				; jump in a never-ending loop <<<<<<<< TODO >>>>>>>> better?

SECTION .bss
stack:
	resb STACKSIZE
