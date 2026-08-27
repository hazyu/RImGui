#include <logger.hpp>
#include <texture_manager.hpp>
#include <filesystem>
#include <unordered_map>
#include <SDL3_image/SDL_image.h>

std::unordered_map<std::string, SDL_Texture * > textures = {};


void TextureManager::Load(SDL_Renderer * renderer) {
  textures.clear();

  for (const auto& entry : std::filesystem::recursive_directory_iterator("art")) {
    if (entry.is_regular_file() && entry.path().extension() == ".png") {
      SDL_Texture * texture = IMG_LoadTexture(renderer, entry.path().c_str());
      if (!texture) {
        LogError("Texture Manager", "Failed to load texture ", entry.path().c_str());
      }
      auto rel = std::filesystem::relative(entry.path(), "./art");
      textures[rel] = texture;
      Log("Texture Manager", "Loaded texture ", rel);
    }
  }
}

void TextureManager::Unload() {
  for (const auto& texture : textures) {
    SDL_DestroyTexture(texture.second);
    Log("Texture Manger", texture.first, " destroyed");
  }
}
