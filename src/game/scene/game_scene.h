#pragma once
#include "../../engine/scene/scene.h"

namespace game::scene {

class GameScene final: public engine::scene::Scene {
public:
    GameScene(engine::core::Context& context);
    ~GameScene();

    void init() override;
    void clean() override;

private:
    // --- 测试资源管理器 ---
    void testResourceManager();

    int scene_num_{0}; // 场景编号，测试用
    bool onReplace();
    bool onPop();
    bool onPush();
    bool onQuit();
};


}