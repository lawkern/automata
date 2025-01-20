/* (c) copyright 2025 Lawrence D. Kern ////////////////////////////////////// */

    .global main

    .equ GRID_WIDTH, 106
    .equ GRID_HEIGHT, 212

/* ////////////////////////////////////////////////////////////////////////// */
    .section .text

main:
    str x30, [sp, -16]!

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
    .asciz "Rule 110 Cellular Automata"

pattern_values:
    .byte 0, 1, 1, 1, 0, 1, 1, 0

colors:
    .4byte 0x000000FF, 0xFFFFFFFF

grid:
    .byte 0 // NOTE: Boundary zero for neighbor computations.

    .byte 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1
    .byte 0, 0, 0, 1, 1, 1, 0, 1, 1, 1
    .byte 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1

    .byte 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1
    .byte 1, 0, 0, 1, 1, 1, 1
    .byte 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1

    .byte 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1
    .byte 1, 1, 1
    .byte 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1

    .byte 0 // NOTE: Boundary zero for neighbor computations.

    // NOTE: Uncomment the line below to pad the remaining space in first
    // row. This is only necessary if the initial pattern changes and we don't
    // want to determine GRID_WIDTH programmatically. Note that it won't help
    // the case where GRID_WIDTH is too small.

    // .zero GRID_WIDTH - (. - grid)

    .zero GRID_WIDTH * (GRID_HEIGHT - 1)
