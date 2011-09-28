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

#ifndef __FS_FS_H
#define __FS_FS_H

#include <fs/file.h>
#include <thread.h>

#define _FS_PROT_DIR   0x200
#define _FS_PROT_OWN_R 0x100
#define _FS_PROT_OWN_W 0x080
#define _FS_PROT_OWN_X 0x040
#define _FS_PROT_GRP_R 0x020
#define _FS_PROT_GRP_W 0x010
#define _FS_PROT_GRP_X 0x008
#define _FS_PROT_ALL_R 0x004
#define _FS_PROT_ALL_W 0x002
#define _FS_PROT_ALL_X 0x001

#define _FS_META_DIR  0x000
#define _FS_META_BLK  0x001
#define _FS_META_BIN  0x002
#define _FS_META_SYM  0x003
#define _FS_META_MNT  0x004
#define _FS_META_ROOT 0x004
#define _FS_META_LNK  0x005

#define _FS_USER_ROOT  0
#define _FS_GROUP_ROOT 0

#define _FS_MAX_DRIVES 0x20

#define _FS_ROOT_RIGHTS (_FS_PROT_OWN_R|_FS_PROT_OWN_W|_FS_PROT_OWN_X|_FS_PROT_GRP_R|_FS_PROT_GRP_X|_FS_PROT_ALL_R|_FS_PROT_ALL_X)
#define _FS_ROOT_INODE 0x2

#define _VFS_STD_BLCK 0x200
#define _VFS_STD_SIZE (0x100000/_VFS_STD_BLCK)

struct _FS_INODE
{
  unsigned short prot;       // protection bits d-rwx-rwx-rwx
  unsigned int usrid;        // Owner data
  unsigned int grpid;        // Owner data
  unsigned int meta;         // Any flags required for administration
  unsigned int drv;	     // Drive id
  unsigned int inode;        // Address of inode on disk
  size_t size;               // The size of the file
  struct _FS_FILE* data;     // Where is the data in memory
  mutex_t lock;              // If there are operations to be done on the file, the file must be locked, untill the operations are complete
};

#define _FS_MNT_ERR  0x000
#define _FS_MNT_EXT  0x001
#define _FS_MNT_EXT2 0x002
#define _FS_MNT_EXT3 0x003
#define _FS_MNT_EXT4 0x004
#define _FS_MNT_FT12 0x005
#define _FS_MNT_FT16 0x006
#define _FS_MNT_FT32 0x007
#define _FS_MNT_NTFS 0x008
#define _FS_MNT_REIS 0x009
#define _FS_MNT_UFS  0x00A
#define _FS_MNT_AFS  0x00B
#define _FS_MNT_NFS  0x00C

typedef struct _FS_INODE inode_t;

extern struct _FS_INODE* _fs_root;

void fsInit(inode_t* root);
struct _FS_INODE* vfsInit(size_t size, unsigned int protection);
void list(inode_t *dir);

#define SEEK_SET 0
#define SEEK_RD  1
#define SEEK_WRT 2
#define SEEK_END 3

#endif