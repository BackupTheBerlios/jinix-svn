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

void *memset(void *dest, int8_t val, int32_t count) // set a avlue count times to dest
{
	int8_t *dp = (int8_t *)dest; // destination position
	for(; count != 0; count--) // for count is not nu
		*dp++ = val; // set the value to the destination
	return dest; // return destination
}
