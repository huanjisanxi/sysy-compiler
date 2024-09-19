
	.data
	.global n_0
n_0:
	.word 0

	.text
	.globl bubblesort
bubblesort:
	addi sp, sp, -168

0:

	sw a0, 0(sp)

4:

8:

	li t0, 0
	sw t0, 4(sp)

	j while_entry_0
while_entry_0:

	lw t0, 4(sp)
	sw t0, 12(sp)
12:

	la t0, n_0
	lw t0, 0(t0)
	sw t0, 16(sp)
16:

	lw t0, 16(sp)
	li t1, 1
	sub t0, t0, t1
	sw t0, 20(sp)
20:

	lw t0, 12(sp)
	lw t1, 20(sp)
	slt t0, t0, t1
	sw t0, 24(sp)
24:

	lw t0, 24(sp)
	bnez t0, while_body_0
	j while_end_0
while_body_0:

	li t0, 0
	sw t0, 8(sp)

	j while_entry_1
while_end_0:

	li a0, 0
	addi sp, sp, 168
	ret

while_entry_1:

	lw t0, 8(sp)
	sw t0, 28(sp)
28:

	la t0, n_0
	lw t0, 0(t0)
	sw t0, 32(sp)
32:

	lw t0, 4(sp)
	sw t0, 36(sp)
36:

	lw t0, 32(sp)
	lw t1, 36(sp)
	sub t0, t0, t1
	sw t0, 40(sp)
40:

	lw t0, 40(sp)
	li t1, 1
	sub t0, t0, t1
	sw t0, 44(sp)
44:

	lw t0, 28(sp)
	lw t1, 44(sp)
	slt t0, t0, t1
	sw t0, 48(sp)
48:

	lw t0, 48(sp)
	bnez t0, while_body_1
	j while_end_1
while_body_1:

	lw t0, 8(sp)
	sw t0, 52(sp)
52:

	lw t0, 0(sp)
	sw t0, 56(sp)
56:

	lw t0, 56(sp)
	lw t1, 52(sp)
	li t2, 4
	mul t1, t1, t2
	add t0, t0, t1
	sw t0, 60(sp)
60:

	lw t0, 60(sp)
	lw t0, 0(t0)
	sw t0, 64(sp)
64:

	lw t0, 8(sp)
	sw t0, 68(sp)
68:

	lw t0, 68(sp)
	li t1, 1
	add t0, t0, t1
	sw t0, 72(sp)
72:

	lw t0, 0(sp)
	sw t0, 76(sp)
76:

	lw t0, 76(sp)
	lw t1, 72(sp)
	li t2, 4
	mul t1, t1, t2
	add t0, t0, t1
	sw t0, 80(sp)
80:

	lw t0, 80(sp)
	lw t0, 0(t0)
	sw t0, 84(sp)
84:

	lw t0, 64(sp)
	lw t1, 84(sp)
	slt t0, t1, t0
	sw t0, 88(sp)
88:

	lw t0, 88(sp)
	bnez t0, then_2
	j end_2
while_end_1:

	lw t0, 4(sp)
	sw t0, 92(sp)
92:

	lw t0, 92(sp)
	li t1, 1
	add t0, t0, t1
	sw t0, 96(sp)
96:

	lw t0, 96(sp)
	sw t0, 4(sp)

	j while_entry_0
then_2:

100:	%tmp_4 = alloc i32
	%18 = load %j_3
	lw t0, 8(sp)
	sw t0, 104(sp)
104:
	%19 = add %18, 1
	lw t0, 104(sp)
	li t1, 1
	add t0, t0, t1
	sw t0, 108(sp)
108:
	%20 = load %arr_1
	lw t0, 0(sp)
	sw t0, 112(sp)
112:
	%ptr2 = getptr %20, %19
	lw t0, 112(sp)
	lw t1, 108(sp)
	li t2, 4
	mul t1, t1, t2
	add t0, t0, t1
	sw t0, 116(sp)
116:
	%21 = load %ptr2
	lw t0, 116(sp)
	lw t0, 0(t0)
	sw t0, 120(sp)
120:
	store %21, %tmp_4
	lw t0, 120(sp)
	sw t0, 100(sp)
	%22 = load %j_3
	lw t0, 8(sp)
	sw t0, 124(sp)
124:
	%23 = add %22, 1
	lw t0, 124(sp)
	li t1, 1
	add t0, t0, t1
	sw t0, 128(sp)
128:
	%24 = load %arr_1
	lw t0, 0(sp)
	sw t0, 132(sp)
