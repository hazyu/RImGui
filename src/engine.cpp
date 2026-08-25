#include <SDL3/SDL_render.h>
#include <engine.hpp>
#include <logger.hpp>
#include <SDL3/SDL.h>

SDL_Window * window = nullptr;
SDL_Renderer * renderer = nullptr;

bool Engine::Init() {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    LogError("Engine failed init");
    return false;
  }

  window = SDL_CreateWindow("Game", 128, 128, SDL_WINDOW_BORDERLESS);
  if (window == nullptr) {
    LogError("Engine failed window creation");
    return false;
  }

  renderer = SDL_CreateRenderer(window, NULL);
  if (renderer == nullptr) {
    LogError("Engine failed renderer creation");
    return false;
  }

  if (!SDL_SetRenderVSync(renderer, 1)) {
    LogError("Engine failed vsync");
    return false;
  }

  
  return true;
}
