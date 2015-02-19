/* Matsushita AM33/2.0 support for 32-bit GNU/Linux CGC
   Copyright 2003, 2005, 2007
   Free Software Foundation, Inc.

   This file is part of BFD, the Binary File Descriptor library.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston,
   MA 02110-1301, USA.  */

#include "sysdep.h"
#include "bfd.h"
#include "cgc-bfd.h"
#include "cgc/mn10300.h"

#define cgc_symbol_leading_char 0

#define TARGET_LITTLE_SYM	bfd_cgc32_am33lin_vec
#define TARGET_LITTLE_NAME	"cgc32-am33lin"
#define CGC_ARCH		bfd_arch_mn10300
#define CGC_MACHINE_CODE	EM_MN10300
#define CGC_MACHINE_ALT1	EM_CYGNUS_MN10300
#define CGC_MAXPAGESIZE		0x1000

/* Rename global functions.  */
#define _bfd_mn10300_cgc_merge_private_bfd_data  _bfd_am33_cgc_merge_private_bfd_data
#define _bfd_mn10300_cgc_object_p                _bfd_am33_cgc_object_p
#define _bfd_mn10300_cgc_final_write_processing  _bfd_am33_cgc_final_write_processing

/* Support for core dump NOTE sections.  */
static bfd_boolean
cgc32_am33lin_grok_prstatus (bfd *abfd, Cgc_Internal_Note *note)
{
  int offset;
  unsigned int size;

  switch (note->descsz)
    {
      default:
	return FALSE;

      case 184:
      case 188:		/* Linux/am33 */
	/* pr_cursig */
	cgc_tdata (abfd)->core->signal = bfd_get_16 (abfd, note->descdata + 12);

	/* pr_pid */
	cgc_tdata (abfd)->core->lwpid = bfd_get_32 (abfd, note->descdata + 24);

	/* pr_reg */
	offset = 72;
	size = 112;

	break;
    }

  /* Make a ".reg/999" section.  */
  return _bfd_cgccore_make_pseudosection (abfd, ".reg", size,
					  note->descpos + offset);
}

static bfd_boolean
cgc32_am33lin_grok_psinfo (bfd *abfd, Cgc_Internal_Note *note)
{
  switch (note->descsz)
    {
      default:
	return FALSE;

      case 124:		/* Linux/am33 cgc_prpsinfo */
	cgc_tdata (abfd)->core->program
	 = _bfd_cgccore_strndup (abfd, note->descdata + 28, 16);
	cgc_tdata (abfd)->core->command
	 = _bfd_cgccore_strndup (abfd, note->descdata + 44, 80);
    }

  /* Note that for some reason, a spurious space is tacked
     onto the end of the args in some (at least one anyway)
     implementations, so strip it off if it exists.  */

  {
    char *command = cgc_tdata (abfd)->core->command;
    int n = strlen (command);

    if (0 < n && command[n - 1] == ' ')
      command[n - 1] = '\0';
  }

  return TRUE;
}

#define cgc_backend_grok_prstatus	cgc32_am33lin_grok_prstatus
#define cgc_backend_grok_psinfo		cgc32_am33lin_grok_psinfo

#include "cgc-m10300.c"
