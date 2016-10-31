/*++

Copyright (c) 2005 - 2007, Intel Corporation                                                         
All rights reserved. This program and the accompanying materials                          
are licensed and made available under the terms and conditions of the BSD License         
which accompanies this distribution.  The full text of the license may be found at        
http://opensource.org/licenses/bsd-license.php                                            
                                                                                          
THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,                     
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.             

Module Name:

  x64math.c

Abstract:

  Math routines for x64.

--*/

#include "Uefi.h"

UINT64
LeftShiftU64 (
  IN UINT64   Operand,
  IN UINT64   Count
  )
/*++

Routine Description:
  
  Left-shift a 64 bit value.

Arguments:

  Operand - 64-bit value to shift
  Count   - shift count

Returns:

  Operand << Count

--*/
{
  if (Count > 63) {
    return 0;
  }

  return Operand << Count;
}

UINT64
RightShiftU64 (
  IN UINT64   Operand,
  IN UINT64   Count
  )
/*++

Routine Description:
  
  Right-shift a 64 bit value.

Arguments:

  Operand - 64-bit value to shift
  Count   - shift count

Returns:

  Operand >> Count

--*/
{
  if (Count > 63) {
    return 0;
  }

  return Operand >> Count;
}

UINT64
ARShiftU64 (
  IN UINT64   Operand,
  IN UINTN   Count
  )
/*++

Routine Description:
  
  Right-shift a 64 bit signed value.

Arguments:

  Operand - 64-bit value to shift
  Count   - shift count

Returns:

  Operand >> Count

--*/
{
  if (Count > 63) {

    if (Operand & (0x01ll << 63)) {
      return (UINT64)~0;
    }

    return 0;
  }

  return Operand >> Count;
}

VOID
MemoryFence(
  VOID
)
{
  return;
}

INT64
MultS64x64 (
  INT64 Value1,
  INT64 Value2
  )
/*++

Routine Description:
  
  Multiply two signed 32-bit numbers.

Arguments:

  Value1      - first value to multiply
  Value2      - value to multiply Value1 by

Returns:

  Value1 * Value2

--*/
{
  INT64 Result;
  
  Result  = Value1 * Value2;

  return Result;
}

UINT64
MultU64x64 (
  UINT64 Value1,
  UINT64 Value2
  )
/*++

Routine Description:
  
  Multiply two unsigned 32-bit values.

Arguments:

  Value1      - first number
  Value2      - number to multiply by Value1 

Returns:

  Value1 * Value2

--*/
{
  UINT64  Result;

  Result  = Value1 * Value2;

  return Result;
}

INT64
DivS64x64Remainder(
  INT64 Value1,
  INT64 Value2,
  INT64 *Remainder
  )
/*++

Routine Description:
  
  Divide two 64-bit signed values.

Arguments:

  Value1    - dividend
  Value2    - divisor
  Remainder - remainder of Value1/Value2

Returns:

  Value1 / Value2

Note:

  The 64-bit remainder is in *Remainder and the quotient is the return value.

--*/
{
  INT64 Result;

  if (Value2 == 0x0) {
    Result      = 0x8000000000000000;
    *Remainder  = 0x8000000000000000;
  } else {
    Result      = Value1 / Value2;
    *Remainder  = Value1 - Result * Value2;
  }

  return Result;
}

UINT64
DivU64x64Remainder (
  UINT64 Value1,
  UINT64 Value2,
  UINT64 *Remainder
  )
/*++

Routine Description:
  
  Divide two 64-bit unsigned values.

Arguments:

  Value1    - dividend
  Value2    - divisor
  Remainder - remainder of Value1/Value2

Returns:

  Value1 / Valu2

Note:

  The 64-bit remainder is in *Remainder and the quotient is the return value.

--*/
{
  UINT64  Result;

  if (Value2 == 0x0) {
    Result      = 0x8000000000000000;
    *Remainder  = 0x8000000000000000;
  } else {
    Result      = Value1 / Value2;
    *Remainder  = Value1 - Result * Value2;
  }

  return Result;
}
