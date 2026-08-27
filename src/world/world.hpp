#pragma once

#include <SDL3/SDL_render.h>

namespace World {
  void Load();
  void Update();
  void Draw(SDL_Renderer *);
}
