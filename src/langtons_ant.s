/* (c) copyright 2025 Lawrence D. Kern ////////////////////////////////////// */

    .global main

    .equ WHITE,     0
    .equ BLACK,     1
    .equ ANT_WHITE, 2
    .equ ANT_BLACK, 3

    .equ NORTH, 0
    .equ EAST,  1
    .equ SOUTH, 2
    .equ WEST,  3

    .equ GRID_WIDTH, 120
    .equ GRID_HEIGHT, 100

/* ////////////////////////////////////////////////////////////////////////// */
    .section .text

main:
    str x30, [sp, -16]!

    mov x0, ANT_WHITE
    ldr x1, =grid
    str x0, [x1]

    ldr x0, =title
    mov x1, GRID_WIDTH
    mov x2, GRID_HEIGHT
    bl platform_initialize

.main.frame_begin:
    bl platform_frame_begin
    cbz x0, .main.end

    ldr x0, =grid
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
    .asciz "Langton's Ant Cellular Automata"

colors:
    .4byte 0xFFFFFFFF, 0x000000FF, 0xFF0000FF, 0xFF0000FF

grid:
    .zero (GRID_WIDTH * GRID_HEIGHT)
