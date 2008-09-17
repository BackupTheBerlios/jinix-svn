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

[GLOBAL gdtFlush]

gdtFlush:
	mov eax, [esp+4]	; get pointer to GDT
	lgdt [eax]		; load the GDT pointer

	jmp 0x08:.flush		; jump to flush
.flush:
	mov ax, 0x10		; 0x10 us the offset in the GDT to our data segment
	mov ds, ax		; load all data segment selectors
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	ret

[GLOBAL idtFlush]

idtFlush:
	mov eax, [esp+4]	; get pointer to IDT
	lidt [eax]		; load the IDT pointer
	ret			; return

[GLOBAL tssFlush]

tssFlush:
	mov ax, 0x2B		; loads the index of our TSS structure
				; the index is 0x28, as it is the 5th selector and each 8 bytes
				; long, but we set the bottom two buts (making 0x2B)
	ltr ax			; load 0x2B into the task state register
	ret			; return
