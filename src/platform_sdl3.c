/* (c) copyright 2025 Lawrence D. Kern ////////////////////////////////////// */

#include "SDL3/SDL.h"
#include "platform.h"

#include <stdlib.h>

struct {
   int width;
   int height;
   int pitch;
   u32 *pixels;
} backbuffer;

struct {
   SDL_Window *window;
   SDL_Renderer *renderer;
   SDL_Texture *texture;
} sdl3;

PLATFORM_INITIALIZE(platform_initialize)
{
   backbuffer.width  = grid_width;
   backbuffer.height = grid_height;
   backbuffer.pitch  = backbuffer.width * sizeof(*backbuffer.pixels);
   backbuffer.pixels = SDL_calloc(1, backbuffer.height * backbuffer.pitch);

   if(!SDL_Init(SDL_INIT_VIDEO))
   {
      SDL_Log("ERROR: Failed to initialize SDL3.");
      exit(1);
   }

   int window_width = grid_width * 4;
   int window_height = grid_height * 4;

   if(!SDL_CreateWindowAndRenderer(title, window_width, window_height, 0, &sdl3.window, &sdl3.renderer))
   {
      SDL_Log("ERROR: Failed to create window/renderer.");
      exit(1);
   }

   if(!SDL_SetRenderVSync(sdl3.renderer, 1))
   {
      SDL_Log("WARNING: Failed to set vsync.");
   }

   if(!SDL_SetRenderLogicalPresentation(sdl3.renderer, grid_width, grid_height, SDL_LOGICAL_PRESENTATION_INTEGER_SCALE))
   {
      SDL_Log("WARNING: Failed to set render logical presentation.");
   }

   sdl3.texture = SDL_CreateTexture(sdl3.renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, grid_width, grid_height);
   if(!sdl3.texture)
   {
      SDL_Log("ERROR: Failed to create texture.");
      exit(1);
   }

   if(!SDL_SetTextureScaleMode(sdl3.texture, SDL_SCALEMODE_NEAREST))
   {
      SDL_Log("WARNING: Failed to set vsync.");
   }
}

void sdl3_toggle_fullscreen(SDL_Window *window)
{
   int already_fullscreen = (SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN);
   SDL_SetWindowFullscreen(sdl3.window, !already_fullscreen);
}

PLATFORM_PROCESS_INPUT(platform_process_input)
{
   bool keep_running = true;

   SDL_Event event;
   while(SDL_PollEvent(&event))
   {
      switch(event.type)
      {
         case SDL_EVENT_QUIT: {
            keep_running = false;
         } break;

         case SDL_EVENT_KEY_UP:
         case SDL_EVENT_KEY_DOWN:
         {
            bool pressed = event.key.down;
            bool repeated = event.key.repeat;

            if(pressed && !repeated)
            {
               switch(event.key.key)
               {
                  case SDLK_ESCAPE: {
                     keep_running = false;
                  } break;

                  case SDLK_F: {
                     sdl3_toggle_fullscreen(sdl3.window);
                  } break;
               }
            }
         } break;
      }
   }

   return(keep_running);
}

PLATFORM_RENDER(platform_render)
{
   SDL_SetRenderDrawColor(sdl3.renderer, 32, 32, 64, 255);
   SDL_RenderClear(sdl3.renderer);

   for(int index = 0; index < (backbuffer.width * backbuffer.height); ++index)
   {
      u8 state = grid[index];
      backbuffer.pixels[index] = colors[state];
   }

   SDL_UpdateTexture(sdl3.texture, 0, backbuffer.pixels, backbuffer.pitch);
   SDL_RenderTexture(sdl3.renderer, sdl3.texture, 0, 0);

   SDL_RenderPresent(sdl3.renderer);
}

PLATFORM_FRAME_END(platform_frame_end)
{
   SDL_Delay(33);
}
