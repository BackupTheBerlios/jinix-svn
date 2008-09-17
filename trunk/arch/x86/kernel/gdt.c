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

extern void gdtFlush(uint32_t); // setup in descriptor_tables.s
gdtEntryT 	gdtEntries[6]; // make place for 6 gdt entry's
gdtPtrT		gdtPtr;

int gdtInit() // initialize the GDT
{
	gdtPtr.limit = (sizeof(gdtEntryT) * 6) -1; // limit is the size of the entry array -1
	gdtPtr.base = (uint32_t)&gdtEntries; // base is address of gdtEntrys

	gdtSetGate(0,0,0,0,0);				// Null
	gdtSetGate(1,0,0xFFFFFFFF, 0x9A, 0xCF);		// Code
	gdtSetGate(2,0,0xFFFFFFFF, 0x92, 0xCF);		// Data
	gdtSetGate(3,0,0xFFFFFFFF, 0xFA, 0xCF);		// User-mode Code
	gdtSetGate(4,0,0xFFFFFFFF, 0xF2, 0xCF);		// User-mode Data
	tssWrite(5,0x10,0x0);				// TSS

	gdtFlush((uint32_t)&gdtPtr);
	tssFlush();

	return 0; //return
}

int gdtSetGate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity) // set the value of one GDT entry
{
	gdtEntries[num].baseLow		= (base & 0xFFFF);
	gdtEntries[num].baseMiddle	= (base >> 16) & 0xFF;
	gdtEntries[num].baseHigh	= (base >> 24) & 0xFF;

	gdtEntries[num].limitLow	= (limit & 0xFFFF);
	gdtEntries[num].granularity	= (limit >> 16) & 0x0F;

	gdtEntries[num].granularity    |= granularity & 0xF0;
	gdtEntries[num].access		= access;

	return 0; // return
}
