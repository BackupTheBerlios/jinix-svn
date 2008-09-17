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

#ifndef __STRING_H
#define __STRING_H

#include <stdint.h>

void *memcpy(void *dest, const void *src, int32_t count); // copy memory
void *memset(void *dest, int8_t val, int32_t count); // set a avlue count times to dest
void *memsetw(uint16_t *dest, uint16_t val, int32_t count); // set a avlue count times to dest
void *memchr(const void *ptr, int64_t value, uint64_t num); // search a char in the num of bytes of string 
/** TODO */void *memmove(void* dest, const void *src, int32_t count); // move some memory

int32_t strlen(const int8_t *str); // take the length of a string
int strcmp(const char *p1, const char *p2); // compare p1 with p2
char *strcpy(int8_t *dest, const int8_t *src); // copy string to another

#endif
