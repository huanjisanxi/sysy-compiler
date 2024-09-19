decl @getint(): i32
decl @getch(): i32
decl @getarray(*i32): i32
decl @putint(i32)
decl @putch(i32)
decl @putarray(i32, *i32)
decl @starttime()
decl @stoptime()

global %n_0 = alloc i32, 0
fun @bubblesort(@arr: *i32): i32 {
%entry:
	%arr_1 = alloc *i32
	store @arr, %arr_1
	%i_2 = alloc i32
	%j_3 = alloc i32
	store 0, %i_2
	jump %while_entry_0

%while_entry_0:
	%0 = load %i_2
	%1 = load %n_0
	%2 = sub %1, 1
	%3 = lt %0, %2
	br %3, %while_body_0, %while_end_0

%while_body_0:
	store 0, %j_3
	jump %while_entry_1

%while_entry_1:
	%4 = load %j_3
	%5 = load %n_0
	%6 = load %i_2
	%7 = sub %5, %6
	%8 = sub %7, 1
	%9 = lt %4, %8
	br %9, %while_body_1, %while_end_1

%while_body_1:
	%10 = load %j_3
	%11 = load %arr_1
	%ptr0 = getptr %11, %10
	%12 = load %ptr0
	%13 = load %j_3
	%14 = add %13, 1
	%15 = load %arr_1
	%ptr1 = getptr %15, %14
	%16 = load %ptr1
	%17 = gt %12, %16
	br %17, %then_2, %end_2

%then_2:
	%tmp_4 = alloc i32
	%18 = load %j_3
	%19 = add %18, 1
	%20 = load %arr_1
	%ptr2 = getptr %20, %19
	%21 = load %ptr2
	store %21, %tmp_4
	%22 = load %j_3
	%23 = add %22, 1
	%24 = load %arr_1
	%ptr3 = getptr %24, %23
	%25 = load %j_3
	%26 = load %arr_1
	%ptr4 = getptr %26, %25
	%27 = load %ptr4
	store %27, %ptr3
	%28 = load %j_3
	%29 = load %arr_1
	%ptr5 = getptr %29, %28
	%30 = load %tmp_4
	store %30, %ptr5
	jump %end_2

%end_2:
	%31 = load %j_3
	%32 = add %31, 1
	store %32, %j_3
	jump %while_entry_1

%while_end_1:
	%33 = load %i_2
	%34 = add %33, 1
	store %34, %i_2
	jump %while_entry_0

%while_end_0:
	ret 0
}

fun @main(): i32 {
%entry:
	store 10, %n_0
	%a_5 = alloc [i32, 10]
	%ptr6 = getelemptr %a_5, 0
	store 0, %ptr6
	%ptr7 = getelemptr %a_5, 1
	store 0, %ptr7
	%ptr8 = getelemptr %a_5, 2
	store 0, %ptr8
	%ptr9 = getelemptr %a_5, 3
	store 0, %ptr9
	%ptr10 = getelemptr %a_5, 4
	store 0, %ptr10
	%ptr11 = getelemptr %a_5, 5
	store 0, %ptr11
	%ptr12 = getelemptr %a_5, 6
	store 0, %ptr12
	%ptr13 = getelemptr %a_5, 7
	store 0, %ptr13
	%ptr14 = getelemptr %a_5, 8
	store 0, %ptr14
	%ptr15 = getelemptr %a_5, 9
	store 0, %ptr15
	%ptr16 = getelemptr %a_5, 0
	store 4, %ptr16
	%ptr17 = getelemptr %a_5, 1
	store 3, %ptr17
	%ptr18 = getelemptr %a_5, 2
	store 9, %ptr18
	%ptr19 = getelemptr %a_5, 3
	store 2, %ptr19
	%ptr20 = getelemptr %a_5, 4
	store 0, %ptr20
	%ptr21 = getelemptr %a_5, 5
	store 1, %ptr21
	%ptr22 = getelemptr %a_5, 6
	store 6, %ptr22
	%ptr23 = getelemptr %a_5, 7
	store 5, %ptr23
	%ptr24 = getelemptr %a_5, 8
	store 7, %ptr24
	%ptr25 = getelemptr %a_5, 9
	store 8, %ptr25
	%i_6 = alloc i32
	%35 = getelemptr %a_5, 0
	%36 = call @bubblesort(%35)
	store %36, %i_6
	jump %while_entry_3

%while_entry_3:
	%37 = load %i_6
	%38 = load %n_0
	%39 = lt %37, %38
	br %39, %while_body_3, %while_end_3

%while_body_3:
	%tmp_7 = alloc i32
	%40 = load %i_6
	%ptr26 = getelemptr %a_5, %40
	%41 = load %ptr26
	store %41, %tmp_7
	%42 = load %tmp_7
	call @putint(%42)
	store 10, %tmp_7
	%43 = load %tmp_7
	call @putch(%43)
	%44 = load %i_6
	%45 = add %44, 1
	store %45, %i_6
	jump %while_entry_3

%while_end_3:
	ret 0
}


