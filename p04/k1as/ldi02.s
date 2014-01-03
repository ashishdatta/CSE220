; This is the expected output that you will see if you hexdump the binary using this command:
;
; $ ./k1as ldi02.s
; $ hexdump -C ldi02

; 4B 31 42 49 4E 21 43 05 00 00 00 00 00 00 00 00
; 00 09 00 00 00 FF FF 0F 00 01 0D 00 00 00 21 43
; 05 00 FF FF FF 0F

.DATA          1048575                     ; The data segment is at 0x000FFFFF

.TEXT          344865                      ; The text segment is at 0x00054321
               LDI     %B -1               ; opcode = 00001  reg = 1  imm = -1 (base 10) = 11111111111111111111111111
                                           ; encoding = 00001111111111111111111111111111
                                           ; encoding = 0000 1111 1111 1111 1111 1111 1111 1111
                                           ; encoding = 0    F    F    F    F    F    F    F
