# 🧠 Operating System Development (x86 From Scratch)

<p align="center">
  <img src="C:\Users\Justin Thomas\OneDrive\รูปภาพ\Screenshot 2025-07-08 211322.png" alt="QEMU boot screen" width="500"/>
</p>

A bootable x86 operating system built entirely from scratch using **C**, **Assembly**, and a **custom cross-toolchain**.  
Includes a BIOS-based bootloader, FAT12 filesystem reader, VGA text output, and QEMU virtualization support.

> **Maintainer**: Justin Thomas

---

## 📌 Project Overview

This is a personal educational project by Justin Thomas to explore the fundamentals of operating system development and low-level x86 systems programming. The operating system runs in QEMU (or real hardware) and is designed to be minimal but functional, featuring a handcrafted bootloader, FAT12 support, a C runtime, and text-based VGA output.

---

## 🛠️ Features Implemented So Far

| Feature                  | Description                                                                 |
|--------------------------|-----------------------------------------------------------------------------|
| **Bootloader**           | 16-bit real mode bootloader using BIOS interrupts for disk I/O             |
| **Disk Reading (INT 13h)** | Sector-based disk access via LBA using BIOS interrupt `0x13`               |
| **FAT12 Filesystem**     | FAT12 support with file loading and directory traversal                     |
| **Subdirectory Support** | Handles nested directories in FAT12                                         |
| **Custom `printf()`**    | Lightweight implementation using `va_list` and varargs                      |
| **VGA Text Output**      | Writes text directly to `0xB8000` using memory-mapped VGA                   |
| **C Kernel**             | Kernel is bootstrapped in C for higher-level logic                          |
| **Build Automation**     | Full build pipeline using **SCons**                                         |
| **QEMU Integration**     | Generates bootable raw disk image for QEMU testing                          |

---

## 📂 Directory Structure

```plaintext
├── bootloader/      # Assembly code for the 16-bit bootloader
├── kernel/          # C-based kernel source code
├── fs/              # FAT12 filesystem parsing utilities
├── libs/            # Custom lightweight libc implementations (e.g., stdio, string)
├── toolchain/       # Toolchain setup scripts and compiler configs
├── build/           # Output binaries, images, and temporary files
├── image/           # SCons disk formatting & integration helpers
├── scripts/         # Run scripts and utilities (e.g., run.sh)
├── sconstruct       # Entry point for SCons build system
└── README.md        # This file
```

---

## ⚙️ Development Environment

- **OS**: Ubuntu (via WSL on Windows)
- **Toolchain**: `i686-elf-gcc` cross-compiler
- **Emulator**: QEMU
- **Disk Tools**: `libguestfs`, `supermin`
- **Build System**: SCons

---

## 🧪 Toolchain Setup & Usage

### 🛠️ Set Up Cross-Compiler Toolchain
```bash
cd toolchain
bash setup.sh
```

### 🏗️ Build the OS
```bash
scons
```

### 🚀 Run in QEMU
```bash
sudo ./scripts/run.sh disk build/i686_debug/image.img
```

---

## 🧠 Key Concepts Demonstrated

- Writing a bootloader with BIOS interrupts (`INT 13h`, `INT 10h`)
- Understanding real-mode memory layout and bootstrapping
- Parsing the FAT12 filesystem and loading files from disk
- Direct VGA memory manipulation at `0xB8000`
- Implementing `printf()` with `va_list` in a freestanding C environment
- Running a no-libc kernel in 16-bit → C environment
- Building a raw disk image with `libguestfs`
- Using QEMU to emulate a real x86 PC environment

---

## 🎯 Planned Features / Roadmap

- ⌨️ PS/2 keyboard input support  
- 🐚 Basic shell / command-line interface  
- 🧠 Memory management (segmentation + paging)  
- 🛡️ Switch to 32-bit protected mode  
- 🔁 Cooperative multitasking and basic process management  

---

## 📝 License

This project is developed and maintained by **Justin Thomas** strictly for educational purposes.  
All assets and code are open for learning, experimentation, and feedback.

---

## 🔍 Credits & Inspiration

This project is inspired by the amazing OSDev wiki, blogs, and tutorials from the systems programming community.  
A huge thanks to all contributors, educators, and developers who document their knowledge and make operating system development approachable.

---

## ✅ Next Steps for GitHub

1. Save this file as `README.md` in your root directory.
2. Add a screenshot as `screenshot.png` for the QEMU preview.
3. Set your GitHub repo description to something like:
   > "A hobby x86 OS built from scratch in C & Assembly — custom bootloader, FAT12, VGA, QEMU-ready."

---