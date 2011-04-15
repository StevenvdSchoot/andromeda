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

#ifdef MMTEST
#include <mm/heap.h>

struct small
{
  int a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p;
};
struct large
{
  int a[1024];
};

typedef struct small small_t;
typedef struct large large_t;

void wait()
{
  int i;
  for (i = 0; i < 0x1FFFFFFF; i++)
  {
  }
}

void testAlloc()
{
  large_t* a = alloc(sizeof(large_t), FALSE);
  large_t* b = alloc(sizeof(large_t), TRUE);
  
  small_t* c = alloc(sizeof(small_t), FALSE);
  small_t* d = alloc(sizeof(small_t), TRUE);
  
  examineHeap();
  wait();
  
  free(a);
  free(c);
  
  examineHeap();
  wait();
  
  a = alloc(sizeof(large_t), TRUE);
  c = alloc(sizeof(small_t), TRUE);
  
  examineHeap();
  wait();
  
  free(a);
  free(b);
  free(c);
  free(d);
  
  examineHeap();
  wait();
}

#endif