#!/bin/bash
set -e

CC=riscv64-unknown-elf-gcc
LD=riscv64-unknown-elf-ld
OBJDUMP=riscv64-unknown-elf-objdump
OBJCOPY=riscv64-unknown-elf-objcopy

SRC_C=main.c
SRC_S=entry.S

OUT_ELF=kernel.elf
OUT_BIN=kernel.bin

$CC -march=rv64ima -mabi=lp64 -ffreestanding -nostdlib -c $SRC_C -o main.o
$CC -march=rv64ima -mabi=lp64 -ffreestanding -nostdlib -c $SRC_S -o entry.o

$LD -T linker.ld -nostdlib -o $OUT_ELF entry.o main.o

$OBJCOPY -O binary $OUT_ELF $OUT_BIN

$OBJDUMP -d $OUT_ELF > kernel.asm

echo "Build complete:"
echo " - ELF: $OUT_ELF"
echo " - BIN: $OUT_BIN"
echo " - Disasm: kernel.asm"
