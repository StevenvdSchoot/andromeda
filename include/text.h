/*
    Orion OS, The educational operatingsystem
    Copyright (C) 2011  Bart Kuivenhoven

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdlib.h>

#ifndef __TEXT_H
#define __TEXT_H

#include <types.h>

#ifdef __cplusplus
extern "C" {
#endif

void println(const char*);
void printf(const char*, ...);
void putc(const uint8_t);
void puts(const char*);
//void printNum(int index, unsigned int base, boolean sInt, boolean capital);
#define printnum(a,b,c,d) printNum(a,b,c,d)
//void printDecimalNum(double index, unsigned int base);
void scroll(unsigned char);
void textInit();
int atoi(char* str);

#ifdef MSG_DBG
#define debug(...) printf(__VA_ARGS__)
#else
#define debug(...)
#endif

#ifdef WARN
#define warning(a) printf("WARNING! " a)
#else
#define warning(a)
#endif

#ifdef __cplusplus
}
#endif

#endif

/** \file */
