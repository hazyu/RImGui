#include <logger.hpp>
#include <iostream>
#include <SDL3/SDL_error.h>

void LogError(std::string text) {
  std::cout << text << ": " <<  SDL_GetError();
}
