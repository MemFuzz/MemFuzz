
/*---------------------------------------------------------------*/
/*--- begin                          guest_nanomips_helpers.c ---*/
/*---------------------------------------------------------------*/

/*
   This file is part of Valgrind, a dynamic binary instrumentation
   framework.

   Copyright (C) 2017-2018 RT-RK

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307, USA.

   The GNU General Public License is contained in the file COPYING.
*/

#include "libvex_basictypes.h"
#include "libvex_emnote.h"
#include "libvex_guest_mips32.h"
#include "libvex_ir.h"
#include "libvex.h"

#include "main_util.h"
#include "main_globals.h"
#include "guest_generic_bb_to_IR.h"
#include "guest_nanomips_defs.h"

#if defined (__GNUC__)
#define GCC_VERSION (__GNUC__ * 100 + __GNUC_MINOR__)
#else
#define GCC_VERSION 0
#endif

/* This file contains helper functions for mips guest code.  Calls to
   these functions are generated by the back end.
*/

#define ALWAYSDEFD32(field)                            \
    { offsetof(VexGuestMIPS32State, field),            \
      (sizeof ((VexGuestMIPS32State*)0)->field) }

VexGuestLayout nanomipsGuest_layout = {
   /* Total size of the guest state, in bytes. */
   .total_sizeB = sizeof(VexGuestMIPS32State),
   /* Describe the stack pointer. */
   .offset_SP = offsetof(VexGuestMIPS32State, guest_r29),
   .sizeof_SP = 4,
   /* Describe the frame pointer. */
   .offset_FP = offsetof(VexGuestMIPS32State, guest_r30),
   .sizeof_FP = 4,
   /* Describe the instruction pointer. */
   .offset_IP = offsetof(VexGuestMIPS32State, guest_PC),
   .sizeof_IP = 4,
   /* Describe any sections to be regarded by Memcheck as
      'always-defined'. */
   .n_alwaysDefd = 8,
   /* ? :(  */
   .alwaysDefd = {
      /* 0 */ ALWAYSDEFD32(guest_r0),
      /* 1 */ ALWAYSDEFD32(guest_r1),
      /* 2 */ ALWAYSDEFD32(guest_EMNOTE),
      /* 3 */ ALWAYSDEFD32(guest_CMSTART),
      /* 4 */ ALWAYSDEFD32(guest_CMLEN),
      /* 5 */ ALWAYSDEFD32(guest_r29),
      /* 6 */ ALWAYSDEFD32(guest_r31),
      /* 7 */ ALWAYSDEFD32(guest_ULR)
   }
};


#define ASM_VOLATILE_RDHWR(opcode)                                 \
   __asm__ __volatile__(".word 0x204001C0 | "#opcode" << 16  \n\t" \
                        : "+r" (x) : :                             \
                       )

HWord nanomips_dirtyhelper_rdhwr ( UInt rd )
{
#if defined(__nanomips__)
   register HWord x __asm__("t4") = 0;

   switch (rd) {
      case 0:  /* x = CPUNum() */
         ASM_VOLATILE_RDHWR(0); /* rdhwr t4, $0 */
         break;

      case 1:  /* x = SYNCI_Step() */
         ASM_VOLATILE_RDHWR(1); /* rdhwr t4, $1 */
         break;

      case 2:  /* x = CC() */
         ASM_VOLATILE_RDHWR(2); /* rdhwr t4, $2 */
         break;

      case 3:  /* x = CCRes() */
         ASM_VOLATILE_RDHWR(3); /* rdhwr t4, $3 */
         break;


      default:
         vassert(0);
         break;
   }

   return x;
#else
   return 0;
#endif
}


/*---------------------------------------------------------------*/
/*--- end                            guest_nanomips_helpers.c ---*/
/*---------------------------------------------------------------*/