132:
	%ptr3 = getptr %24, %23
	lw t0, 132(sp)
	lw t1, 128(sp)
	li t2, 4
	mul t1, t1, t2
	add t0, t0, t1
	sw t0, 136(sp)
136:
	%25 = load %j_3
	lw t0, 8(sp)
	sw t0, 140(sp)
140:
	%26 = load %arr_1
	lw t0, 0(sp)
	sw t0, 144(sp)
144:
	%ptr4 = getptr %26, %25
	lw t0, 144(sp)
	lw t1, 140(sp)
	li t2, 4
	mul t1, t1, t2
	add t0, t0, t1
	sw t0, 148(sp)
148:
	%27 = load %ptr4
	lw t0, 148(sp)
	lw t0, 0(t0)
	sw t0, 152(sp)
152:
	store %27, %ptr3
	lw t0, 152(sp)
	lw t1, 136(sp)
	sw t0, 0(t1)
	%28 = load %j_3
	lw t0, 8(sp)
	sw t0, 156(sp)
156:
	%29 = load %arr_1
	lw t0, 0(sp)
	sw t0, 160(sp)
160:
	%ptr5 = getptr %29, %28
	lw t0, 160(sp)
	lw t1, 156(sp)
	li t2, 4
	mul t1, t1, t2
	add t0, t0, t1
	sw t0, 164(sp)
164:
	%30 = load %tmp_4
	lw t0, 100(sp)
	sw t0, 168(sp)
168:
	store %30, %ptr5
	lw t0, 168(sp)
	lw t1, 164(sp)
	sw t0, 0(t1)

	j end_2
end_2:

	lw t0, 8(sp)
	sw t0, 172(sp)
172:

	lw t0, 172(sp)
	li t1, 1
	add t0, t0, t1
	sw t0, 176(sp)
176:

	lw t0, 176(sp)
	sw t0, 8(sp)

	j while_entry_1
	.text
	.globl main
main:
	addi sp, sp, -184
	sw ra, 180(sp)

	li t0, 10
	la t1, n_0
	sw t0, 0(t1)

0:

	addi t0, sp, 0
	li t1, 0
	li t2, 4
	mul t1, t1, t2
	add t0, t0, t1
	sw t0, 40(sp)
40:

	li t0, 0
	lw t1, 40(sp)
	sw t0, 0(t1)

	addi t0, sp, 0
	li t1, 1
	li t2, 4
	mul t1, t1, t2
	add t0, t0, t1
	sw t0, 44(sp)
44:

	li t0, 0
	lw t1, 44(sp)
	sw t0, 0(t1)

	addi t0, sp, 0
	li t1, 2
	li t2, 4
	mul t1, t1, t2
	add t0, t0, t1
	sw t0, 48(sp)
48:

	li t0, 0
	lw t1, 48(sp)
	sw t0, 0(t1)

	addi t0, sp, 0
	li t1, 3
	li t2, 4
	mul t1, t1, t2
	add t0, t0, t1
	sw t0, 52(sp)
52:

	li t0, 0
	lw t1, 52(sp)
	sw t0, 0(t1)

	addi t0, sp, 0
	li t1, 4
	li t2, 4
	mul t1, t1, t2
	add t0, t0, t1
	sw t0, 56(sp)
56:

	li t0, 0
	lw t1, 56(sp)
	sw t0, 0(t1)

	addi t0, sp, 0
	li t1, 5
	li t2, 4
	mul t1, t1, t2
	add t0, t0, t1
	sw t0, 60(sp)
60:

	li t0, 0
	lw t1, 60(sp)
	sw t0, 0(t1)

	addi t0, sp, 0
	li t1, 6
	li t2, 4
	mul t1, t1, t2
	add t0, t0, t1
	sw t0, 64(sp)
64:

	li t0, 0
	lw t1, 64(sp)
	sw t0, 0(t1)

	addi t0, sp, 0
	li t1, 7
	li t2, 4
	mul t1, t1, t2
	add t0, t0, t1
	sw t0, 68(sp)
68:

	li t0, 0
	lw t1, 68(sp)
	sw t0, 0(t1)

	addi t0, sp, 0
	li t1, 8
	li t2, 4
	mul t1, t1, t2
	add t0, t0, t1
	sw t0, 72(sp)
72:

	li t0, 0
	lw t1, 72(sp)
	sw t0, 0(t1)

	addi t0, sp, 0
	li t1, 9
	li t2, 4
	mul t1, t1, t2
	add t0, t0, t1
	sw t0, 76(sp)
