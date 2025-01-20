/* (c) copyright 2025 Lawrence D. Kern ////////////////////////////////////// */

#include "platform.h"

// NOTE: Pattern referenced from description at
// https://en.wikipedia.org/wiki/Rule_110

static u8 pattern_values[] = {0, 1, 1, 1, 0, 1, 1, 0};
static u32 colors[] = {0x000000FF, 0xFFFFFFFF};

#define GRID_WIDTH 106
#define GRID_HEIGHT 212

static u8 grid[GRID_HEIGHT][GRID_WIDTH] = {{
      0, // NOTE: Boundary zero for neighbor computations.

      0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1,
      0, 0, 0, 1, 1, 1, 0, 1, 1, 1,
      0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1,

      0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1,
      1, 0, 0, 1, 1, 1, 1,
      0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1,

      0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1,
      1, 1, 1,
      0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1,

      0, // NOTE: Boundary zero for neighbor computations.
   }};

int main(void)
{
   int row_index = 0;

   platform_initialize("Rule 110 Cellular Automata", GRID_WIDTH, GRID_HEIGHT);
   while(platform_frame_begin())
   {
      platform_render((u8 *)grid, colors);

      int this_row_index = (row_index + 0) % GRID_HEIGHT;
      int next_row_index = (row_index + 1) % GRID_HEIGHT;

      u8 *this_row = grid[this_row_index];
      u8 *next_row = grid[next_row_index];

      for(int index = 1; index < (int)(GRID_WIDTH - 1); ++index)
      {
         u8 a = this_row[index - 1];
         u8 b = this_row[index + 0];
         u8 c = this_row[index + 1];

         u8 pattern = (a << 2) | (b << 1) | c;
         next_row[index] = pattern_values[pattern];
      }

      row_index++;

      platform_frame_end();
   }

   return(0);
}
