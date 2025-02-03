/* (c) copyright 2025 Lawrence D. Kern ////////////////////////////////////// */

    .global main

    .equ E, 0
    .equ H, 1
    .equ T, 2
    .equ C, 3

    .equ GRID_WIDTH, 16
    .equ GRID_HEIGHT, 14

/* ////////////////////////////////////////////////////////////////////////// */
    .section .text

main:
    str x30, [sp, -16]!

    ldr x20, 0 // Running grid index.

    ldr x0, =title
    mov x1, GRID_WIDTH
    mov x2, GRID_HEIGHT
    bl platform_initialize

.main.frame_begin:
    bl platform_frame_begin
    cbz x0, .main.end

    ldr x0, =grid0
    ldr x1, =colors
    bl  platform_render

    bl platform_frame_end
    b .main.frame_begin

.main.end:
    ldr x30, [sp], 16
    mov x0, xzr
    ret

/* ////////////////////////////////////////////////////////////////////////// */
    .section .data

title:
    .asciz "Wireworld Cellular Automata"

colors:
    .4byte 0x000000FF, 0x0000FFFF, 0xFF0000FF, 0xFFFF00FF

grid0:
    .byte E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E
    .byte E, E, E, E, E, E, E, C, C, E, E, E, E, E, E, E
    .byte E, C, C, C, C, C, C, C, E, C, C, C, C, C, C, E
    .byte E, C, E, E, E, E, E, C, C, E, E, E, E, E, C, E
    .byte E, H, E, E, E, E, E, E, E, E, E, E, E, E, C, E
    .byte E, T, E, E, E, E, E, E, E, E, E, E, E, E, C, E
    .byte E, E, E, E, E, E, E, E, E, E, E, E, E, E, C, E
    .byte E, C, E, E, E, E, E, E, E, E, E, E, E, E, C, E
    .byte E, C, E, E, E, E, E, E, E, E, E, E, E, E, C, E
    .byte E, C, E, E, E, E, E, E, E, E, E, E, E, E, C, E
    .byte E, C, E, E, E, E, E, C, C, E, E, E, E, E, C, E
    .byte E, C, C, C, C, C, C, C, E, C, C, C, C, C, C, E
    .byte E, E, E, E, E, E, E, C, C, E, E, E, E, E, E, E
    .byte E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E

grid1:
    .byte E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E
    .byte E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E
    .byte E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E
    .byte E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E
    .byte E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E
    .byte E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E
    .byte E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E
    .byte E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E
    .byte E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E
    .byte E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E
    .byte E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E
    .byte E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E
    .byte E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E
    .byte E, E, E, E, E, E, E, E, E, E, E, E, E, E, E, E
