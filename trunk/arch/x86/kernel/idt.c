/*
 * Copyright (c) 2008, Jos Kuijpers <jos@kuijpersvof.nl>
 *
 * This file is part of Jinix.
 * Jinix is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Jinix is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Jinix.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdint.h>
#include <interrupts.h>
#include <system.h>

extern idtFlush(uint32_t);
idtEntryT idtEntries[256]; // array of IDT's
idtPtrT idtPtr; // pointer to an idt

int idtInit() // initialize the IDT
{
	idtPtr.limit = sizeof(idtEntryT) * 256 - 1; // the limit is the length of the entryarray - 1
	idtPtr.base = (uint32_t)&idtEntries;

	memset(&idtEntries, 0, sizeof(idtEntryT) * 256); // be sure the array is empty

	// remap the IRQ table
	outb(0x20, 0x11); // send ICW1 to both PIC's
	outb(0xA0, 0x11);
	outb(0x21, 0x20); // send ICW2 to both PIC's
	outb(0xA1, 0x28);
	outb(0x21, 0x04); // send ICW3 to both PIC's
	outb(0xA1, 0x02);
	outb(0x21, 0x01); // send ICW4 to both PIC's
	outb(0xA1, 0x01);
	outb(0x21, 0x0); // enable all interrupts
	outb(0xA1, 0x0);

	idtSetGate(0,(uint32_t)isr0,0x08,0x8E);
	idtSetGate(1,(uint32_t)isr1,0x08,0x8E);
	idtSetGate(2,(uint32_t)isr2,0x08,0x8E);
	idtSetGate(3,(uint32_t)isr3,0x08,0x8E);
	idtSetGate(4,(uint32_t)isr4,0x08,0x8E);
	idtSetGate(5,(uint32_t)isr5,0x08,0x8E);
	idtSetGate(6,(uint32_t)isr6,0x08,0x8E);
	idtSetGate(7,(uint32_t)isr7,0x08,0x8E);
	idtSetGate(8,(uint32_t)isr8,0x08,0x8E);
	idtSetGate(9,(uint32_t)isr9,0x08,0x8E);
	idtSetGate(10,(uint32_t)isr10,0x08,0x8E);
	idtSetGate(11,(uint32_t)isr11,0x08,0x8E);
	idtSetGate(12,(uint32_t)isr12,0x08,0x8E);
	idtSetGate(13,(uint32_t)isr13,0x08,0x8E);
	idtSetGate(14,(uint32_t)isr14,0x08,0x8E);
	idtSetGate(15,(uint32_t)isr15,0x08,0x8E);
	idtSetGate(16,(uint32_t)isr16,0x08,0x8E);
	idtSetGate(17,(uint32_t)isr17,0x08,0x8E);
	idtSetGate(18,(uint32_t)isr18,0x08,0x8E);
	idtSetGate(19,(uint32_t)isr19,0x08,0x8E);
	idtSetGate(20,(uint32_t)isr20,0x08,0x8E);
	idtSetGate(21,(uint32_t)isr21,0x08,0x8E);
	idtSetGate(22,(uint32_t)isr22,0x08,0x8E);
	idtSetGate(23,(uint32_t)isr23,0x08,0x8E);
	idtSetGate(24,(uint32_t)isr24,0x08,0x8E);
	idtSetGate(25,(uint32_t)isr25,0x08,0x8E);
	idtSetGate(26,(uint32_t)isr26,0x08,0x8E);
	idtSetGate(27,(uint32_t)isr27,0x08,0x8E);
	idtSetGate(28,(uint32_t)isr28,0x08,0x8E);
	idtSetGate(29,(uint32_t)isr29,0x08,0x8E);
	idtSetGate(30,(uint32_t)isr30,0x08,0x8E);
	idtSetGate(31,(uint32_t)isr31,0x08,0x8E);

	idtSetGate(32,(uint32_t)irq0,0x08,0x8E);
	idtSetGate(33,(uint32_t)irq1,0x08,0x8E);
	idtSetGate(34,(uint32_t)irq2,0x08,0x8E);
	idtSetGate(35,(uint32_t)irq3,0x08,0x8E);
	idtSetGate(36,(uint32_t)irq4,0x08,0x8E);
	idtSetGate(37,(uint32_t)irq5,0x08,0x8E);
	idtSetGate(38,(uint32_t)irq6,0x08,0x8E);
	idtSetGate(39,(uint32_t)irq7,0x08,0x8E);
	idtSetGate(40,(uint32_t)irq8,0x08,0x8E);
	idtSetGate(41,(uint32_t)irq9,0x08,0x8E);
	idtSetGate(42,(uint32_t)irq10,0x08,0x8E);
	idtSetGate(43,(uint32_t)irq11,0x08,0x8E);
	idtSetGate(44,(uint32_t)irq12,0x08,0x8E);
	idtSetGate(45,(uint32_t)irq13,0x08,0x8E);
	idtSetGate(46,(uint32_t)irq14,0x08,0x8E);
	idtSetGate(47,(uint32_t)irq15,0x08,0x8E);

	idtFlush((uint32_t)&idtPtr);

	memset(&interruptHandlers, 0, sizeof(isrT)*256);
}

int idtSetGate(uint8_t num, uint32_t base, uint16_t selector, uint8_t flags) //set the value of one IDT entry
{
	idtEntries[num].baseLow		= base & 0xFFFF;
	idtEntries[num].baseHigh	= (base >> 16) & 0xFFFF;

	idtEntries[num].selector	= selector;	// selector
	idtEntries[num].always0		= 0;		// always 0 (d^h)

	idtEntries[num].flags		= flags; 	// if usermode: | 0x60
}