76:

	li t0, 0
	lw t1, 76(sp)
	sw t0, 0(t1)

	addi t0, sp, 0
	li t1, 0
	li t2, 4
	mul t1, t1, t2
	add t0, t0, t1
	sw t0, 80(sp)
80:

	li t0, 4
	lw t1, 80(sp)
	sw t0, 0(t1)

	addi t0, sp, 0
	li t1, 1
	li t2, 4
	mul t1, t1, t2
	add t0, t0, t1
	sw t0, 84(sp)
84:

	li t0, 3
	lw t1, 84(sp)
	sw t0, 0(t1)

	addi t0, sp, 0
	li t1, 2
	li t2, 4
	mul t1, t1, t2
	add t0, t0, t1
	sw t0, 88(sp)
88:

	li t0, 9
	lw t1, 88(sp)
	sw t0, 0(t1)

	addi t0, sp, 0
	li t1, 3
	li t2, 4
	mul t1, t1, t2
	add t0, t0, t1
	sw t0, 92(sp)
92:

	li t0, 2
	lw t1, 92(sp)
	sw t0, 0(t1)

	addi t0, sp, 0
	li t1, 4
	li t2, 4
	mul t1, t1, t2
	add t0, t0, t1
	sw t0, 96(sp)
96:

	li t0, 0
	lw t1, 96(sp)
	sw t0, 0(t1)

	addi t0, sp, 0
	li t1, 5
	li t2, 4
	mul t1, t1, t2
	add t0, t0, t1
	sw t0, 100(sp)
100:

	li t0, 1
	lw t1, 100(sp)
	sw t0, 0(t1)

	addi t0, sp, 0
	li t1, 6
	li t2, 4
	mul t1, t1, t2
	add t0, t0, t1
	sw t0, 104(sp)
104:

	li t0, 6
	lw t1, 104(sp)
	sw t0, 0(t1)

	addi t0, sp, 0
	li t1, 7
	li t2, 4
	mul t1, t1, t2
	add t0, t0, t1
	sw t0, 108(sp)
108:

	li t0, 5
	lw t1, 108(sp)
	sw t0, 0(t1)

	addi t0, sp, 0
	li t1, 8
	li t2, 4
	mul t1, t1, t2
	add t0, t0, t1
	sw t0, 112(sp)
112:

	li t0, 7
	lw t1, 112(sp)
	sw t0, 0(t1)

	addi t0, sp, 0
	li t1, 9
	li t2, 4
	mul t1, t1, t2
	add t0, t0, t1
	sw t0, 116(sp)
116:

	li t0, 8
	lw t1, 116(sp)
	sw t0, 0(t1)

120:

	addi t0, sp, 0
	li t1, 0
	li t2, 4
	mul t1, t1, t2
	add t0, t0, t1
	sw t0, 124(sp)
124:

	lw a0, 124(sp)
	call bubblesort
	sw a0, 128(sp)
128:

	lw t0, 128(sp)
	sw t0, 120(sp)

	j while_entry_3
while_entry_3:

	lw t0, 120(sp)
	sw t0, 132(sp)
132:

	la t0, n_0
	lw t0, 0(t0)
	sw t0, 136(sp)
136:

	lw t0, 132(sp)
	lw t1, 136(sp)
	slt t0, t0, t1
	sw t0, 140(sp)
140:

	lw t0, 140(sp)
	bnez t0, while_body_3
	j while_end_3
while_body_3:

144:

	lw t0, 120(sp)
	sw t0, 148(sp)
148:

	addi t0, sp, 0
	lw t1, 148(sp)
	li t2, 4
	mul t1, t1, t2
	add t0, t0, t1
	sw t0, 152(sp)
152:

	lw t0, 152(sp)
	lw t0, 0(t0)
	sw t0, 156(sp)
156:

	lw t0, 156(sp)
	sw t0, 144(sp)

	lw t0, 144(sp)
	sw t0, 160(sp)
160:

	lw a0, 160(sp)
	call putint

	li t0, 10
	sw t0, 144(sp)

	lw t0, 144(sp)
	sw t0, 164(sp)
164:

	lw a0, 164(sp)
	call putch

	lw t0, 120(sp)
	sw t0, 168(sp)
168:

	lw t0, 168(sp)
	li t1, 1
	add t0, t0, t1
	sw t0, 172(sp)
172:

	lw t0, 172(sp)
	sw t0, 120(sp)

	j while_entry_3
while_end_3:

	li a0, 0
	lw ra, 180(sp)
	addi sp, sp, 184
	ret


