/* (c) copyright 2025 Lawrence D. Kern ////////////////////////////////////// */

#include <stdbool.h>
#include <stdint.h>
typedef uint8_t u8;
typedef uint32_t u32;

#define lengthof(a) (sizeof(a) / sizeof((a)[0]))

#define PLATFORM_INITIALIZE(name) void name(char *title, int grid_width, int grid_height)
PLATFORM_INITIALIZE(platform_initialize);

#define PLATFORM_FRAME_BEGIN(name) bool name(void)
PLATFORM_FRAME_BEGIN(platform_frame_begin);

#define PLATFORM_RENDER(name) void name(u8 *grid, u32 *colors)
PLATFORM_RENDER(platform_render);

#define PLATFORM_FRAME_END(name) void name(void)
PLATFORM_FRAME_END(platform_frame_end);
