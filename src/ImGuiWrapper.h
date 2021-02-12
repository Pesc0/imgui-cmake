#pragma once

#include "imgui.h"
#include <SDL.h>
#include <GL/gl3w.h>

#include <string>
#include <thread>

class ImGuiWrapper
{
public:

    ImGuiWrapper() {}
    virtual ~ImGuiWrapper() {}

    void Run(const std::string& title = "Dear ImGui SDL2+OpenGL3 example", int width = 640, int height = 480);
    void Quit();

protected:
    // Called once after Run() is called and the window has been created.
    virtual void OnRunStart() {}

    // Called once per frame, to allow for application logic updates.
    virtual void OnNewFrame() {}

    // Called once per frame. Place ImGui calls here. Do not make raw OpenGL calls here.
    virtual void DrawImGui() {}

    // Generic OpenGL drawing context, called immediately after DrawImGui().
    virtual void DrawOpenGL() {}

    // Called once when the window has been closed, either by the user or by calling Quit().
    virtual void OnWindowClose() {}

    // The background color. This can be modified at any time.
    ImVec4 m_clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Window handle to interact trough SDL functions.
    SDL_Window *m_window;
    const char *GetGlslVersion() const { return m_glsl_version; }

private:
    bool m_running = false;
    std::thread m_gui_thread;
    void _run(const std::string& title, int width , int height);

    char* m_glsl_version;
};