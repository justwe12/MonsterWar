#include "game_scene.h"

#include "../../engine/core/context.h"
#include "../../engine/input/input_manager.h"
#include "../../engine/utils/events.h"
#include <entt/signal/dispatcher.hpp>

#include <spdlog/spdlog.h>


namespace game::scene {

GameScene::GameScene(std::string_view name, engine::core::Context& context, engine::scene::SceneManager& scene_manager)
: engine::scene::Scene(name, context, scene_manager)
{

}

GameScene::~GameScene()
{
}
void GameScene::init()
{
    auto &input_manager = context_.getInputManager();
    input_manager.onAction("attack").connect<&GameScene::onAttack>(this); // TODO: fix lambda
    input_manager.onAction("jump", engine::input::ActionState::RELEASED).connect<&GameScene::onJump>(this);

}
void GameScene::clean()
{
    auto &input_manager = context_.getInputManager();
    input_manager.onAction("attack").disconnect<&GameScene::onAttack>(this); // TODO: fix lambda
    input_manager.onAction("jump", engine::input::ActionState::RELEASED).disconnect<&GameScene::onJump>(this);
}
void GameScene::onAttack()
{
    spdlog::info("Attack action triggered!");

    context_.getDispatcher().enqueue<engine::utils::QuitEvent>(); // 触发退出事件，测试事件系统
}
void GameScene::onJump()
{
    spdlog::info("Jump action triggered!");
}
}