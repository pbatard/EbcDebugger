/*++

Copyright (c) 2016 - Pete Batard <pete@akeo.ie>

All rights reserved. This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Abstract:

Minimal set of EfiCommonLib declarations required to build the application

--*/

#ifndef _EFI_COMMON_LIB_H_
#define _EFI_COMMON_LIB_H_

VOID
EfiCommonLibCopyMem(
	IN VOID     *Destination,
	IN VOID     *Source,
	IN UINTN    Length
);

EFI_STATUS
EfiLibReportStatusCode(
	IN EFI_STATUS_CODE_TYPE     Type,
	IN EFI_STATUS_CODE_VALUE    Value,
	IN UINT32                   Instance,
	IN EFI_GUID                 *CallerId OPTIONAL,
	IN EFI_STATUS_CODE_DATA     *Data     OPTIONAL
);

#endif
