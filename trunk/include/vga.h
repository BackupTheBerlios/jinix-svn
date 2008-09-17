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
#ifndef __VGA_H
#define __VGA_H

#include <stdint.h>

int vgaInit(); // initialize the screen
int vgaScroll(); // scroll the screen if needed
int vgaSetCursor(int32_t x, int32_t y); // set the cursor position
int vgaUpdateCursor(); // update the hardwarecursor to the x and y of the software cursor
int vgaClearScreen(); // clear the screen
int vgaPutChar(char c); // put a char on the screen
int vgaSetColor(uint8_t foreColor, uint8_t backColor); // set the fore and background color
int vgaPutString(uint8_t* string);

#endif