test
	.data
	.global n_0
n_0:
	.word 0

	.text
	.globl bubblesort
bubblesort:
	addi sp, sp, -168
test
test
	sw a0, 0(sp)
test
test
test
	li t0, 0
	sw t0, 4(sp)
test
	j while_entry_0
while_entry_0:
test
	lw t0, 4(sp)
	sw t0, 12(sp)
test
	la t0, n_0
	lw t0, 0(t0)
	sw t0, 16(sp)
test
	lw t0, 16(sp)
	li t1, 1
	sub t0, t0, t1
	sw t0, 20(sp)
test
	lw t0, 12(sp)
	lw t1, 20(sp)
	slt t0, t0, t1
	sw t0, 24(sp)
test
	lw t0, 24(sp)
	bnez t0, while_body_0
	j while_end_0
while_body_0:
test
	li t0, 0
	sw t0, 8(sp)
test
	j while_entry_1
while_end_0:
test
	li a0, 0
	addi sp, sp, 168
	ret

while_entry_1:
test
	lw t0, 8(sp)
	sw t0, 28(sp)
test
	la t0, n_0
	lw t0, 0(t0)
	sw t0, 32(sp)
test
	lw t0, 4(sp)
	sw t0, 36(sp)
test
	lw t0, 32(sp)
	lw t1, 36(sp)
	sub t0, t0, t1
	sw t0, 40(sp)
test
	lw t0, 40(sp)
	li t1, 1
	sub t0, t0, t1
	sw t0, 44(sp)
test
	lw t0, 28(sp)
	lw t1, 44(sp)
	slt t0, t0, t1
	sw t0, 48(sp)
test
	lw t0, 48(sp)
	bnez t0, while_body_1
	j while_end_1
while_body_1:
test
	lw t0, 8(sp)
	sw t0, 52(sp)
test
	lw t0, 0(sp)
	sw t0, 56(sp)
test
	lw t0, 56(sp)
	lw t1, 52(sp)
	li t2, 4
	mul t1, t1, t2
	add t0, t0, t1
	sw t0, 60(sp)
test
	lw t0, 60(sp)
	lw t0, 0(t0)
	sw t0, 64(sp)
test
	lw t0, 8(sp)
	sw t0, 68(sp)
test
	lw t0, 68(sp)
	li t1, 1
	add t0, t0, t1
	sw t0, 72(sp)
test
	lw t0, 0(sp)
	sw t0, 76(sp)
test
	lw t0, 76(sp)
	lw t1, 72(sp)
	li t2, 4
	mul t1, t1, t2
	add t0, t0, t1
	sw t0, 80(sp)
test
	lw t0, 80(sp)
	lw t0, 0(t0)
	sw t0, 84(sp)
test
	lw t0, 64(sp)
	lw t1, 84(sp)
	slt t0, t1, t0
	sw t0, 88(sp)
test
	lw t0, 88(sp)
	bnez t0, then_2
	j end_2
while_end_1:
test
	lw t0, 4(sp)
	sw t0, 92(sp)
test
	lw t0, 92(sp)
	li t1, 1
	add t0, t0, t1
	sw t0, 96(sp)
test
	lw t0, 96(sp)
	sw t0, 4(sp)
test
	j while_entry_0
then_2:
test
test
	lw t0, 8(sp)
	sw t0, 104(sp)
test
	lw t0, 104(sp)
	li t1, 1
	add t0, t0, t1
	sw t0, 108(sp)
test
	lw t0, 0(sp)
	sw t0, 112(sp)
test
	lw t0, 112(sp)
	lw t1, 108(sp)
	li t2, 4
	mul t1, t1, t2
	add t0, t0, t1
	sw t0, 116(sp)
test
	lw t0, 116(sp)
	lw t0, 0(t0)
	sw t0, 120(sp)
test
	lw t0, 120(sp)
	sw t0, 100(sp)
test
	lw t0, 8(sp)
	sw t0, 124(sp)
test
	lw t0, 124(sp)
	li t1, 1
	add t0, t0, t1
	sw t0, 128(sp)
test
	lw t0, 0(sp)
	sw t0, 132(sp)
test
	lw t0, 132(sp)
	lw t1, 128(sp)
	li t2, 4
	mul t1, t1, t2
	add t0, t0, t1
	sw t0, 136(sp)
