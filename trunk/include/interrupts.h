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

#ifndef __INTERRUPTS_H
#define __INTERRUPTS_H

#include <stdint.h>

#define IRQ0 32 // PIT
#define IRQ1 33 // KBD
#define IRQ2 34 // EGA, VGA, NET
#define IRQ3 35 // COM2 if available
#define IRQ4 36 // COM1
#define IRQ5 37 // PC/XT HDD, PC/AT: LPT2 (if available, else nothing)
#define IRQ6 38 // FDD
#define IRQ7 39 // LPT1
#define IRQ8 40 // CMOS RTC
#define IRQ9 41
#define IRQ10 42
#define IRQ11 43
#define IRQ12 44 // PS/2: mouse
#define IRQ13 45 // Numeric Coprocessor
#define IRQ14 46 // HDD
#define IRQ15 47

struct gdtEntryS // a struct for the entries of gdt
{
	uint16_t limitLow; // LOW of limit
	uint16_t baseLow; // LOW of base
	uint8_t baseMiddle; // MIDDEL of base
	uint8_t access; // user? kernel?
	uint8_t granularity;
	uint8_t baseHigh; // HIGH of base
} __attribute__((packed)); // packed
typedef struct gdtEntryS gdtEntryT; // typedef....

struct gdtPtrS // a struct for the gdt pointer
{
	uint16_t limit;
	uint32_t base;
} __attribute__((packed)); // packed
typedef struct gdtPtrS gdtPtrT; // typedef

struct idtEntryS // a struct for the entries of IDT
{
	uint16_t baseLow;	// Lower 16  bits of the address to jump to
	uint16_t selector;	// kernel segment selector
	uint8_t always0;	// always be zzero
	uint8_t flags;		// Flags
	uint16_t baseHigh;	// High 16 of the address to jump to
} __attribute__((packed));	// packed
typedef struct idtEntryS idtEntryT; // typedef

struct idtPtrS // a struct for pointer to IDT
{
	uint16_t limit;
	uint32_t base;
} __attribute__((packed)); // pakced
typedef struct idtPtrS idtPtrT;

struct registersStruct
{
	uint32_t ds;			// data segment selecor
	uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; // pushed by pusha
	uint32_t intNo, errCode; 	// interrupt number and error code
	uint32_t eip, cs, eflags, useresp, ss; // psuhed by processor
};
typedef struct registersStruct registersT;

struct tssEntryS
{
	uint32_t prevTss; 	// the previous TSS
	uint32_t esp0;		// stack pointer to load when we change to kernel mode
	uint32_t ss0;		// stack segment to load when we change to kernel mode
	uint32_t esp1;		// unused...
	uint32_t ss1;
	uint32_t esp2;
	uint32_t ss2;
	uint32_t cr3;
	uint32_t eip;
	uint32_t eflags;
	uint32_t eax;
	uint32_t ecx;
	uint32_t edx;
	uint32_t ebx;
	uint32_t esi;
	uint32_t edi;
	uint32_t es;		// The values to load into the register when we change to kernel mode
	uint32_t cs;
	uint32_t ss;
	uint32_t ds;
	uint32_t fs;
	uint32_t gs;
	uint32_t ldt;		// Unused
	uint16_t trap;
	uint16_t iomapBase;

} __attribute__((packed));
typedef struct tssEntryS tssEntryT;

typedef void (*isrT)(registersT);

extern isrT interruptHandlers[];

int gdtSetGate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity); // set the value of one GDT entry
int idtSetGate(uint8_t num, uint32_t base, uint16_t selector, uint8_t flags); //set the value of one IDT entry
int gdtInit(); // initialize the GDT
int idtInit(); // initialize the IDT
void tssWrite(int32_t,uint16_t,uint32_t); // write a TSS
void isrHandler(registersT regs); // handle ISR
void irqHandler(registersT regs); // handle IRQ
void setKernelStack(uint32_t stack);

void registerInterruptHandler(uint8_t num, isrT handler); // register the handler handler to interrupt num

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

#endif
