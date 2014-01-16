/*
 *  Andromeda
 *  Copyright (C) 2011  Michel Megens - dev@michelmegens.net
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

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#ifdef __cplusplus
extern "C" {
#endif

struct list_node;

struct list{
        struct list_node* head;
        size_t size;
        mutex_t lock;
};

struct list_node {
        struct list_node* head;
        struct list_node* next;
        void* data;
};

#ifdef __cplusplus
}
#endif

#endif // LINKEDLIST_H