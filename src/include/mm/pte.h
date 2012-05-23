/*
 *  Andromeda
 *  Copyright (C) 2011  Bart Kuivenhoven
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * \defgroup PTE
 * @{
 */

#ifndef __MM_PTE_H
#define __MM_PTE_H

#include <mm/paging.h>

#ifdef __cplusplus
extern "C" {
#endif

struct pte_shadow;
extern struct pte_shadow* pte_core;

/**
 * \struct pte
 * \brief Page table entry
 * \todo Move this structure out into arch/x86
 */
struct pte {
        /**
         * \var page_table
         * \brief The page table entries
         */
        struct page_table table[0x400];
};

/**
 * \struct pte_shadow
 * \brief The shadow discriptor of the page table
 */
struct pte_shadow {
        /**
         * \var pte
         * \brief The virtual reference to the page table
         * \var children
         * \brief The virtual descriptor of the children
         * \var state
         * \brief An integer indicating the condition the page table entry has
         */
        struct pte* pte;
        struct pte_shadow* children[1024];
        int state;
};

/**
 * \fn pte_init
 * \brief Setup the first pte administration
 * \param kern_boundary
 * \brief Where does the kernel start?
 * \todo Write pte_init
 *
 * \fn pte_switch
 * \brief Switch to pte mode
 * \todo write pte_switch
 *
 * \fn pte_map
 * \brief Map a virtual page to a physical one
 * \param phys
 * \param virt
 * \param pte
 * \todo Write pte_map
 *
 * \fn pte_unmap
 * \brief Unmap a particular page
 * \param phys
 * \param pte
 */
int pte_init(void* kern_boundary);
int pte_switch();
int pte_map(void* virt, void* phys, struct pte_shadow* pte);
int pte_unmap(void* virt, struct pte_shadow* pte);

#ifdef __cplusplus
};
#endif

#endif

/** @} \file  */