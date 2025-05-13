.set MAGIC, 0x1badb002  # so that grub excepts it as a kernel
.set FLAGS, (1<<0 | 1<<1)
.set CHECKSUM, -(MAGIC + FLAGS)

.section .multiboot
	.long MAGIC
	.long FLAGS
	.long CHECKSUM

.section .text
.extern FeyKernelMain
# .extern callConstructors
.global loader

loader:
	mov $kernel_stack, %esp

	# call callConstructors
	
	push %eax
	push %ebx
	call FeyKernelMain

_stop:
	cli
	hlt
	jmp _stop


.section .bss:
.space 2*1024*1024;  #2 	Mib

kernel_stack:
