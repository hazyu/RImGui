#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>

extern "C" void Load() {

}

extern "C" void Update() {

}

extern "C" void Draw(SDL_Renderer * renderer) {
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}
