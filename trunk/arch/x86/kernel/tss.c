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

extern void tssFlush();
tssEntryT tssEntry;

void tssWrite(int32_t num,uint16_t ss0,uint32_t esp0) // write a TSS
{
	// firstly, create base and limit address
	uint32_t base = (uint32_t) &tssEntry;
	uint32_t limit = base + sizeof(tssEntry);

	// add out TSS to our GDT
	gdtSetGate(num, base, limit, 0xE9, 0x00);

	// ensure the descriptor is zero
	memset(&tssEntry, 0, sizeof(tssEntry));

	tssEntry.ss0 = ss0;	// set the kernel stack segment
	tssEntry.esp0 = esp0;	// set the kernel stack pointer

	tssEntry.cs = 0x0b;
	tssEntry.ss = tssEntry.ds = tssEntry.es = tssEntry.fs = tssEntry.gs = 0x13;
}

void setKernelStack(uint32_t stack)
{
	tssEntry.esp0 = stack;
}
