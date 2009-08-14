/*
 * Copyright (c) 2009 by Stefan Siegl <stesie@brokenpipe.de>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * For more information on the GPL, please go to:
 * http://www.gnu.org/copyleft/gpl.html
 */

#ifndef VFS_MCA25_H
#define VFS_MCA25_H

#include <stdlib.h>

typedef struct {
} vfs_file_handle_mca25_t;

/* vfs_mca25_ Prototypes. */
struct vfs_file_handle_t *vfs_mca25_open (const char *filename);
void vfs_mca25_close (struct vfs_file_handle_t *);
vfs_size_t vfs_mca25_read  (struct vfs_file_handle_t *, void *buf,
			 vfs_size_t length);
vfs_size_t vfs_mca25_size (struct vfs_file_handle_t *);


#define VFS_MCA25_FUNCS {		\
    "mca25",				\
    vfs_mca25_open,			\
    vfs_mca25_close,			\
    vfs_mca25_read,			\
    NULL, /* write */			\
    NULL, /* fseek */			\
    NULL, /* truncate */		\
    NULL, /* create */			\
    NULL, /* size */			\
    90,	  /* blocksize */		\
  }

#endif	/* VFS_MCA25_H */
