; Banji Lawal
; Computer Operating Systems Assignment #1
; Submission Date: 2024-01-19

;----- Assignment Description -----
; This code gives an idea of the system calls to a helloWorld program.
; I am assuming it was written in C/C++, or C# because Java and Python 
; and most other languages we use at Metro State use interpreters.


section	.text
	global _start       ;must be declared for using gcc
_start:                     ;tell linker entry point
    ; For rindirect addressing we need the array's length for the offest
	mov	edx, message_size   
	; Move the string's start address into the Extended Counter 
	mov	ecx, message    ;message to write
	; I think POSIX standard says stdout is assigned file descriptor 1
	; Stdin uses file descriptor 0
	; I'm guessing if we wanted to get input we would need a string for prompting message
	; The datatype and value we need to load into accumulator for processing
	mov	ebx, 1	    ;file descriptor (stdout)
	; I'm guessing it puts the address of sys_write on the accumulator.
	; I would have expected that in the program counter
	mov	eax, 4	    ;system call number (sys_write)
	; Call the kernel to schedule the task's run
	int	0x80        ;call kernel
	
	
	; The second call rus through the same steps with the same registers
	mov edx, exit_message_size
	mov ecx, exit_message
	mov ebx, 1
	mov eax, 4
	int 0x80
	
	; Third system call exits and 
	mov	eax, 1	    ;system call number (sys_exit)
	int	0x80        ;call kernel

section	.data

; 
message	db	'Assignment 1 for Banji Lawal',0xa	;our dear string
message_size equ	$ - message			;length of our dear string
exit_message db 'All done',0xa
exit_message_size equ $ - exit_message