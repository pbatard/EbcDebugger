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

#ifndef UEFI_H
#define UEFI_H

#if !defined (_MSC_VER) && !defined (__clang__)
#error This header should only be used with Microsoft compilers
#endif

#if defined (_M_IX86)
#define MDE_CPU_IA32
#define EFI32
#elif defined (_M_X64)
#define MDE_CPU_X64
#elif defined (_M_ARM)
#define MDE_CPU_ARM
#define EFI32
#endif

#define VA_LIST  va_list
#define VA_START va_start
#define VA_ARG   va_arg
#define VA_COPY  va_copy
#define VA_END   va_end

#include <efi.h>
#include <efilib.h>

#define GUID EFI_GUID
#define SIGNATURE_16  EFI_SIGNATURE_16
#define SIGNATURE_32  EFI_SIGNATURE_32

#include "IndustryStandard/PeImage.h"

#define AsciiStrCmp strcmpa
#define AsciiStrnCmp strncmpa
#define AsciiStrLen strlena
#define UnicodeVSPrint VSPrint

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(A) (sizeof(A)/sizeof((A)[0]))
#endif

#define EfiGetSystemConfigurationTable LibGetSystemConfigurationTable

#define EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL EFI_SIMPLE_TEXT_OUT_PROTOCOL
#define EFI_SIMPLE_TEXT_INPUT_PROTOCOL  EFI_SIMPLE_TEXT_IN_PROTOCOL

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
INT64 EFIAPI DivS64x64Remainder (
  IN  INT64  Dividend,
  IN  INT64  Divisor,
  OUT INT64  *Remainder  OPTIONAL
);

UINT64 EFIAPI DivU64x64Remainder(
  IN  UINT64  Dividend,
  IN  UINT64  Divisor,
  OUT UINT64  *Remainder  OPTIONAL
);

INT64 EFIAPI MultS64x64(
  IN  INT64  Multiplicand,
  IN  INT64  Multiplier
);

UINT64 EFIAPI MultU64x64(
  IN  UINT64  Multiplicand,
  IN  UINT64  Multiplier
);

UINT64 EFIAPI ARShiftU64(
  IN UINT64  Operand,
  IN UINTN   Count
);

UINT16 EFIAPI SwapBytes16 (
  IN UINT16  Value
);

UINT32 EFIAPI SwapBytes32(
  IN UINT32  Value
);

VOID EFIAPI MemoryFence(
  VOID
);

#endif
