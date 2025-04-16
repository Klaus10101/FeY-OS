GCCPARAMS = -m32 -fno-use-cxa-atexit  -nostdlib  -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore
ASPARAMS  = --32
LDPARAMS  = -melf32_i386

# GCCPARAMS = -m64
# ASPARAMS = --64
# LDPARAMS = -melfx86_64

objects   = loader.o gdt.o port.o interupts.o interuptstubs.o kernel.o

%.o: src/%.cpp
	gcc $(GCCPARAMS) -o $@ -c $<

%.o: src/%.s
	as $(ASPARAMS) -o $@ $<

feykernel.bin: linker.ld $(objects)
	ld$( LDPARAMS) -T $< -o $@ $(objects)


feykernel.iso: feykernel.bin
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	cp $< iso/boot/
	echo 'set timeout=0' >> iso/boot/grub/grub.cfg
	echo 'set default-0' >> iso/boot/grub/grub.cfg
	echo '' >> iso/boot/grub/grub.cfg
	echo 'menuentry "fey-os" {' >> iso/boot/grub/grub.cfg
	echo ' multiboot /boot/feykernel.bin' >> iso/boot/grub/grub.cfg
	echo ' boot' >> iso/boot/grub/grub.cfg
	echo '}' >> iso/boot/grub/grub.cfg
	grub-mkrescue --output=$@ iso
	

clean:
	rm -rf iso feykernel.bin $(objects)

clean-iso: clean
	rm -rf feykernel.iso    
