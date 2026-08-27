#pragma once

#include <SDL3/SDL_render.h>
#include <string>
namespace TextureManager {
  void Load(SDL_Renderer * renderer);
  void Unload();
  SDL_Texture * GetTexture(std::string name);
}
