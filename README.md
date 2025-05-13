
# FeY-OS  


FeY-OS is a minimal operating system that boots from GRUB:  
 ![License](https://img.shields.io/badge/license-BSD-green.svg)
 ![x86](https://img.shields.io/badge/architecture-x86-blue.svg)
 ![32-bit](https://img.shields.io/badge/architecture-32--bit-blue.svg)



## 🔥 Focus: Building a Minimal x86 (32-bit) Operating System  
The goal of FeY-OS is to create a **lightweight, minimalistic operating system** with core functionality, including: 

 
- Be able to **dual boot with any existing OS**
- A simple **networking interface**  
- To impliment  ** A web engine without javascript **  
- Basic **GUI** (planned)  
- Support for **user-space applications** (future goal)  


## For now:
- A simple **kernel written in C++**  
- Booting via **GRUB** 
- Basic **Interupts** 
- Basic **system calls and I/O handling** (planned)  


## 🚧 Status: Work in Progress  
- [x] Basic bootloader setup with GRUB  
- [x] Simple kernel that prints a message  
- [ ] Implementing system calls  
- [ ] Adding keyboard input support  
- [ ] Expanding the kernel functionality  

## 📥 Prebuilt ISO  
A prebuilt ISO is available in th repo.  

## 🛠️ Building From Source  

### **Dependencies**  
To build FeY-OS, you need the following packages:  
- **GCC (32-bit cross-compiler for x86)**  
- **LD (GNU Linker for x86 32-bit)**  
- **Make** (to automate the build process)  
- **GRUB** (for bootloader setup)  
- **xorriso** (for ISO generation)  
- **GASM** (for assembly code)  

#### **Installing Dependencies (Debian-based systems)**  
Run the following command to install all required dependencies:  
```sh
sudo apt update && sudo apt install build-essential grub-pc-bin xorriso nasm gcc-multilib
```
#### Build Instructions

To build Fey-OS in the project directory, simply run:
```
make feykernel.iso
```
This will generate feykernel.iso, which can be booted using an emulator like QEMU:
```
qemu-system-i386 -cdrom feykernel.iso
```

or you can use virtual box.
