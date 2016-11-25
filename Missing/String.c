/*++

Copyright (c) 2004 - 2007, Intel Corporation
All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

String.c

Abstract:

String primitives

--*/

#include <Uefi.h>

VOID
EFIAPI
StrCpyS(
	OUT CHAR16       *Dst,
	IN  UINTN        DstMax,
	IN  CONST CHAR16 *Src
)
{
	UINTN Index;
	UINTN SrcLen;

	SrcLen = StrLen(Src);

	Index = 0;
	while (Index < SrcLen) {
		Dst[Index] = Src[Index];
		Index++;
	}
	Dst[Index] = 0;
}

VOID
EFIAPI
StrnCpyS(
	OUT CHAR16       *Dst,
	IN  UINTN        DstMax,
	IN  CONST CHAR16 *Src,
	IN  UINTN        Length
)
{
	UINTN Index;
	UINTN SrcLen;

	SrcLen = StrLen(Src);

	Index = 0;
	while (Index < Length && Index < SrcLen) {
		Dst[Index] = Src[Index];
		Index++;
	}
	for (Index = SrcLen; Index < Length; Index++) {
		Dst[Index] = 0;
	}
}

VOID
EFIAPI
StrnCatS(
	IN OUT CHAR16       *Dest,
	IN     UINTN        DestMax,
	IN     CONST CHAR16 *Src,
	IN     UINTN        Length
)
{
	StrnCpyS(Dest + StrLen(Dest), DestMax, Src, Length);
}

VOID
EFIAPI
AsciiStrnCpyS(
	OUT CHAR8    *Dst,
	IN  UINTN    DstMax,
	IN  CHAR8    *Src,
	IN  UINTN    Length
)
{
	UINTN Index;
	UINTN SrcLen;

	SrcLen = AsciiStrLen(Src);

	Index = 0;
	while (Index < Length && Index < SrcLen) {
		Dst[Index] = Src[Index];
		Index++;
	}
	for (Index = SrcLen; Index < Length; Index++) {
		Dst[Index] = 0;
	}
}

extern CHAR8 AsciiToUpper(CHAR8 Chr);

INTN
EFIAPI
AsciiStriCmp(
	IN CHAR8    *String,
	IN CHAR8    *String2
)
{
	while ((*String != L'\0') &&
		(AsciiToUpper(*String) == (CHAR16)AsciiToUpper(*String2))) {
		String++;
		String2++;
	}

	return AsciiToUpper(*String) - (CHAR16)AsciiToUpper(*String2);
}
