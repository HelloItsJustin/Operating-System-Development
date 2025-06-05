
# 🧠 Operating System Development

Welcome to my custom operating system development project. This project is a hands-on exploration of low-level systems programming, focusing on creating a minimal yet functional operating system from scratch using Assembly, C, and x86 architecture fundamentals.

> **Project Maintainer**: Justin Thomas

---

## 📌 Project Overview

This project is an educational endeavor where I (Justin Thomas) build an operating system step-by-step. The goal is to understand how modern operating systems work under the hood by building each component from the ground up.

---

## 🛠️ Features Implemented So Far

| Feature                         | Description                                                                 |
|-------------------------------|-----------------------------------------------------------------------------|
| Bootloader                     | A custom bootloader that displays a message using BIOS interrupts.         |
| Disk Reading                   | Ability to read sectors from disk using INT 13h.                            |
| FAT12 Filesystem Support       | Basic FAT file reading and directory traversal support.                     |
| printf Implementation          | A lightweight custom `printf()` function using variable arguments.          |
| Kernel in C                    | Transition from Assembly to C for writing kernel-level code.                |
| Subdirectory Navigation        | Added support for FAT12 subdirectories within the OS.                       |

---

## 📂 Directory Structure

```
├── bootloader/           # Bootloader code in Assembly
├── kernel/               # C-based kernel code
├── lib/                  # Custom libraries like stdio
├── fs/                   # File system interaction (FAT12)
├── build/                # Output ISO or binaries
├── toolchain/            # Cross compiler setup
├── sconstruct            # SCons build script
├── .gitattributes        # Git LFS configuration (if needed)
└── README.md             # This file
```

---

## ⚙️ Development Environment

- **Operating System**: WSL (Ubuntu on Windows)
- **Toolchain**: Custom x86-elf GCC cross compiler
- **Emulator**: QEMU
- **Build System**: SCons

To set up the toolchain:
```bash
cd toolchain
bash setup.sh
```

To build the OS:
```bash
scons
```

To run in QEMU:
```bash
qemu-system-i386 -cdrom build/os.iso
```

---

## 🧪 What I’m Learning

- Assembly-level system initialization (16-bit real mode)
- Sector reading using BIOS
- Bootloader design and memory map layout
- File system implementation (FAT12)
- Writing low-level drivers and interfaces in C
- Kernel structure and design principles
- Creating and linking binaries for bare-metal environments

---

## ✅ Future Goals

- Implement keyboard input handling
- Develop a basic shell interface
- Add a memory manager (paging and segmentation)
- Transition to 32-bit protected mode
- Introduce multitasking and process control

---

## 📝 License

This project is created and maintained by **Justin Thomas** for educational purposes.