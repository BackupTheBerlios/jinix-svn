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
#include <system.h>
#include <vga.h>

void panic(uint8_t* message) // panic!
{
#ifndef DEBUG // if debugging, do not clear screen
	vgaSetColor(0, 4); // set standard colors to Blue/white
	vgaClearScreen(); // clear the screen
	vgaPutString("\n\n\n\t");
#endif
	vgaPutString(message); // write the message to the screen
	cli(); // stop interupts
	for(;;); // loop forever
}
