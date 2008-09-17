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

void *memcpy(void *dest, const void *src, int32_t count) // copy memory
{
	const int8_t *sp = (const int8_t *)src; // source position
	int8_t *dp = (int8_t *)dest; // destination position
	for(; count != 0; count--) // for count is not null
		*dp++ = *sp++; // copy
	return dest; // return destination
}
