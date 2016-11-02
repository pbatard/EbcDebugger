;
; EBC (EFI Byte Code) assembly 'Hello World'
; Copyright © 2016 Pete Batard <pete@akeo.ie> - Public Domain
;

include 'ebc.inc'
include 'efi.inc'
include 'format.inc'
include 'utf8.inc'

format peebc efi
entry EfiMain

section '.text' code executable readable
EfiMain:
  MOVn   R1, @R0(EFI_MAIN_PARAMETERS.SystemTable)
  MOVn   R1, @R1(EFI_SYSTEM_TABLE.ConOut)
  MOVREL R2, Hello
  PUSHn  R2
  PUSHn  R1
  CALLEX @R1(SIMPLE_TEXT_OUTPUT_INTERFACE.OutputString)
  MOV    R0, R0(+2,0)
  XOR    R7, R7
  BREAK  3
  RET

section '.data' data readable writeable
  Hello: du 0x0D, 0x0A
         du "Hello EBC World!", 0x0D, 0x0A
         du 0x0D, 0x0A, 0x00

section '.reloc' fixups data discardable
