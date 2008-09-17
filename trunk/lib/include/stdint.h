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

#ifndef __STDINT_H
#define __STDINT_H

// signed
typedef signed char	int8_t;
typedef short int	int16_t;
typedef int		int32_t;

#ifdef __x86_64__
	typedef long int	int64_t;
#else
	typedef long long int	int64_t;
#endif

// unsigned
typedef unsigned char		uint8_t;
typedef unsigned short int	uint16_t;
typedef unsigned int		uint32_t;

#ifdef __x86_64__
	typedef unsigned long int	uint64_t;
#else
	typedef unsigned long long int	uint64_t;
#endif

// least types
// signed
typedef signed char	int_least8_t;
typedef short int	int_least16_t;
typedef int		int_least32_t;

#ifdef __x86_64__
	typedef long int	int_least64_t;
#else
	typedef long long int	int_least64_t;
#endif

// unsigned
typedef unsigned char		uint_least8_t;
typedef unsigned short int	uint_least16_t;
typedef unsigned int		uint_least32_t;

#ifdef __x86_64__
	typedef unsigned long int	uint_least64_t;
#else
	typedef unsigned long long int	uint_least64_t;
#endif

// fast types
// signed
typedef signed char	int_fast8_t;
#ifdef __x86_64__
	typedef long int	int_fast16_t;
	typedef long int	int_fast32_t;
	typedef long int	int_fast64_t;
#else
	typedef int		int_fast16_t;
	typedef int		int_fast32_t;
	typedef long long int	int_fast64_t;
#endif

// unsigned
typedef unsigned char		uint_fast8_t;
#ifdef __x86_64__
	typedef unsigned long int	uint_fast16_t;
	typedef unsigned long int	uint_fast32_t;
	typedef unsigned long int	uint_fast64_t;
#else
	typedef unsigned int		uint_fast16_t;
	typedef unsigned int		uint_fast32_t;
	typedef unsigned long long int	uint_fast64_t;
#endif

// tpes for void pointers
#ifdef __x86_64__
	typedef long int		intptr_t;
	typedef unsigned long int	uintptr_t;
#else
	typedef int			intptr_t;
	typedef unsigned long long int	uintptr_t;
#endif

// greates width integer types
#ifdef __x86_64__
	typedef long int		intmax_t;
	typedef unsigned long int	uintmax_t;
#else
	typedef long long int		intmax_t;
	typedef unsigned long long int	uintmax_t;
#endif

#endif
