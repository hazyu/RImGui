#pragma once

#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>

namespace Engine {
  bool Init();
  SDL_Window * GetWindow();
  SDL_Renderer * GetRender();
}
