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

[EXTERN isrHandler]
[EXTERN irqHandler]

%macro ISR_NOERRCODE 1
	[GLOBAL isr%1]
	isr%1:
		cli			; disable interrups
		push byte 0		; push a dummy error code
		push byte %1		; push the interrupt number
		jmp isrCommonStub	; handler
%endmacro

%macro ISR_ERRCODE 1
	[GLOBAL isr%1]
	isr%1:
		cli			; disable interrups
		push byte %1		; push the interrupt number
		jmp isrCommonStub	; handler
%endmacro

%macro IRQ 2
	[GLOBAL irq%1]
	irq%1:
		cli			; disable interrups
		push byte 0		; push dummy error code
		push byte %2		; push isr number
		jmp irqCommonStub	; handler
%endmacro


; our common ISR stub. it saves CPU state, sets up for kernel mode segments, calls C-level fault handler, final-> restores stack frame
isrCommonStub:
	pusha		; pushes edi, esi,ebp, esp, ebx, ecx, edx, eax
	mov ax, ds	; lower 16 bits of eax = ds
	push eax	; saves the datab segment descriptor

	mov ax, 0x10	; load the kernel data segment descriptor (DSD :P)
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	call isrHandler

	pop ebx		; relaod the original DSD
	mov ds, bx
	mov es, bx
	mov fs, bx
	mov gs, bx

	popa		;pops edi, esi, ebp......
	add esp, 8	; cleans up the pushed error code and pushed ISR number
	sti		; enable interrups
	iret		; pops 5 yhings at once, cs, eip, eflags, ss, and esp :)

; our common IRQ stub, same as out isr stub, only different is the call
irqCommonStub:
	pusha		; pushes edi, esi,ebp, esp, ebx, ecx, edx, eax
	mov ax, ds	; lower 16 bits of eax = ds
	push eax	; saves the datab segment descriptor

	mov ax, 0x10	; load the kernel data segment descriptor (DSD :P)
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	call irqHandler

	pop ebx		; relaod the original DSD
	mov ds, bx
	mov es, bx
	mov fs, bx
	mov gs, bx

	popa		;pops edi, esi, ebp......
	add esp, 8	; cleans up the pushed error code and pushed ISR number
	sti		; enable interrups
	iret		; pops 5 yhings at once, cs, eip, eflags, ss, and esp :)


ISR_NOERRCODE 0
ISR_NOERRCODE 1
ISR_NOERRCODE 2
ISR_NOERRCODE 3
ISR_NOERRCODE 4
ISR_NOERRCODE 5
ISR_NOERRCODE 6
ISR_NOERRCODE 7
ISR_ERRCODE 8
ISR_NOERRCODE 9
ISR_ERRCODE 10
ISR_ERRCODE 11
ISR_ERRCODE 12
ISR_ERRCODE 13
ISR_NOERRCODE 14
ISR_NOERRCODE 15
ISR_NOERRCODE 16
ISR_NOERRCODE 17
ISR_NOERRCODE 18
ISR_NOERRCODE 19
ISR_NOERRCODE 20
ISR_NOERRCODE 21
ISR_NOERRCODE 22
ISR_NOERRCODE 23
ISR_NOERRCODE 24
ISR_NOERRCODE 25
ISR_NOERRCODE 26
ISR_NOERRCODE 27
ISR_NOERRCODE 28
ISR_NOERRCODE 29
ISR_NOERRCODE 30
ISR_NOERRCODE 31
 
IRQ 0, 32
IRQ 1, 33
IRQ 2, 34
IRQ 3, 35
IRQ 4, 36
IRQ 5, 37
IRQ 6, 38
IRQ 7, 39
IRQ 8, 40
IRQ 9, 41
IRQ 10, 42
IRQ 11, 43
IRQ 12, 44
IRQ 13, 45
IRQ 14, 46
IRQ 15, 47

