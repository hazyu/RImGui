#include "texture_manager.hpp"
#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <algorithm>
#include <logger.hpp>

int main() {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    LogError("Engine", "failed init");
    return 0; 
  }
  Log("Engine", "passed init");

  SDL_Window * window = SDL_CreateWindow("Game", 1280, 720, SDL_WINDOW_BORDERLESS);
  if (!window) {
    LogError("Engine", "failed window creation");
    return 0;
  }
  Log("Engine", "passed window creation");

  SDL_Renderer * renderer = SDL_CreateRenderer(window, NULL);
  if (!renderer) {
    LogError("Engine", "failed renderer creation");
    return 0;
  }
  Log("Engine", "passed renderer creation");
  SDL_SetRenderVSync(renderer, 1);

  bool running = true;
  SDL_Event event;

  SDL_Texture * rt = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 240, 160);
  if (!rt) {
    LogError("Engine", "failed render texture creation");
    return 0;
  }
  Log("Engine", "passed render texture creation");

  int scale = std::min(
    (1280 / 240),
    (720 / 160)
  );

  SDL_FRect rect = {};
  rect.w = (rt->w * scale);
  rect.h = (rt->h * scale);
  rect.x = int(1280 / 2) - (rect.w / 2);
  rect.y = int(720 / 2) - (rect.h / 2);

  TextureManager::Load(renderer);


  while (running) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT) running = false;
    }

    SDL_SetRenderTarget(renderer, rt);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderTarget(renderer, NULL);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderTexture(renderer, rt, NULL, &rect);
    SDL_RenderPresent(renderer);
  }

  TextureManager::Unload();

  SDL_DestroyRenderer(renderer);
  Log("Engine", "renderer destroyed");
  SDL_DestroyWindow(window);
  Log("Engine", "window destroyed");
  return 1;
}
