/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** main
*/

#include <EGL/egl.h>
#include <GLES3/gl3.h>

#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include "GuiVR.hpp"
#define IMGUI_IMPL_OPENGL_ES3
#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_impl_opengl3.h"
#include "UtilsVR.hpp"
#include "Maths/Vector2.hpp"

MemoryIOSystem *gMemoryIOSystem;

android_app *EGE::UtilsVR::app = nullptr;

extern "C" void android_main(android_app *app) {
    EGE::UtilsVR::app = app;
    gMemoryIOSystem = new MemoryIOSystem();
    gMemoryIOSystem->setAssetManager(app->activity->assetManager);

    gMemoryIOSystem->addFile("models/floor/floor.obj");
    gMemoryIOSystem->addFile("models/floor/floor.mtl");
    gMemoryIOSystem->addFile("models/food/steak.obj");
    gMemoryIOSystem->addFile("models/food/steak.mtl");
    gMemoryIOSystem->addFile("models/items/1.obj");
    gMemoryIOSystem->addFile("models/items/1.mtl");
    gMemoryIOSystem->addFile("models/items/2.obj");
    gMemoryIOSystem->addFile("models/items/2.mtl");
    gMemoryIOSystem->addFile("models/items/3.obj");
    gMemoryIOSystem->addFile("models/items/3.mtl");
    gMemoryIOSystem->addFile("models/items/4.obj");
    gMemoryIOSystem->addFile("models/items/4.mtl");
    gMemoryIOSystem->addFile("models/items/5.obj");
    gMemoryIOSystem->addFile("models/items/5.mtl");
    gMemoryIOSystem->addFile("models/items/6.obj");
    gMemoryIOSystem->addFile("models/items/6.mtl");
    gMemoryIOSystem->addFile("models/player/lvl1/lvl1.obj");
    gMemoryIOSystem->addFile("models/player/lvl2/lvl2.obj");
    gMemoryIOSystem->addFile("models/player/lvl3/lvl3.obj");
    gMemoryIOSystem->addFile("models/player/lvl4/lvl4.obj");
    gMemoryIOSystem->addFile("models/player/lvl5/lvl5.obj");
    gMemoryIOSystem->addFile("models/player/lvl6/lvl6.obj");
    gMemoryIOSystem->addFile("models/player/lvl7/lvl7.obj");
    gMemoryIOSystem->addFile("models/player/lvl8/lvl8.obj");
    gMemoryIOSystem->addFile("models/egg/egg.obj");

    GuiVR a(app);

    while (a.isRunning()) {
        a.update();
    }
}
