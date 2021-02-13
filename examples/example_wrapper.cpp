#include "ImGuiWrapper.h"

#include <chrono>
#include <thread>
#include <iostream>

#define BUFFER_OFFSET(i) ((char *)NULL + (i))


// If you get an error please report on github. You may try different GL context version or GLSL version. See GL<>GLSL version table at the top of this file.
static bool CheckShader(GLuint handle, const char* desc)
{
    GLint status = 0, log_length = 0;
    glGetShaderiv(handle, GL_COMPILE_STATUS, &status);
    glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &log_length);
    if ((GLboolean)status == GL_FALSE)
        fprintf(stderr, "ERROR: ImGui_ImplOpenGL3_CreateDeviceObjects: failed to compile %s!\n", desc);
    if (log_length > 1)
    {
        ImVector<char> buf;
        buf.resize((int)(log_length + 1));
        glGetShaderInfoLog(handle, log_length, NULL, (GLchar*)buf.begin());
        fprintf(stderr, "Shader log:\n%s\n", buf.begin());
    }
    return (GLboolean)status == GL_TRUE;
}

// If you get an error please report on GitHub. You may try different GL context version or GLSL version.
static bool CheckProgram(GLuint handle, const char* desc)
{
    GLint status = 0, log_length = 0;
    glGetProgramiv(handle, GL_LINK_STATUS, &status);
    glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &log_length);
    if ((GLboolean)status == GL_FALSE)
        fprintf(stderr, "ERROR: ImGui_ImplOpenGL3_CreateDeviceObjects: failed to link %s! (with GLSL '%s')\n", desc, "");
    if (log_length > 1)
    {
        ImVector<char> buf;
        buf.resize((int)(log_length + 1));
        glGetProgramInfoLog(handle, log_length, NULL, (GLchar*)buf.begin());
        fprintf(stderr, "Program log:\n%s\n", buf.begin());
    }
    return (GLboolean)status == GL_TRUE;
}

GLuint CreateShader(GLenum type, const char *shaderSrc)
{
    GLuint shader = glCreateShader(type);

    if (shader == 0) return 0;
        
    // Set source and compile    
    glShaderSource(shader, 1, &shaderSrc, nullptr);
    glCompileShader(shader);

    if(CheckShader(shader, ""))
        return shader;
    else
        return 0;
}

GLuint CreateProgram(const std::string &vShader, const std::string &fShader)
{
    GLuint vertexShader = CreateShader(GL_VERTEX_SHADER, vShader.c_str());
    GLuint fragmentShader = CreateShader(GL_FRAGMENT_SHADER, fShader.c_str());

    GLuint programObject = glCreateProgram();
    if (programObject == 0)
        return 0;

    glAttachShader(programObject, vertexShader);
    glAttachShader(programObject, fragmentShader);

    glLinkProgram(programObject);
    if(!CheckProgram(programObject, "")) return 0;
    glValidateProgram(programObject);

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
        SDL_SetWindowTitle(m_window, "Testing..."); // Change title
        SDL_GL_SetSwapInterval(0); // Disable vsync

//        glGenBuffers(1,&vbo);                                       //generate an index for the vertexbuffer
//        glBindBuffer(GL_ARRAY_BUFFER,vbo);                          //use vbo as ARRAY_BUFFER
//        glBufferData(GL_ARRAY_BUFFER,sizeof(f),f,GL_STATIC_DRAW);   //fill up the array with vertex and color-data
        glEnableVertexAttribArray(w);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, f);

        std::string vShader =  
        "\n"
        "attribute vec4 position;    \n"
        "void main()                  \n"
        "{                            \n"
        "   gl_Position = position;  \n"
        "}                            \n";
    
        std::string fShader = 
        "\n"
        "void main()                                  \n"
        "{                                            \n"
        "   gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);  \n"
        "}                                            \n";

        GLuint program = CreateProgram(GetGlslVersion() + vShader, GetGlslVersion() +fShader);
        glUseProgram(program);
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
        glEnableVertexAttribArray(w);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, f);
        glDrawArrays(GL_TRIANGLES,0,3); 
    }

    void OnWindowClose() override
    {
        std::cout << "Window closed." << std::endl; 
    }

    bool show_demo_window = true;
    bool show_another_window = false;

    unsigned int framecounter = 0;

    GLuint vbo;
    GLuint w=0;
    float f[6]={0.0, 1.0, -1.0, -1.0, 1.0, -1.0};    //vertex array
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