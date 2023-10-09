#include <iostream>

#include "imgui/imgui.h"
#include "Window.h"
#include "Gui.h"
#include "Time.h"
#include "Game.h"

int main(void)
{
    try {
        auto window = Window();
        window.LoadGL();
        std::cout << "Loaded OpenGL " << glGetString(GL_VERSION) << std::endl;

        auto game = Game(window.GetWindowWidth(), window.GetWindowHeight());
        auto gui = Gui(window.GetWindow());

        while (!window.ShouldClose()) {
            Time::Init();

            window.Clear();

            gui.OnUpdate();
            game.OnUpdate();

            game.OnRender();
            gui.OnRender();

            window.SwapBuffers();
            window.PollEvents();
        }
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}