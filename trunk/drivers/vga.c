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

#include <vga.h>
#include <stdint.h>

int32_t vgaCsrX = 0;
int32_t vgaCsrY = 0;
int32_t vgaScrnWidth = 80;
int32_t vgaScrnHeight = 25;
uint8_t vgaColorAttr = (0 << 4) | (15 & 0x0f);
uint16_t *vgaFbAddr;

int vgaInit() // initialize the vga
{
	vgaFbAddr = (uint16_t*)0xB8000; // set the vgabuffer to a pointer
	vgaClearScreen(); // clear the screen
	return 0; // return 0;
}

int vgaScroll() // scroll the text if needed
{
	uint16_t blank = 0x20 | (vgaColorAttr << 8);
	unsigned temp;

	if(vgaCsrY >= vgaScrnHeight) // is scrolling needed?
	{
		temp = vgaCsrY - vgaScrnHeight + 1; // temporary location
		memcpy(vgaFbAddr,vgaFbAddr + temp * vgaScrnWidth, (vgaScrnHeight - temp) * vgaScrnWidth * 2); // move everything one line up
		memsetw(vgaFbAddr + (vgaScrnHeight + temp) * vgaScrnWidth, blank, vgaScrnWidth); // clear the last line
		vgaCsrY = vgaScrnHeight -1; // set the y of the cursor to the height - 1
	}
	return 0; // return
}

int vgaSetCursor(int32_t x, int32_t y) // set the position of the cursor
{
	uint16_t where = (vgaCsrY * vgaScrnWidth) + vgaCsrX; // make the position
	outb(0x3D4,14);
	outb(0x3D5,where >> 8);
	outb(0x3D4,15);
	outb(0x3D5,where);
	return 0;
}

int vgaUpdateCursor() // update the cursor to the x and y of software cursor
{
	return vgaSetCursor(vgaCsrX,vgaCsrY); // return the result of setting cursor position to software cursor x and y
}

int vgaClearScreen() // clear the screen
{
	uint16_t blank = 0x20 | (vgaColorAttr << 8); // declare the blank char (a space with the standard fore and backcolor)
	int i;

	for(i = 0; i < vgaScrnHeight; i++) // for each line
		memsetw(vgaFbAddr + (i*vgaScrnWidth), blank, vgaScrnWidth); // fill it with spaces

	// set the cursor positions to zero
	vgaCsrX = vgaCsrY = 0;
	// update the hardware cursor
	vgaUpdateCursor();

	return 0; // return null
}

int vgaPutChar(char c) // put a char on the screen
{
	uint16_t *where;
	uint16_t attr = vgaColorAttr << 8;

	if(c == 0x08) // backspace
	{
		vgaCsrX--; // go back one char
		vgaPutChar(' '); // put a space
		vgaCsrX--; // go back one char
	}
	else if(c == 0x09) // tab
	{
		vgaCsrX+=5; // add 5 spaces
	}
	else if(c == '\r') // carriage return?
	{
		vgaCsrX = 0; // x to 0
	}
	else if(c == '\n') // linefeed?
	{
		vgaCsrX = 0; // x to 0
		vgaCsrY++; // a line down
	}
	else if(c >= ' ') // is it a space or bigger than a space?
	{
		where = vgaFbAddr + ((vgaCsrY * vgaScrnWidth) + vgaCsrX); // get the pointer to the place of cursor
		*where = c | attr; // add the char + color
		vgaCsrX++; // we have put a char, cursor x one up
	}
	
	if(vgaCsrX >= vgaScrnWidth) // is x bigger or equal to the screen width? down one line
	{
		vgaCsrX = vgaCsrX - vgaScrnWidth; // new x is remaing chars
		vgaCsrY++; // go down
	}
	else if(vgaCsrX < 0) // is x smaller than 0? y want down!
	{
		vgaCsrX = vgaScrnWidth + vgaCsrX; // width+-1 = width-1
		vgaCsrY--; // go up
	}
	
	//scroll and update the cursor
	vgaScroll();
	vgaUpdateCursor();
	return 0; // return null for sucess
}

int vgaSetColor(uint8_t foreColor, uint8_t backColor) // set the fore and background color
{
	vgaColorAttr = (backColor << 4) | (foreColor & 0x0f);
}

int vgaPutString(uint8_t* string)
{
	int i = 0;
	while(string[i])
	{
		vgaPutChar(string[i++]);	
	}
	return 0;
}
