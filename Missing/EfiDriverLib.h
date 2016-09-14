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

#endif
