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

char *strcpy(int8_t *dest, const int8_t *src) // copy string to another
{
	const int8_t *p;
	int8_t *q;

	for(p = src, q = dest; *p != '\0'; p++, q++)
		*q = *p;
	*q = '\0';
	return dest;
}
