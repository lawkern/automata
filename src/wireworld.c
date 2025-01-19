/* (c) copyright 2025 Lawrence D. Kern ////////////////////////////////////// */

#include "platform.h"

typedef enum {
   E,
   H,
   T,
   C,
   GRID_STATE_COUNT,
} grid_state;

static u32 colors[GRID_STATE_COUNT] = {
   [E] = 0x000000FF,
   [H] = 0x0000FFFF,
   [T] = 0xFF0000FF,
   [C] = 0xFFFF00FF,
};

#define GRID_WIDTH 16
#define GRID_HEIGHT 14
static u8 grid0[GRID_HEIGHT][GRID_WIDTH] = {
   {E},
   {E, E, E, E, E, E, E, C, C, E, E, E, E, E, E, E},
   {E, C, C, C, C, C, C, C, E, C, C, C, C, C, C, E},
   {E, C, E, E, E, E, E, C, C, E, E, E, E, E, C, E},
   {E, H, E, E, E, E, E, E, E, E, E, E, E, E, C, E},
   {E, T, E, E, E, E, E, E, E, E, E, E, E, E, C, E},
   {E, E, E, E, E, E, E, E, E, E, E, E, E, E, C, E},
   {E, C, E, E, E, E, E, E, E, E, E, E, E, E, C, E},
   {E, C, E, E, E, E, E, E, E, E, E, E, E, E, C, E},
   {E, C, E, E, E, E, E, E, E, E, E, E, E, E, C, E},
   {E, C, E, E, E, E, E, C, C, E, E, E, E, E, C, E},
   {E, C, C, C, C, C, C, C, E, C, C, C, C, C, C, E},
   {E, E, E, E, E, E, E, C, C, E, E, E, E, E, E, E},
   {E},
};
static u8 grid1[GRID_HEIGHT][GRID_WIDTH];

static u8 *grids[] = {(u8 *)grid0, (u8 *)grid1};

int main(void)
{
   int running_grid_index = 0;

   platform_initialize("Wireworld Cellular Automata", GRID_WIDTH, GRID_HEIGHT);
   while(platform_frame_begin())
   {
      int this_grid_index = (running_grid_index + 0) % lengthof(grids);
      int next_grid_index = (running_grid_index + 1) % lengthof(grids);
      running_grid_index++;

      platform_render(grids[this_grid_index], colors);

      u8 *this_grid = grids[this_grid_index];
      u8 *next_grid = grids[next_grid_index];

      for(int y = 1; y < (GRID_HEIGHT - 1); ++y)
      {
         u8 *this_grid_this_row = this_grid + (GRID_WIDTH * y);
         u8 *next_grid_this_row = next_grid + (GRID_WIDTH * y);

         u8 *this_grid_prev_row = this_grid + (GRID_WIDTH * (y - 1));
         u8 *this_grid_next_row = this_grid + (GRID_WIDTH * (y + 1));

         for(int x = 1; x < (GRID_WIDTH - 1); ++x)
         {
            u8 this_state = this_grid_this_row[x];

            switch(this_state)
            {
               case E: { next_grid_this_row[x] = E; } break; // empty -> empty
               case H: { next_grid_this_row[x] = T; } break; // head -> tail
               case T: { next_grid_this_row[x] = C; } break; // tail -> conductor
               case C: {
                  // conductor -> head iif 1 or 2 neighbors are heads
                  int neighbor_head_count =
                     (this_grid_prev_row[x - 1] == H) +
                     (this_grid_prev_row[x + 0] == H) +
                     (this_grid_prev_row[x + 1] == H) +

                     (this_grid_this_row[x - 1] == H) +
                     (this_grid_this_row[x + 1] == H) +

                     (this_grid_next_row[x - 1] == H) +
                     (this_grid_next_row[x + 0] == H) +
                     (this_grid_next_row[x + 1] == H);

                  if(neighbor_head_count == 1 || neighbor_head_count == 2)
                  {
                     next_grid_this_row[x] = H;
                  }
                  else
                  {
                     next_grid_this_row[x] = C;
                  }
               } break;
            }
         }
      }

      platform_frame_end();
   }

   return(0);
}
