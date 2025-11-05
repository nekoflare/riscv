
kernel.elf:     file format elf64-littleriscv


Disassembly of section .text:

0000000000000000 <_start>:
   0:	00005117          	auipc	sp,0x5
   4:	00010113          	mv	sp,sp
   8:	ff017113          	andi	sp,sp,-16
   c:	014000ef          	jal	20 <main>
  10:	10500073          	wfi
  14:	00100073          	ebreak
  18:	10500073          	wfi
  1c:	ffdff06f          	j	18 <_start+0x18>

0000000000000020 <main>:
  20:	ff010113          	addi	sp,sp,-16 # 4ff0 <__bss_start+0x3ff0>
  24:	00813423          	sd	s0,8(sp)
  28:	01010413          	addi	s0,sp,16
  2c:	00100793          	li	a5,1
  30:	02479793          	slli	a5,a5,0x24
  34:	04800713          	li	a4,72
  38:	00e78023          	sb	a4,0(a5)
  3c:	00100793          	li	a5,1
  40:	02479793          	slli	a5,a5,0x24
  44:	06500713          	li	a4,101
  48:	00e78023          	sb	a4,0(a5)
  4c:	00100793          	li	a5,1
  50:	02479793          	slli	a5,a5,0x24
  54:	06c00713          	li	a4,108
  58:	00e78023          	sb	a4,0(a5)
  5c:	00100793          	li	a5,1
  60:	02479793          	slli	a5,a5,0x24
  64:	06c00713          	li	a4,108
  68:	00e78023          	sb	a4,0(a5)
  6c:	00100793          	li	a5,1
  70:	02479793          	slli	a5,a5,0x24
  74:	06f00713          	li	a4,111
  78:	00e78023          	sb	a4,0(a5)
  7c:	00100793          	li	a5,1
  80:	02479793          	slli	a5,a5,0x24
  84:	02000713          	li	a4,32
  88:	00e78023          	sb	a4,0(a5)
  8c:	00100793          	li	a5,1
  90:	02479793          	slli	a5,a5,0x24
  94:	07700713          	li	a4,119
  98:	00e78023          	sb	a4,0(a5)
  9c:	00100793          	li	a5,1
  a0:	02479793          	slli	a5,a5,0x24
  a4:	06f00713          	li	a4,111
  a8:	00e78023          	sb	a4,0(a5)
  ac:	00100793          	li	a5,1
  b0:	02479793          	slli	a5,a5,0x24
  b4:	07200713          	li	a4,114
  b8:	00e78023          	sb	a4,0(a5)
  bc:	00100793          	li	a5,1
  c0:	02479793          	slli	a5,a5,0x24
  c4:	06c00713          	li	a4,108
  c8:	00e78023          	sb	a4,0(a5)
  cc:	00100793          	li	a5,1
  d0:	02479793          	slli	a5,a5,0x24
  d4:	06400713          	li	a4,100
  d8:	00e78023          	sb	a4,0(a5)
  dc:	00100793          	li	a5,1
  e0:	02479793          	slli	a5,a5,0x24
  e4:	02100713          	li	a4,33
  e8:	00e78023          	sb	a4,0(a5)
  ec:	00100793          	li	a5,1
  f0:	02479793          	slli	a5,a5,0x24
  f4:	00a00713          	li	a4,10
  f8:	00e78023          	sb	a4,0(a5)
  fc:	10500073          	wfi
 100:	ffdff06f          	j	fc <main+0xdc>
