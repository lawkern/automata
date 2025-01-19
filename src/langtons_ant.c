/* (c) copyright 2025 Lawrence D. Kern ////////////////////////////////////// */

#include "platform.h"
#include <stdio.h>

enum
{
   WHITE,
   BLACK,
   ANT_WHITE,
   ANT_BLACK,
   GRID_STATE_COUNT,
};

typedef enum {
   NORTH, EAST, SOUTH, WEST,
} ant_direction;

static u32 colors[GRID_STATE_COUNT] = {0xFFFFFFFF, 0x000000FF, 0xFF0000FF, 0xFF0000FF};

#define GRID_WIDTH 120
#define GRID_HEIGHT 100

static u8 grid[GRID_HEIGHT][GRID_WIDTH];

static ant_direction cw[] = {
   [NORTH] = EAST,
   [EAST] = SOUTH,
   [SOUTH] = WEST,
   [WEST] = NORTH,
};

static ant_direction ccw[] = {
   [NORTH] = WEST,
   [EAST] = NORTH,
   [SOUTH] = EAST,
   [WEST] = SOUTH,
};

int main(void)
{
   int ant_x = GRID_WIDTH / 3;
   int ant_y = GRID_HEIGHT / 3;

   grid[ant_y][ant_x] = ANT_WHITE;
   ant_direction direction = NORTH;

   platform_initialize("Langton's Ant Cellular Automata", GRID_WIDTH, GRID_HEIGHT);

   while(platform_frame_begin())
   {
      platform_render((u8 *)grid, colors);

      grid[ant_y][ant_x] -= 2;
      if(grid[ant_y][ant_x] == WHITE)
      {
         direction = cw[direction];
         grid[ant_y][ant_x] = BLACK;
      }
      else // BLACK
      {
         direction = ccw[direction];
         grid[ant_y][ant_x] = WHITE;
      }

      switch(direction)
      {
         case NORTH: { ant_y--; if(ant_y < 0)            ant_y += GRID_HEIGHT; } break;
         case SOUTH: { ant_y++; if(ant_y >= GRID_HEIGHT) ant_y -= GRID_HEIGHT; } break;
         case EAST:  { ant_x++; if(ant_x >= GRID_WIDTH)  ant_x -= GRID_WIDTH; } break;
         case WEST:  { ant_x--; if(ant_x < 0)            ant_x += GRID_WIDTH; } break;
      }
      grid[ant_y][ant_x] += 2;

      platform_frame_end();
   }

   return(0);
}
