;;; (c) copyright 2025 Lawrence D. Kern ///////////////////////////////////// */

    global main
    extern platform_initialize
    extern platform_frame_begin
    extern platform_render
    extern platform_frame_end

    GRID_WIDTH  equ 106
    GRID_HEIGHT equ 212

;;; ///////////////////////////////////////////////////////////////////////// */
    section .text

main:
    push rbp
    mov rbp, rsp

    mov rdi, title
    mov esi, GRID_WIDTH
    mov edx, GRID_HEIGHT
    call platform_initialize

    .frame_begin:
    call platform_frame_begin
    cmp eax, 0
    je .end

    mov rdi, grid
    mov rsi, colors
    call platform_render

    call platform_frame_end
    jmp .frame_begin

    .end:

    pop rbp
    xor eax, eax
    ret

;;; ///////////////////////////////////////////////////////////////////////// */
    section .rodata

title:
    db "Rule 110 Cellular Automata", 0

pattern_values:
    db 0, 1, 1, 1, 0, 1, 1, 0

colors:
    dd 0x000000FF, 0xFFFFFFFF

grid:
    db 0 ;; NOTE: Boundary zero for neighbor computations.

    db 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1
    db 0, 0, 0, 1, 1, 1, 0, 1, 1, 1
    db 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1

    db 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1
    db 1, 0, 0, 1, 1, 1, 1
    db 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1

    db 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1
    db 1, 1, 1
    db 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1

    db 0 ;; NOTE: Boundary zero for neighbor computations.

    ;; NOTE: Uncomment the line below to pad the remaining space in first
    ;; row. This is only necessary if the initial pattern changes and we don't
    ;; want to determine GRID_WIDTH programmatically. Note that it won't help
    ;; the case where GRID_WIDTH is too small.

    ;; times GRID_WIDTH - (. - grid) db 0

    times GRID_WIDTH * (GRID_HEIGHT - 1) db 0
