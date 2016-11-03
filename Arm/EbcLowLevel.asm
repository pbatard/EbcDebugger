///** @file
//
//  This code provides low level routines that support the Virtual Machine
//  for option ROMs.
//
//  Copyright (c) 2016, Pete Batard. All rights reserved.<BR>
//  Copyright (c) 2016, Linaro, Ltd. All rights reserved.<BR>
//  Copyright (c) 2015, The Linux Foundation. All rights reserved.<BR>
//  Copyright (c) 2007 - 2014, Intel Corporation. All rights reserved.<BR>
//
//  This program and the accompanying materials
//  are licensed and made available under the terms and conditions of the BSD License
//  which accompanies this distribution.  The full text of the license may be found at
//  http://opensource.org/licenses/bsd-license.php
//
//  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
//  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
//
//**/

    EXPORT EbcLLCALLEXNativeArm
    EXPORT EbcLLEbcInterpret
    EXPORT EbcLLExecuteEbcImageEntryPoint

    EXPORT mEbcInstructionBufferTemplate

    IMPORT ExecuteEbcImageEntryPoint
    IMPORT EbcInterpret

    AREA EbcLowLevel, CODE, READONLY

//****************************************************************************
// EbcLLCALLEX
//
// This function is called to execute an EBC CALLEX instruction.
// This instruction requires that we thunk out to external native code.
// Note that due to the ARM Procedure Call Standard, we may have to align
// 64-bit arguments to an even register or dword aligned stack address,
// which is what the extra ArgLayout parameter is used for.
// Also, to optimize for speed, we arbitrarily limit to 16 the maximum
// number of arguments a native call can have.
//
//****************************************************************************
// UINTN EbcLLCALLEXNativeArm(UINTN FuncAddr, UINTN NewStackPointer,
//                            VOID *FramePtr, UINT16 ArgLayout)
EbcLLCALLEXNativeArm FUNCTION

    mov     ip, r1                  // Use ip as our argument walker
    push    {r0, r4-r6}
    mov     r4, r2                  // Keep a copy of FramePtr
    mov     r5, r3                  // Keep a copy of ArgLayout
    mov     r6, #2                  // Arg counter (2 for r0 and r2)

    //
    // Process the register arguments, skipping r1 and r3
    // as needed, according to the argument layout.
    //
    lsrs    r5, r5, #1
    bcc     n0                      // Is our next argument 64-bit?
    ldr     r0, [ip], #4            // Yes => fill in r0-r1
    ldr     r1, [ip], #4
    b       n1
n0
    ldr     r0, [ip], #4            // No => fill in r0
    lsrs    r5, r5, #1
    bcs     n2                      // Is our next argument 64-bit?
    ldr     r1, [ip], #4            // No => fill in r1
    add     r6, r6, #1              // Increment arg counter for r1
n1
    lsrs    r5, r5, #1
    bcc     n3                      // Is our next argument 64-bit?
n2
    ldr     r2, [ip], #4            // Yes => fill in r2-r3
    ldr     r3, [ip], #4
    b       n4
n3
    ldr     r2, [ip], #4            // No => fill in r2
    tst     r5, #1
    bne     n4                      // Is our next argument 64-bit?
    ldr     r3, [ip], #4            // No => fill in r3
    lsr     r5, r5, #1
    add     r6, r6, #1              // Increment arg counter for r3
n4
    cmp     r4, ip
    bgt     n5                      // More args?
    pop     {ip}                    // No => perform a tail call
    pop     {r4-r6}
    bx      ip

    //
    // Cannot perform a tail call => We need to properly enqueue (and
    // align) all EBC stack parameters before we invoke the native call.
    //
n5
    push    {r7-r10, lr}
    mov     r10, sp                 // Preserve original sp
    sub     r7, r10, #116           // Space for 14 64-bit args (+1 word)
    and     r7, r7, #0xfffffff8     // Start with an aligned stack
    mov     sp, r7

    //
    // Duplicate EBC data onto the local stack:
    // ip = EBC arg walker
    // r4 = top of EBC stack frame
    // r5 = arg layout
    // r6 = arg counter
    // r7 = local stack pointer
    //
n6
    add     r6, r6, #1              // Increment the arg counter
    lsrs    r5, r5, #1
    bcs     n7                      // Is the current argument 64 bit?
    ldr     r8, [ip], #4            // No? Then just copy it onstack
    str     r8, [r7], #4
    b       n9
n7
    tst     r7, #7                  // Yes. Is SP aligned to 8 bytes?
    beq     n8
    add     r7, r7, #4              // No? Realign.
n8
    ldr     r8, [ip], #4            // EBC stack may not be aligned for ldrd...
    ldr     r9, [ip], #4
    strd    r8, r9, [r7], #8        // ...but the local stack is.
n9
    cmp     r6, #16                 // More than 16 arguments processed?
    bge     n10
    cmp     r4, ip                  // Reached the top of the EBC stack frame?
    bgt     n6

n10
    ldr     ip, [r10, #20]          // Set the target address in ip
    blx     ip
    mov     sp, r10                 // Restore the stack, dequeue and return
    pop     {r7-r10, ip}
    pop     {r3, r4-r6}             // Destack with r3, as r0 may contain a return value
    mov     pc, ip
    ENDFUNC

//****************************************************************************
// EbcLLEbcInterpret
//
// This function is called by the thunk code to handle an Native to EBC call
// This can handle up to 16 arguments (1-4 on in r0-r3, 5-16 are on the stack)
// ip contains the Entry point that will be the first argument when
// EBCInterpret is called.
//
//****************************************************************************
EbcLLEbcInterpret FUNCTION

    stmdb   sp!, {r4, lr}

    // push the entry point and the address of args #5 - #16 onto the stack
    add     r4, sp, #8
    str     ip, [sp, #-8]!
    str     r4, [sp, #4]

    // call C-code
    bl      EbcInterpret

    add     sp, sp, #8
    ldmia   sp!, {r4, pc}

    ENDFUNC

//****************************************************************************
// EbcLLExecuteEbcImageEntryPoint
//
// This function is called by the thunk code to handle the image entry point
// ip contains the Entry point that will be the third argument when
// ExecuteEbcImageEntryPoint is called.
//
//****************************************************************************
EbcLLExecuteEbcImageEntryPoint FUNCTION
    ldr     r2, [ip, #12]

    // tail call to C code
    b       ExecuteEbcImageEntryPoint
    ENDFUNC

//****************************************************************************
// mEbcInstructionBufferTemplate
//****************************************************************************
;    .section    ".rodata", "a"
;    .align      2
;    .arm
mEbcInstructionBufferTemplate FUNCTION
    adr     ip, .
    ldr     pc, n11

    //
    // Add a magic code here to help the VM recognize the thunk.
    //
    udf     #0xEBC

    dcd   0                       // EBC_ENTRYPOINT_SIGNATURE
n11
    dcd   0                       // EBC_LL_EBC_ENTRYPOINT_SIGNATURE
    ENDFUNC

    END
