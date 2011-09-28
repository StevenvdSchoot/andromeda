/*
 *   Andromeda Kernel - I/O APIC interface
 *   Copyright (C) 2011  Michel Megens
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#ifndef IOAPIC_H
#define	IOAPIC_H

#ifdef	__cplusplus
extern "C"
{
#endif

    typedef uint32_t ioapic_addr_t;
    typedef struct ioapic
    {
        uint8_t id;
        uint8_t apic_id:4;
        uint32_t int_base /* system interrupt base */, num_intr;
        volatile ioapic_addr_t* address;
        void (*write)(const ioapic_addr_t*, const uint8_t, const uint32_t);
        uint32_t (*read)(const ioapic_addr_t*, const uin8_t);
    } *ioapic_t;

static int
create_ioapic(ol_madt_ioapic_t);

int
init_ioapic();
#ifdef	__cplusplus
}
#endif

#endif	/* IOAPIC_H */
