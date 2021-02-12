#include "ImGuiWrapper.h"

#include <chrono>
#include <thread>
#include <iostream>

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

class App final : public ImGuiWrapper
{
public:
    App() {}

private:

    void OnRunStart() override
    {
        SDL_SetWindowTitle(m_window, "Testing...");
        SDL_GL_SetSwapInterval(0); // Disable vsync

        glEnable(GL_DEPTH_TEST);
        glGenBuffers(1,&vbo); //generate an index for the vertexbuffer
        glBindBuffer(GL_ARRAY_BUFFER,vbo);    //use vbo as ARRAY_BUFFER
        glBufferData(GL_ARRAY_BUFFER,sizeof(f),f,GL_STATIC_DRAW);//fill up the array with vertex and color-data
        glEnableVertexAttribArray(w);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    }

    void OnNewFrame() override
    {
        framecounter++;
    }

    // Called once per frame. Place ImGui calls here. Do not make raw OpenGL calls here.
    void DrawImGui() override
    {
        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&m_clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::Text("Number of frames: %u", framecounter);
            ImGui::End();
        }

        // 3. Show another simple window.
        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }
    }

    void DrawOpenGL() override
    {
        glClear(GL_DEPTH_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES,0,3); 
    }

    void OnWindowClose() override
    {
        std::cout << "Window closed." << std::endl; 
    }

    bool show_demo_window = true;
    bool show_another_window = false;

    GLuint vbo;
    GLuint w=0;
    float f[6]={0.0, 1.0, -1.0, -1.0, 1.0, -1.0};    //vertex array

    unsigned int framecounter = 0;
};


int main(int, char**)
{
    App app;
    app.Run("", 1280, 720);

    while (true)
    {
        std::cout << "Running.." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    return 0;
}