/* (c) copyright 2025 Lawrence D. Kern ////////////////////////////////////// */

#include <unistd.h> // usleep
#include <stdio.h>

#include <stdint.h>
typedef uint8_t u8;

#define lengthof(a) (sizeof(a) / sizeof((a)[0]))

// NOTE: Pattern referenced from description at
// https://en.wikipedia.org/wiki/Rule_110

static u8 initial_row[] = {
   0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1,
   0, 0, 0, 1, 1, 1, 0, 1, 1, 1,
   0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1,

   0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1,
   1, 0, 0, 1, 1, 1, 1,
   0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1,

   0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1,
   1, 1, 1,
   0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1,
};

// NOTE: GRID_WIDTH is the length of the conceptual row we care about. The rows
// inside grid are padded with a zero on each end for the sake of neighbor
// computations. Loops over a row should range from 1 to GRID_WIDTH (inclusive).

#define GRID_WIDTH (lengthof(initial_row))
static u8 grid[2][GRID_WIDTH + 2];

static void draw_row(int row_index)
{
   char grid_tiles[] = {' ', 'Z'};

   u8 *row = grid[row_index];
   for(int index = 1; index <= GRID_WIDTH; ++index)
   {
      u8 state = row[index];
      putchar(grid_tiles[state]);
   }
   putchar('\n');
}

int main(void)
{
   puts("--------------------------");
   puts("Rule 110 Cellular Automata");
   puts("--------------------------");

   u8 pattern_values[] = {0, 1, 1, 1, 0, 1, 1, 0};

   // NOTE: Ideally we would just embed initial_row inside grid, but manually
   // padding the zeros would be kind of ugly.
   for(int index = 1; index <= GRID_WIDTH; ++index)
   {
      grid[0][index] = initial_row[index - 1];
   }

   int row_index = 0;
   while(1)
   {
      int this_index = (row_index + 0) % lengthof(grid);
      int next_index = (row_index + 1) % lengthof(grid);

      draw_row(this_index);

      u8 *this_row = grid[this_index];
      u8 *next_row = grid[next_index];

      for(int index = 1; index <= GRID_WIDTH; ++index)
      {
         u8 a = this_row[index - 1];
         u8 b = this_row[index + 0];
         u8 c = this_row[index + 1];

         u8 pattern = (a << 2) | (b << 1) | c;
         next_row[index] = pattern_values[pattern];
      }

      row_index++;
      usleep(33 * 1000);
   }

   return(0);
}
