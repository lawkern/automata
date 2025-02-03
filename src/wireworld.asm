;; (c) copyright 2025 Lawrence D. Kern ////////////////////////////////////// */

global main
extern platform_initialize
extern platform_frame_begin
extern platform_render
extern platform_frame_end

   E equ 0
   H equ 1
   T equ 2
   C equ 3

   GRID_WIDTH  equ 16
   GRID_HEIGHT equ 14

;; ////////////////////////////////////////////////////////////////////////// */
section .text

main:
   push rbp
   mov rbp, rsp

   mov r12, 0                   ; Running grid index.

   mov rdi, title
   mov esi, GRID_WIDTH
   mov edx, GRID_HEIGHT
   call platform_initialize

.frame_begin:
   call platform_frame_begin
   cmp eax, 0
   je .end

   mov rdi, grid0
   mov rsi, colors
   call platform_render

   call platform_frame_end
   jmp .frame_begin

.end:

   pop rbp
   xor eax, eax
   ret

;; ////////////////////////////////////////////////////////////////////////// */
section .rodata

title:
   db "Wireworld Cellular Automata", 0

colors:
   dd 0x000000FF, 0x0000FFFF, 0xFF0000FF, 0xFFFF00FF

grid0:
    db E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E
    db E, E, E, E, E, E, E, C, C, E, E, E, E, E, E, E
    db E, C, C, C, C, C, C, C, E, C, C, C, C, C, C, E
    db E, C, E, E, E, E, E, C, C, E, E, E, E, E, C, E
    db E, H, E, E, E, E, E, E, E, E, E, E, E, E, C, E
    db E, T, E, E, E, E, E, E, E, E, E, E, E, E, C, E
    db E, E, E, E, E, E, E, E, E, E, E, E, E, E, C, E
    db E, C, E, E, E, E, E, E, E, E, E, E, E, E, C, E
    db E, C, E, E, E, E, E, E, E, E, E, E, E, E, C, E
    db E, C, E, E, E, E, E, E, E, E, E, E, E, E, C, E
    db E, C, E, E, E, E, E, C, C, E, E, E, E, E, C, E
    db E, C, C, C, C, C, C, C, E, C, C, C, C, C, C, E
    db E, E, E, E, E, E, E, C, C, E, E, E, E, E, E, E
    db E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E

grid1:
    db E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E
    db E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E
    db E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E
    db E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E
    db E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E
    db E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E
    db E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E
    db E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E
    db E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E
    db E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E
    db E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E
    db E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E
    db E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E
    db E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E
