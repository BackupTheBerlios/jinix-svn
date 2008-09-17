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

void irqHandler(registersT regs) // handle IRQ
{
	if(regs.intNo >= 40) // if interrupt involved the slave, send EOI
	{
		outb(0xA0, 0x20); // send reset signal to slave
	}

	outb(0x20,0x20); // send reset signal to master

	if(interruptHandlers[regs.intNo] != 0) // if there is an handler installed
	{
		isrT handler = interruptHandlers[regs.intNo]; // create callable handler
		handler(regs); // call the handler
	}
}