test
	lw t0, 8(sp)
	sw t0, 140(sp)
test
	lw t0, 0(sp)
	sw t0, 144(sp)
test
	lw t0, 144(sp)
	lw t1, 140(sp)
	li t2, 4
	mul t1, t1, t2
	add t0, t0, t1
	sw t0, 148(sp)
test
	lw t0, 148(sp)
	lw t0, 0(t0)
	sw t0, 152(sp)
test
	lw t0, 152(sp)
	lw t1, 136(sp)
	sw t0, 0(t1)
test
	lw t0, 8(sp)
	sw t0, 156(sp)
test
	lw t0, 0(sp)
	sw t0, 160(sp)
test
	lw t0, 160(sp)
	lw t1, 156(sp)
	li t2, 4
	mul t1, t1, t2
	add t0, t0, t1
	sw t0, 164(sp)
test
	lw t0, 100(sp)
	sw t0, 168(sp)
test
	lw t0, 168(sp)
	lw t1, 164(sp)
	sw t0, 0(t1)
test
	j end_2
end_2:
test
	lw t0, 8(sp)
	sw t0, 172(sp)
test
	lw t0, 172(sp)
	li t1, 1
	add t0, t0, t1
	sw t0, 176(sp)
test
	lw t0, 176(sp)
	sw t0, 8(sp)
test
	j while_entry_1
176:
168:
160:
156:
152:
148:
144:
136:
132:
116:
128:
36:
164:
76:
20:
48:
100:
112:
16:
28:
56:
68:
4:
40:
0:
120:
32:
60:
140:
80:
92:
64:
124:
24:
8:
84:
172:
72:
12:
44:
88:
52:
108:
96:
104:
	.text
	.globl main
main:
	addi sp, sp, -184
	sw ra, 180(sp)
test
	li t0, 10
	la t1, n_0
	sw t0, 0(t1)
test
test
	addi t0, sp, 0
	li t1, 0
	li t2, 4
	mul t1, t1, t2
	add t0, t0, t1
	sw t0, 40(sp)
test
	li t0, 0
	lw t1, 40(sp)
	sw t0, 0(t1)
test
	addi t0, sp, 0
	li t1, 1
	li t2, 4
	mul t1, t1, t2
	add t0, t0, t1
	sw t0, 44(sp)
test
	li t0, 0
	lw t1, 44(sp)
	sw t0, 0(t1)
test
	addi t0, sp, 0
	li t1, 2
	li t2, 4
	mul t1, t1, t2
	add t0, t0, t1
	sw t0, 48(sp)
test
	li t0, 0
	lw t1, 48(sp)
	sw t0, 0(t1)
test
	addi t0, sp, 0
	li t1, 3
	li t2, 4
	mul t1, t1, t2
	add t0, t0, t1
	sw t0, 52(sp)
test
	li t0, 0
	lw t1, 52(sp)
	sw t0, 0(t1)
test
	addi t0, sp, 0
	li t1, 4
	li t2, 4
	mul t1, t1, t2
	add t0, t0, t1
	sw t0, 56(sp)
test
	li t0, 0
	lw t1, 56(sp)
	sw t0, 0(t1)
test
	addi t0, sp, 0
	li t1, 5
	li t2, 4
	mul t1, t1, t2
	add t0, t0, t1
	sw t0, 60(sp)
test
	li t0, 0
	lw t1, 60(sp)
	sw t0, 0(t1)
test
	addi t0, sp, 0
	li t1, 6
	li t2, 4
	mul t1, t1, t2
	add t0, t0, t1
	sw t0, 64(sp)
test
	li t0, 0
	lw t1, 64(sp)
	sw t0, 0(t1)
test
	addi t0, sp, 0
	li t1, 7
	li t2, 4
	mul t1, t1, t2
	add t0, t0, t1
	sw t0, 68(sp)
test
	li t0, 0
	lw t1, 68(sp)
	sw t0, 0(t1)
test
	addi t0, sp, 0
	li t1, 8
	li t2, 4
	mul t1, t1, t2
	add t0, t0, t1
	sw t0, 72(sp)
test
	li t0, 0
	lw t1, 72(sp)
	sw t0, 0(t1)
test
	addi t0, sp, 0
	li t1, 9
	li t2, 4
	mul t1, t1, t2
	add t0, t0, t1
	sw t0, 76(sp)
test
	li t0, 0
	lw t1, 76(sp)
	sw t0, 0(t1)
test
	addi t0, sp, 0
	li t1, 0
	li t2, 4
	mul t1, t1, t2
	add t0, t0, t1
	sw t0, 80(sp)
