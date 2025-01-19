/* (c) copyright 2025 Lawrence D. Kern ////////////////////////////////////// */

#include <stdbool.h>
#include <stdint.h>

typedef uint8_t u8;
typedef uint32_t u32;

#define lengthof(a) (sizeof(a) / sizeof((a)[0]))

// NOTE: Perform any initialization required by the platform, e.g. creating a
// window, allocating textures, etc.
#define PLATFORM_INITIALIZE(name) void name(char *title, int grid_width, int grid_height)
PLATFORM_INITIALIZE(platform_initialize);

// NOTE: Perform any actions that should occur at the beginning of each frame,
// e.g handling input and other incoming OS events. Return false to indicate the
// program should quit. The caller can use that value to terminate main.
#define PLATFORM_FRAME_BEGIN(name) bool name(void)
PLATFORM_FRAME_BEGIN(platform_frame_begin);

// NOTE: Render the cell grid with the provided palette of colors. It is
// currently up to the platform to remember the grid dimensions provided during
// initialization. The colors array is indexed by the possible values of each
// grid cell. It is up to the caller to ensure grid values are not out of range
// for the colors array.
#define PLATFORM_RENDER(name) void name(u8 *grid, u32 *colors)
PLATFORM_RENDER(platform_render);

// NOTE: Perform any actions that should occur at the end of each frame,
// e.g. frame time computations.
#define PLATFORM_FRAME_END(name) void name(void)
PLATFORM_FRAME_END(platform_frame_end);
