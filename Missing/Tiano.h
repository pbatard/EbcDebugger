/*++

Copyright (c) 2016 - Pete Batard <pete@akeo.ie>

All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Abstract:

EDK definitions that have no match in gnu-efi yet.

--*/

#ifndef TIANO_H
#define TIANO_H

#include <efi.h>
#include <efilib.h>
#include "includes.h"

#include "EfiImage.h"

#define AsciiStrCmp strcmpa
#define AsciiStrLen strlena

#define EfiInitializeDriverLib InitializeLib
#define EfiLibGetSystemConfigurationTable LibGetSystemConfigurationTable

#define EFI_PROTOCOL_DEFINITION(a)  "includes.h"
#define EFI_GUID_DEFINITION(x)      "includes.h"
#define EFI_GUID_STRING(guidpointer, shortstring, longstring)

#define EFI_FORWARD_DECLARATION(x) typedef struct _##x x

#define DEBUG_CODE_BEGIN()  do { if (0) { UINT8  __DebugCodeLocal
#define DEBUG_CODE_END()    __DebugCodeLocal = 0; __DebugCodeLocal++; } } while (FALSE)
#define DEBUG_CODE(Expression)  \
  DEBUG_CODE_BEGIN ();          \
  Expression                    \
  DEBUG_CODE_END ()

// TODO: should handle x86, ARM, etc.
#define CpuBreakpoint() Print(L"EFI_BREAKPOINT() TRIGGERED!!\n") //__asm__ volatile("int $0x03");
#define CpuDeadLoop() while (TRUE)

//
// Math library routines
//
INT64 DivS64x64Remainder(
  IN INT64      Value1,
  IN INT64      Value2,
  OUT INT64     *Remainder);

UINT64 DivU64x64Remainder(
  IN UINT64   Value1,
  IN UINT64   Value2,
  OUT UINT64  *Remainder);

INT64 MultS64x64(
  IN INT64  Value1,
  IN INT64  Value2);

UINT64 MultU64x64(
  IN UINT64   Value1,
  IN UINT64   Value2);

UINT64 ARShiftU64(
  IN UINT64   Operand,
  IN UINTN    Count);

UINT64 LeftShiftU64(
  IN UINT64   Operand,
  IN UINT64   Count);

UINT64 RightShiftU64(
  IN UINT64   Operand,
  IN UINT64   Count);

VOID MemoryFence(
  VOID);

#endif
