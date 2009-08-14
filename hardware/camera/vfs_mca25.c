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

#include <avr/pgmspace.h>

#include <stdlib.h>

#include "core/vfs/vfs.h"
#include "hardware/camera/mca25.h"

struct vfs_file_handle_t *
vfs_mca25_open (const char *filename)
{
  if (strcmp_P (filename, PSTR ("mca25")))
    return NULL;		/* We have only one file to serve :) */

  MCA25_DEBUG ("vfs_mca25_open: creating handle\n");
  struct vfs_file_handle_t *fh = malloc (sizeof (struct vfs_file_handle_t));
  if (fh == NULL)
    return NULL;

  fh->fh_type = VFS_MCA25;
  return fh;
}

void
vfs_mca25_close (struct vfs_file_handle_t *fh)
{
  free (fh);
}

vfs_size_t
vfs_mca25_read (struct vfs_file_handle_t *fh, void *buf, vfs_size_t length)
{
  MCA25_DEBUG ("vfs_mca25_read: %d bytes\n", length);

  if (length % 90) {
    debug_printf ("vfs_mca25_read: caller isn't considering our blocksize :-(\n");
    return 0;			/* can't help ya, go away! */
  }

  vfs_size_t readlen = 0;
  for (uint16_t l; length >= 90; length -= 90, buf += 90) {
    uint8_t r = mca25_copy_image_data_to_tcp_buffer(buf, &l);

    readlen += l;
    if (!r) break;		/* read last packet */
  }

  return readlen;
}
