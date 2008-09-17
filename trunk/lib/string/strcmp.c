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

#include <string.h>
#include <stdint.h>

int strcmp(const char *p1, const char *p2) // compare p1 with p2
{
	register const uint8_t *s1 = (const uint8_t *) p1; // declares
	register const uint8_t *s2 = (const uint8_t *) p2;
	uint8_t c1, c2;

	do // loop while
	{
		c1 = (uint8_t) *s1++; // set c1 to the current char of p1
		c2 = (uint8_t) *s2++; // set c2 to the current char of p2
		if(c1 == '\0')
			return c1-c2;
	}
	while(c1 == c2); // while c1 is equeal to c2

	return c1 - c2; // return value
}
