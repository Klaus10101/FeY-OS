.set IRQ_BASE, 0x20

.section .text

.extern  _ZN15InteruptManager14handleInteruptEhj
.global _ZN15InteruptManager21IgnoreInteruptRequestEv

.macro HandleException num
.global _ZN15InteruptManager15HandleInteruptRequest\num\()Ev
 _ZN15InteruptManager15HandleInteruptRequest\num\()Ev:
    movb $\num, (interuptnumber)
    jmp int_bottom
.endm


.macro HandleInteruptRequest num
.global _ZN15InteruptManager25HandleInteruptRequest\num\()Ev
_ZN15InteruptManager25HandleInteruptRequest\num\()Ev:
    movb $\num + IRQ_BASE, (interuptnumber)
    jmp int_bottom
.endm


HandleInteruptRequest 0x00
HandleInteruptRequest 0x01
 

int_bottom:

    pusha
    pushl %ds
    pushl %es
    pushl %fs
    pushl %gs
    
    pushl %esp
    push (interuptnumber)
    call _ZN15InteruptManager14handleInteruptEhj
    
    movl %eax, %esp


    popl %gs
    popl %fs
    popl %es
    popl %ds
    popa
    
_ZN15InteruptManager21IgnoreInteruptRequestEv:
    
    iret


.data
     interuptnumber: .byte 0
     
