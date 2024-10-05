.section .text.boot

.global s_RESET
s_RESET:
lui $a0, 0xcafe
lui $a1, 0xbfc0
ori $a1, $a1, 0xfc0
sw $a0, 0x0 ($a1)
move $sp, $a1
j c_RESET