test
	li t0, 4
	lw t1, 80(sp)
	sw t0, 0(t1)
test
	addi t0, sp, 0
	li t1, 1
	li t2, 4
	mul t1, t1, t2
	add t0, t0, t1
	sw t0, 84(sp)
test
	li t0, 3
	lw t1, 84(sp)
	sw t0, 0(t1)
test
	addi t0, sp, 0
	li t1, 2
	li t2, 4
	mul t1, t1, t2
	add t0, t0, t1
	sw t0, 88(sp)
test
	li t0, 9
	lw t1, 88(sp)
	sw t0, 0(t1)
test
	addi t0, sp, 0
	li t1, 3
	li t2, 4
	mul t1, t1, t2
	add t0, t0, t1
	sw t0, 92(sp)
test
	li t0, 2
	lw t1, 92(sp)
	sw t0, 0(t1)
test
	addi t0, sp, 0
	li t1, 4
	li t2, 4
	mul t1, t1, t2
	add t0, t0, t1
	sw t0, 96(sp)
test
	li t0, 0
	lw t1, 96(sp)
	sw t0, 0(t1)
test
	addi t0, sp, 0
	li t1, 5
	li t2, 4
	mul t1, t1, t2
	add t0, t0, t1
	sw t0, 100(sp)
test
	li t0, 1
	lw t1, 100(sp)
	sw t0, 0(t1)
test
	addi t0, sp, 0
	li t1, 6
	li t2, 4
	mul t1, t1, t2
	add t0, t0, t1
	sw t0, 104(sp)
test
	li t0, 6
	lw t1, 104(sp)
	sw t0, 0(t1)
test
	addi t0, sp, 0
	li t1, 7
	li t2, 4
	mul t1, t1, t2
	add t0, t0, t1
	sw t0, 108(sp)
test
	li t0, 5
	lw t1, 108(sp)
	sw t0, 0(t1)
test
	addi t0, sp, 0
	li t1, 8
	li t2, 4
	mul t1, t1, t2
	add t0, t0, t1
	sw t0, 112(sp)
test
	li t0, 7
	lw t1, 112(sp)
	sw t0, 0(t1)
test
	addi t0, sp, 0
	li t1, 9
	li t2, 4
	mul t1, t1, t2
	add t0, t0, t1
	sw t0, 116(sp)
test
	li t0, 8
	lw t1, 116(sp)
	sw t0, 0(t1)
test
test
	addi t0, sp, 0
	li t1, 0
	li t2, 4
	mul t1, t1, t2
	add t0, t0, t1
	sw t0, 124(sp)
test
	lw a0, 124(sp)
	call bubblesort
	sw a0, 128(sp)
test
	lw t0, 128(sp)
	sw t0, 120(sp)
test
	j while_entry_3
while_entry_3:
test
	lw t0, 120(sp)
	sw t0, 132(sp)
test
	la t0, n_0
	lw t0, 0(t0)
	sw t0, 136(sp)
test
	lw t0, 132(sp)
	lw t1, 136(sp)
	slt t0, t0, t1
	sw t0, 140(sp)
test
	lw t0, 140(sp)
	bnez t0, while_body_3
	j while_end_3
while_body_3:
test
test
	lw t0, 120(sp)
	sw t0, 148(sp)
test
	addi t0, sp, 0
	lw t1, 148(sp)
	li t2, 4
	mul t1, t1, t2
	add t0, t0, t1
	sw t0, 152(sp)
test
	lw t0, 152(sp)
	lw t0, 0(t0)
	sw t0, 156(sp)
test
	lw t0, 156(sp)
	sw t0, 144(sp)
test
	lw t0, 144(sp)
	sw t0, 160(sp)
test
	lw a0, 160(sp)
	call putint
test
	li t0, 10
	sw t0, 144(sp)
test
	lw t0, 144(sp)
	sw t0, 164(sp)
test
	lw a0, 164(sp)
	call putch
test
	lw t0, 120(sp)
	sw t0, 168(sp)
test
	lw t0, 168(sp)
	li t1, 1
	add t0, t0, t1
	sw t0, 172(sp)
test
	lw t0, 172(sp)
	sw t0, 120(sp)
test
	j while_entry_3
while_end_3:
test
	li a0, 0
	lw ra, 180(sp)
	addi sp, sp, 184
	ret

172:
164:
160:
156:
144:
140:
136:
132:
128:
124:
116:
168:
112:
108:
104:
100:
96:
88:
80:
76:
72:
68:
64:
60:
152:
56:
120:
52:
148:
48:
44:
92:
40:
84:
0:

