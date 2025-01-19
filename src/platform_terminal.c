/* (c) copyright 2025 Lawrence D. Kern ////////////////////////////////////// */

#include <unistd.h> // usleep
#include <stdio.h>

#include "platform.h"

struct {
   int width;
   int height;
   int pitch;
} terminal;

PLATFORM_INITIALIZE(platform_initialize)
{
   puts(title);
   puts("--");

   terminal.width  = grid_width;
   terminal.height = grid_height;
   terminal.pitch  = terminal.width * sizeof(char);
}

PLATFORM_FRAME_BEGIN(platform_frame_begin)
{
   bool keep_running = true;
   return(keep_running);
}

PLATFORM_RENDER(platform_render)
{
   (void)colors;

   for(int y = 0; y < terminal.height; ++y)
   {
      u8 *row = grid + (terminal.pitch * y);

      for(int x = 0; x < terminal.width; ++x)
      {
         u8 state = row[x];
         putchar('0' + state);
      }
      putchar('\n');
   }
   putchar('\n');
}

PLATFORM_FRAME_END(platform_frame_end)
{
   usleep(33 * 1000 * 10);
}
