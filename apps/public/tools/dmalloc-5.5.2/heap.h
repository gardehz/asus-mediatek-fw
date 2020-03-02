/*
 * defines for the system specific memory routines
 *
 * Copyright 2000 by Gray Watson
 *
 * This file is part of the dmalloc package.
 *
 * Permission to use, copy, modify, and distribute this software for
 * any purpose and without fee is hereby granted, provided that the
 * above copyright notice and this permission notice appear in all
 * copies, and that the name of Gray Watson not be used in advertising
 * or publicity pertaining to distribution of the document or software
 * without specific, written prior permission.
 *
 * Gray Watson makes no representations about the suitability of the
 * software described herein for any purpose.  It is provided "as is"
 * without express or implied warranty.
 *
 * The author may be contacted via http://dmalloc.com/
 *
 * $Id: //BBN_Linux/Branch/Branch_for_SDK_Release_MultiChip_20111013/tclinux_phoenix/apps/public/tools/dmalloc-5.5.2/heap.h#1 $
 */

#ifndef __HEAP_H__
#define __HEAP_H__

#include "dmalloc_loc.h"			/* for LOCAL and BLOCK_SIZE */

/*
 * error code returned by heap allocation routine
 */
#define HEAP_ALLOC_ERROR	0L

/* test whether pointer PNT is in the heap space */
#define IS_IN_HEAP(pnt)		\
  ((char *)(pnt) >= (char *)_dmalloc_heap_low \
   && (char *)(pnt) < (char *)_dmalloc_heap_high)

/*<<<<<<<<<<  The below prototypes are auto-generated by fillproto */

extern
void		*_dmalloc_heap_low;	/* base of our heap */

extern
void		*_dmalloc_heap_high;	/* end of our heap */

/*
 * int _heap_startup
 *
 * DESCRIPTION:
 *
 * Initialize heap pointers.
 *
 * RETURNS:
 *
 * Success - 1
 *
 * Failure - 0
 *
 * ARGUMENTS:
 *
 * None.
 */
extern
int	_dmalloc_heap_startup(void);

/*
 * void *_dmalloc_heap_alloc
 *
 * DESCRIPTION:
 *
 * Function to get memory bytes from the heap.
 *
 * RETURNS:
 *
 * Success - Valid pointer.
 *
 * Failure - NULL
 *
 * ARGUMENTS:
 *
 * size -> Number of bytes we need.
 */
extern
void	*_dmalloc_heap_alloc(const unsigned int size);

/*<<<<<<<<<<   This is end of the auto-generated output from fillproto. */

#endif /* ! __HEAP_H__ */
