#include "game_scene.h"

#include "../../engine/core/context.h"
#include "../../engine/input/input_manager.h"
#include "../../engine/utils/events.h"
#include <entt/signal/dispatcher.hpp>

#include <spdlog/spdlog.h>
#include "../../engine/audio/audio_player.h"
#include "../../engine/resource/resource_manager.h"
#include "../../engine/render/text_renderer.h"
#include "../../engine/ui/ui_manager.h"
#include "../../engine/ui/ui_image.h"
#include "../../engine/ui/ui_label.h"
#include <entt/core/hashed_string.hpp>

using namespace entt::literals;

namespace game::scene {

GameScene::GameScene(engine::core::Context& context)
    : engine::scene::Scene("GameScene", context) {
}

GameScene::~GameScene() {
}
void GameScene::init()
{
    // auto &input_manager = context_.getInputManager();
    // input_manager.onAction("attack").connect<&GameScene::onAttack>(this); // TODO: fix lambda
    // input_manager.onAction("jump", engine::input::ActionState::RELEASED).connect<&GameScene::onJump>(this);
	testResourceManager();
	Scene::init();
    static int count = 0;
    scene_num_ = count++;

    // auto &input_manager = context_.getInputManager();
    // input_manager.onAction("jump").connect<&GameScene::onReplace>(this); // TODO: fix lambda
    // input_manager.onAction("mouse_left").connect<&GameScene::onPush>(this);
    // input_manager.onAction("mouse_right").connect<&GameScene::onPop>(this);
    // input_manager.onAction("pause").connect<&GameScene::onQuit>(this);

}
void GameScene::clean()
{
    auto &input_manager = context_.getInputManager();
    // input_manager.onAction("attack").disconnect<&GameScene::onAttack>(this); // TODO: fix lambda
    // input_manager.onAction("jump", engine::input::ActionState::RELEASED).disconnect<&GameScene::onJump>(this);

    // input_manager.onAction("jump").disconnect<&GameScene::onReplace>(this); // TODO: fix lambda
    // input_manager.onAction("mouse_left").disconnect<&GameScene::onPush>(this);
    // input_manager.onAction("mouse_right").disconnect<&GameScene::onPop>(this);
    // input_manager.onAction("pause").disconnect<&GameScene::onQuit>(this);
	
	Scene::clean();
}

void GameScene::testResourceManager() {
    // 载入资源
    context_.getResourceManager().loadTexture("assets/textures/Buildings/Castle.png"_hs);
    // 播放音乐
    context_.getAudioPlayer().playMusic("battle_bgm"_hs);
    
    // 测试UI元素（使用载入的资源）
    ui_manager_->addElement(std::make_unique<engine::ui::UIImage>("assets/textures/Buildings/Castle.png"_hs));
    ui_manager_->addElement(std::make_unique<engine::ui::UILabel>(
        context_.getTextRenderer(), 
        "Hello, World!", 
        "assets/fonts/VonwaonBitmap-16px.ttf"
    ));
}

// void GameScene::onAttack()
// {
//     spdlog::info("Attack action triggered!");

//     context_.getDispatcher().enqueue<engine::utils::QuitEvent>(); // 触发退出事件，测试事件系统
// }
// void GameScene::onJump()
// {
//     spdlog::info("Jump action triggered!");
// }
bool GameScene::onReplace()
{
    requestReplaceScene(std::make_unique<game::scene::GameScene>(context_));
    return true;
}
bool GameScene::onPop()
{
    requestPopScene();
    return true;
}
bool GameScene::onPush()
{
    requestPushScene(std::make_unique<game::scene::GameScene>(context_));
    return true;
}
bool GameScene::onQuit()
{
    quit();
    return true;
}
}