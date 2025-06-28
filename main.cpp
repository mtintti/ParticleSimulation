
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // Adjust the OpenGL viewport to the new window size
    glViewport(0, 0, width, height);
}

int main(){
    
    std::cout << "Hey c++ is working" ;

    // Initialize GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    // Set OpenGL version (3.3 Core)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a window
    GLFWwindow *window = glfwCreateWindow(800, 600, "OpenGL Window", NULL, NULL);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Load OpenGL using GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    // triangle tutorial

    float vertices[] = {
        //-0.5f, -0.5f, 0.0f,
        // 0.5f, -0.5f, 0.0f,
        // 0.0f, 0.5f, 0.0f
        0.5f, -0.5f,
        //-0.5f, -0.5f,
    };

    

    // unsigned int VBO;
    GLuint VBO = 0;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(vertices), vertices, GL_STATIC_DRAW); old from tutorial
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    // shaders
    // const char* vertex_shader = "#version 410 core\n"
    //"in vec3 vp;" "void main() { gl_Position = vec4(vp.x, vp.y + 1.0, vp.z, 1.0);} };";

    const char *vertex_shader = "#version 330 core\n"
                                "layout (location = 0) in vec2 Pos;"
                                "void main() {gl_Position = vec4(Pos.x, Pos.y, 0.0, 1.0);} };";

    const char *fragment_shader =
        //"#version 410 core\n" "out vec3 frag_colour;" " void main() { frag_colour = vec4(0.5, 0.0, 0.5, 1.0)}" "}";
        "#version 330 core\n"
        "out vec4 FragColor;"
        "void main() {FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);} }";

    // opengl shaderiin loadataan ylemmät kaksi stringiä
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex_shader, NULL);
    glCompileShader(vs);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragment_shader, NULL);
    glCompileShader(fs);

    // linkataan meidän ylemmät shaderit shader programmiin
    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, fs);
    glAttachShader(shader_program, vs);
    glLinkProgram(shader_program);
    // shaders done

    // next we draw on our screen using a loop

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents(); // update window events

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // pyyhitän piirros surface puhtaaksi

        glUseProgram(shader_program);
        glBindVertexArray(vao);
        // laitetaan shader program ja VAO opengl  state machine

        glPointSize(3.0f); // points size, duh..

        glDrawArrays(GL_POINTS, 0, 1);
        // piirretään 0-3 points VAO:sta ja current shaderistä

        glfwSwapBuffers(window);
        // laitetaan meidän hieno kolmio ruudulle
    }

    // triangle tutorial end
    

    //second particle simulation

    

    // second end

    // Set window title (simulate displaying text)
    glfwSetWindowTitle(window, "OpenGL Test Window - Hello, World!");

    // Render loop
    while (!glfwWindowShouldClose(window))
    {
        // Input
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        // Render background color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}