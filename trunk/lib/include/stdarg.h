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

#ifndef __STDARG_H
#define __STDARG_H

#define va_start(v,l)	__builtin_va_start(v,l)
#define va_arg(v,l)	__builtin_va_arg(v,l)
#define va_end(v)	__builtin_va_end(v)
#define va_copy(d,s)	__builtin_va_copy(d,s)
typedef __builtin_va_list va_list;

#endif
