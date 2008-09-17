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

isrT interruptHandlers[256];

uint8_t *isrExceptionMessages[] =
{
	"Division By Zero",
	"Debug",
	"Non Maskable Interrupt",
	"Breakpoint",
	"Into Detected Overflow",
	"Out of Bounds",
	"Invalid Opcode",
	"No Coprocessor",

	"Double Fault",
	"Coprocessor Segment Overrun",
	"Bad TSS",
	"Segment Not Present",
	"Stack Fault",
	"General Protection Fault",
	"Page Fault",
	"Intel Reserved",

	"Coprocessor Fault",
	"Alignment Check",
	"Machine Check",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",

	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved"
};

void isrHandler(registersT regs) // handle ISR
{
	
	if(interruptHandlers[regs.intNo] != 0) // if there is an handler installed
	{
		isrT handler = interruptHandlers[regs.intNo]; // create callable handler
		handler(regs); // call the handler
	}
	else
	{
		//printk("%s. Unhandled Interrupt. System Halted.\n",isrExceptionMessages[regs.intNo]);
		vgaPutString(isrExceptionMessages[regs.intNo]); // write down the exception
		vgaPutString(". Unhandled Interrupt. System Halted.\n"); // ...
		for(;;); // forever loop. What will happen if interrups are not halted? :P
	}
}

void registerInterruptHandler(uint8_t num, isrT handler) // rgeister the handler handler to interrupt num
{
	interruptHandlers[num] = handler;
}
