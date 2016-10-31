/*++

Copyright (c) 2016 - Pete Batard <pete@akeo.ie>

All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Abstract:

Minimal set of PrintLib declarations required to build the application

--*/

#ifndef _EFI_PRINT_LIB_H_
#define _EFI_PRINT_LIB_H_

EFI_STATUS
EFIAPI
StrnCatS(
	IN OUT CHAR16       *Dest,
	IN     UINTN        DestMax,
	IN     CONST CHAR16 *Src,
	IN     UINTN        Length
);

VOID
EFIAPI
StrCpyS(
	OUT CHAR16       *Dst,
	IN  UINTN        DstMax,
	IN  CONST CHAR16 *Src
);

VOID
EFIAPI
StrnCpyS(
	OUT CHAR16       *Dst,
	IN  UINTN        DstMax,
	IN  CONST CHAR16 *Src,
	IN  UINTN        Length
);

VOID
EFIAPI
AsciiStrnCpyS(
	OUT CHAR8    *Dst,
	IN  UINTN    DstMax,
	IN  CHAR8    *Src,
	IN  UINTN    Length
);

INTN
EFIAPI
AsciiStriCmp(
	IN CHAR8    *String,
	IN CHAR8    *String2
);

#endif
