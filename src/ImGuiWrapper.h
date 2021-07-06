#pragma once

#include "imgui.h"
#include <SDL.h>

#if defined(IMGUI_IMPL_OPENGL_ES2)
    #include <GLES2/gl2.h>
#else
    #include <GL/gl3w.h>
#endif

#include <string>
#include <thread>

class ImGuiWrapper
{
public:

    ImGuiWrapper() {}
    virtual ~ImGuiWrapper() { Quit(); }

    void Run(const std::string& title = "Dear ImGui SDL2+OpenGL3 example", int width = 640, int height = 480);
    void Quit();

protected:
    // Called once after Run() is called and the window has been created.
    virtual void OnInit() {}

    // Called once per frame, to allow for application logic updates. 
    // The argument event has already been procesed by ImGui.
    virtual void OnNewFrame(const SDL_Event* event) {}

    // Called once per frame, place imgui code and OpenGL draw calls here.
    virtual void Draw() {}

    // Called once when the window has been closed, either by the user or by calling Quit().
    virtual void OnExit() {}

    // The background color. This can be modified at any time.
    ImVec4 m_clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Window handle to interact trough SDL functions.
    SDL_Window *m_window;

    inline const std::string &GetGlslVersion() const { return m_glsl_version; }

    inline bool IsRunning() const { return m_running; }

private:
    bool m_running = false;
    std::thread m_gui_thread;
    void _run(const std::string& title, int width , int height);

    std::string m_glsl_version;
};