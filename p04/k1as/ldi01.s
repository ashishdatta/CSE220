; This is the expected output that you will see if you hexdump the binary using this command:
;
; $ ./k1as ldi01.s
; $ hexdump -C ldi01

; 4B 31 42 49 4E 21 43 05 00 00 00 00 00 00 00 00
; 00 09 00 00 00 FF FF 0F 00 01 0D 00 00 00 21 43
; 05 00 FF FF FF 0B

.DATA          1048575                     ; The data segment is at 0x000FFFFF

.TEXT          344865                      ; The text segment is at 0x00054321
               LDI     %A -1               ; opcode = 00001  reg = 0  imm = -1 (base 10) = 11111111111111111111111111
                                           ; encoding = 00001011111111111111111111111111
                                           ; encoding = 0000 1011 1111 1111 1111 1111 1111 1111
                                           ; encoding = 0    B    F    F    F    F    F    F
