#pragma once

#include "../../engine/scene/scene.h"


namespace game::scene {

class GameScene : public engine::scene::Scene {
public:

    GameScene(std::string_view name, engine::core::Context& context, engine::scene::SceneManager& scene_manager);
    ~GameScene();

    void init() override;
    void clean() override;

private:
    void onAttack();
    void onJump();
};


}