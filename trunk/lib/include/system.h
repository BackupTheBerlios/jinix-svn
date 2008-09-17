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

#ifndef __SYSTEM_H
#define __SYSTEM_H

#include <stdint.h>

uint8_t inb(uint16_t port); // inbyte
uint16_t inw(uint16_t port); // inword
uint32_t inl(uint16_t port); // inlong

void outb(uint16_t port, uint8_t value); // outbyte
void outw(uint16_t port, uint16_t value); // outword
void outl(uint16_t port, uint32_t value); // outlong

void panic(uint8_t* message); // panic!

#define cli() asm volatile("cli")
#define sti() asm volatile("sti")
#define nop() asm volatile("nop")
#define iret() asm volatile("iret")

#endif
