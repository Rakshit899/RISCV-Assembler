#R format
add x1 x2 x3
and x1 x2 x3
or x1 x2 x3
sll x1 x2 x3
slt x1 x2 x3
sra x1 x2 x3
sub x1 x2 x3
xor x1 x2 x3
mul x1 x2 x3
div x1 x2 x3
rem x10 x31 x21
#I format addi, andi, ori, lb, ld, lh, lw, jalr
addi x1 x2 5
andi x1 x2 7
ori x1 x2 10
jalr x1 x2 0
lw x2 0(x3)
lb x2 0(x3)
ld x2 40(x3)
lh x2 10(x3)
# S format - sb, sw, sd, sh
sb x2 0(x3)
sw x2 0(x3)
sd x2 0(x3)
sh x2 -4(x3)
# SB format - beq, bne, bge, blt
beq x0 x3 -4
bne x10 x3 -40
bge x0 x3 12
blt x12 x13 8
# U format - auipc, lui
auipc x5 65536
lui x5 65536
#UJ format - jal
jal x1 -4
