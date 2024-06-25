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
    try {
        __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "main.cpp: android_main():26");
        EGE::UtilsVR::app = app;
        __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "main.cpp: android_main():28");
        gMemoryIOSystem = new MemoryIOSystem();
        __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "main.cpp: android_main():30");
        gMemoryIOSystem->setAssetManager(app->activity->assetManager);
        __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "main.cpp: android_main():32");
        gMemoryIOSystem->addFile("models/floor/floor.obj");
        __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "main.cpp: android_main():34");
        gMemoryIOSystem->addFile("models/floor/floor.mtl");
        __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "main.cpp: android_main():36");
        gMemoryIOSystem->addFile("models/food/steak.obj");
        __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "main.cpp: android_main():38");
        gMemoryIOSystem->addFile("models/food/steak.mtl");
        __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "main.cpp: android_main():40");
        gMemoryIOSystem->addFile("models/items/1.obj");
        __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "main.cpp: android_main():42");
        gMemoryIOSystem->addFile("models/items/1.mtl");
        __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "main.cpp: android_main():44");
        gMemoryIOSystem->addFile("models/items/2.obj");
        __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "main.cpp: android_main():46");
        gMemoryIOSystem->addFile("models/items/2.mtl");
        __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "main.cpp: android_main():48");
        gMemoryIOSystem->addFile("models/items/3.obj");
        __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "main.cpp: android_main():50");
        gMemoryIOSystem->addFile("models/items/3.mtl");
        __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "main.cpp: android_main():52");
        gMemoryIOSystem->addFile("models/items/4.obj");
        __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "main.cpp: android_main():54");
        gMemoryIOSystem->addFile("models/items/4.mtl");
        __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "main.cpp: android_main():56");
        gMemoryIOSystem->addFile("models/items/5.obj");
        __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "main.cpp: android_main():58");
        gMemoryIOSystem->addFile("models/items/5.mtl");
        __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "main.cpp: android_main():60");
        gMemoryIOSystem->addFile("models/items/6.obj");
        __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "main.cpp: android_main():62");
        gMemoryIOSystem->addFile("models/items/6.mtl");
        __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "main.cpp: android_main():64");
        gMemoryIOSystem->addFile("models/player/lvl1/lvl1.obj");
        gMemoryIOSystem->addFile("models/player/lvl1/lvl1.mtl");
        __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "main.cpp: android_main():66");
        gMemoryIOSystem->addFile("models/player/lvl2/lvl2.obj");
        gMemoryIOSystem->addFile("models/player/lvl2/lvl2.mtl");
        __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "main.cpp: android_main():68");
        gMemoryIOSystem->addFile("models/player/lvl3/lvl3.obj");
        gMemoryIOSystem->addFile("models/player/lvl3/lvl3.mtl");
        __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "main.cpp: android_main():70");
        gMemoryIOSystem->addFile("models/player/lvl4/lvl4.obj");
        gMemoryIOSystem->addFile("models/player/lvl4/lvl4.mtl");
        __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "main.cpp: android_main():72");
        gMemoryIOSystem->addFile("models/player/lvl5/lvl5.obj");
        gMemoryIOSystem->addFile("models/player/lvl5/lvl5.mtl");
        __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "main.cpp: android_main():74");
        gMemoryIOSystem->addFile("models/player/lvl6/lvl6.obj");
        gMemoryIOSystem->addFile("models/player/lvl6/lvl6.mtl");
        __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "main.cpp: android_main():76");
        gMemoryIOSystem->addFile("models/player/lvl7/lvl7.obj");
        gMemoryIOSystem->addFile("models/player/lvl7/lvl7.mtl");
        __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "main.cpp: android_main():78");
        gMemoryIOSystem->addFile("models/player/lvl8/lvl8.obj");
        gMemoryIOSystem->addFile("models/player/lvl8/lvl8.mtl");
        __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "main.cpp: android_main():80");
        gMemoryIOSystem->addFile("models/egg/egg.obj");
        __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "main.cpp: android_main():82");
        gMemoryIOSystem->addFile("models/egg/materials.mtl");
        __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "main.cpp: android_main():84");
        gMemoryIOSystem->addFile("models/egg/egg.obj");
        gMemoryIOSystem->addFile("models/egg/materials.mtl");

        GuiVR a(app);
        __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "main.cpp: android_main():87");


        while (a.isRunning()) {
            a.update();
        }
    } catch (const std::exception& e) {
        __android_log_print(ANDROID_LOG_FATAL, "DEBUG", "catched exception: %s", e.what());
    }
}
