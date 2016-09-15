#ifndef _EFI_DRIVER_LIB_H_
#define _EFI_DRIVER_LIB_H_

VOID *
EfiLibAllocatePool(
	IN  UINTN   AllocationSize
);

VOID *
EfiLibAllocateRuntimePool(
	IN  UINTN   AllocationSize
);

VOID *
EfiLibAllocateZeroPool(
	IN  UINTN   AllocationSize
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
