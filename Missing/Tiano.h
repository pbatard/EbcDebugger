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

#define EfiCopyMem CopyMem
#define EfiZeroMem ZeroMem
#define EfiSetMem SetMem
#define EfiStrLen StrLen
#define EfiStrCmp StrCmp
#define EfiStrCpy StrCpy
#define EfiAsciiStrCmp strcmpa
#define EfiAsciiStrLen strlena

#define EfiInitializeDriverLib InitializeLib
#define EfiLibGetSystemConfigurationTable LibGetSystemConfigurationTable

#define EFI_PROTOCOL_DEFINITION(a)  "includes.h"
#define EFI_GUID_DEFINITION(x)      "includes.h"
#define EFI_GUID_STRING(guidpointer, shortstring, longstring)

#define EFI_FORWARD_DECLARATION(x) typedef struct _##x x

#define DEBUG_CODE(x)
// TODO: should handle x86, ARM, etc.
#define EFI_BREAKPOINT() Print(L"EFI_BREAKPOINT() TRIGGERED!!\n") //__asm__ volatile("int $0x03");
#define EFI_DEADLOOP() while (TRUE)

#define EFI_ERROR_CODE             0x00000002
#define EFI_ERROR_UNRECOVERED      0x90000000

#define EFI_SOFTWARE               0x03000000
#define EFI_SOFTWARE_EBC_EXCEPTION (EFI_SOFTWARE | 0x000C0000)

typedef INTN   EFI_EXCEPTION_TYPE;

typedef UINT32 EFI_STATUS_CODE_VALUE;
typedef UINT32 EFI_STATUS_CODE_TYPE;
typedef struct {
	UINT16    HeaderSize;
	UINT16    Size;
	EFI_GUID  Type;
} EFI_STATUS_CODE_DATA;

#endif
