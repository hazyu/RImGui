#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_loadso.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>

void (*loadFunc)();
void (*updateFunc)();
void (*drawFunc)(SDL_Renderer * renderer);


int main() {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    return 0;
  }

  SDL_Window * window = SDL_CreateWindow("Game", 1280, 720, SDL_WINDOW_BORDERLESS);
  if (!window) return 0;

  SDL_Renderer * renderer = SDL_CreateRenderer(window, NULL);
  if (!renderer) return 0;

  SDL_SharedObject * handle = SDL_LoadObject("./game.so");
  if (handle == nullptr) {
    SDL_Log("Failed to load lib");
    return 0;
  }
  loadFunc = (void (*)())SDL_LoadFunction(handle, "Load");
  updateFunc = (void (*)())SDL_LoadFunction(handle, "Update");
  drawFunc = (void (*)(SDL_Renderer * renderer))SDL_LoadFunction(handle, "Draw"); 

  loadFunc();

  bool running = true;
  SDL_Event event;

  while (running) {
    updateFunc();
    SDL_RenderClear(renderer);
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT) {
        running = false;
      }

      if (event.type == SDL_EVENT_KEY_DOWN) {
        if (event.key.scancode == SDL_SCANCODE_R && event.key.mod | SDL_KMOD_CTRL) {
          SDL_UnloadObject(handle);
          handle = SDL_LoadObject("./game.so");
          if (handle == nullptr) {
            SDL_Log("Failed to load lib");
            return 0;
          }
          loadFunc = (void (*)())SDL_LoadFunction(handle, "Load");
          updateFunc = (void (*)())SDL_LoadFunction(handle, "Update");
          drawFunc = (void (*)(SDL_Renderer * renderer))SDL_LoadFunction(handle, "Draw"); 
          SDL_Log("Reload");
        }
      }
    }
    drawFunc(renderer);
    SDL_RenderPresent(renderer);
  }

  return 1;
}
