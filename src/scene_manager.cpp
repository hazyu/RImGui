#include <scene_manager.hpp>
#include <world/world.hpp>
#include <unordered_map>

std::unordered_map<GameScenes, Scene> scenes = {};
GameScenes current;

void SceneManager::Load() {
  scenes.clear();


  Scene world = {.Load=World::Load, .Update=World::Update, .Draw=World::Draw};
  scenes[GameScenes::WORLD] = world;

  current = GameScenes::WORLD;

  scenes[current].Load();
}

void SceneManager::Update() {
  scenes[current].Update();
}

void SceneManager::Draw(SDL_Renderer * renderer) {
  scenes[current].Draw(renderer);
}
