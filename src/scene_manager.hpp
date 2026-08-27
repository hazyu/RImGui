#pragma once

#include <functional>
#include <SDL3/SDL_render.h>

struct Scene {
  std::function<void()> Load;
  std::function<void()> Update;
  std::function<void(SDL_Renderer *)> Draw;
};

enum class GameScenes {
  WORLD
};

namespace SceneManager {
  void Load();
  void Update();
  void Draw(SDL_Renderer * );
  void ChangeScene(GameScenes scene);
}
