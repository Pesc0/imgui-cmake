#include "ImGuiWrapper.h"

#include <chrono>
#include <thread>
#include <iostream>


static bool CheckShader(GLuint handle)
{
    GLint status, log_length;
    glGetShaderiv(handle, GL_COMPILE_STATUS, &status);
    glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &log_length);

    if ((GLboolean)status == GL_FALSE)
        std::cerr << "Failed to compile shader!\n";

    if (log_length > 1)
    {
        char *buf = new char[log_length + 1];
        glGetShaderInfoLog(handle, log_length, NULL, buf);
        std::cerr << "Shader log: " << buf << '\n';
        delete buf;
    }
    return (GLboolean)status == GL_TRUE;
}

static bool CheckProgram(GLuint handle)
{
    GLint status, log_length;
    glGetProgramiv(handle, GL_LINK_STATUS, &status);
    glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &log_length);

    if ((GLboolean)status == GL_FALSE)
        std::cerr << "Failed to link program!\n";

    if (log_length > 1)
    {
        char *buf = new char[log_length + 1];
        glGetProgramInfoLog(handle, log_length, NULL, buf);
        std::cerr << "Program log: " << buf << '\n';
        delete buf;
    }
    return (GLboolean)status == GL_TRUE;
}

static GLuint CreateShader(GLenum type, const std::string &shaderSrc)
{
    GLuint shader = glCreateShader(type);
    if (shader == 0) return 0;

    // Set source and compile
    const char *src = shaderSrc.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    if(CheckShader(shader) == false) return 0;

    return shader;
}

static GLuint CreateProgram(const std::string &vShader, const std::string &fShader)
{
    GLuint programObject = glCreateProgram();
    if (programObject == 0) return 0;

    GLuint vertexShader = CreateShader(GL_VERTEX_SHADER, vShader);
    GLuint fragmentShader = CreateShader(GL_FRAGMENT_SHADER, fShader);

    glAttachShader(programObject, vertexShader);
    glAttachShader(programObject, fragmentShader);

    glLinkProgram(programObject);

    if(CheckProgram(programObject) == 0) return 0;

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return programObject;
}



class App final : public ImGuiWrapper
{
public:
    App() {}

private:

    void OnRunStart() override
    {
        SDL_SetWindowTitle(m_window, "Testing..."); // Override the title set in Run()
        SDL_GL_SetSwapInterval(0);                  // Override vsync setting by disabling it

        std::string vShader =
        "\n"
        "attribute vec4 position;       \n"
        "void main()                    \n"
        "{                              \n"
        "   gl_Position = position;     \n"
        "}                              \n";

        std::string fShader =
        "\n"
        "void main()                                  \n"
        "{                                            \n"
        "   gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);  \n"
        "}                                            \n";

        program = CreateProgram(GetGlslVersion() + vShader, GetGlslVersion() + fShader);
        glUseProgram(program);
    }

    void OnNewFrame() override
    {
        framecounter++;
    }

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
            ImGui::Checkbox("Show triangle", &show_triangle);

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
        if (show_triangle)
        {
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, triangle_verts);
            glDrawArrays(GL_TRIANGLES,0,3); 
        }
    }

    void OnWindowClose() override
    {
        std::cout << "Window closed." << std::endl; 
        glDeleteProgram(program);
    }

    bool show_demo_window = true;
    bool show_another_window = false;
    bool show_triangle = true;

    unsigned int framecounter = 0;

    float triangle_verts[6] = {0.0, 1.0, -1.0, -1.0, 1.0, -1.0}; 
    GLuint program;
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