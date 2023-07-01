
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;
    

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    //  Pass glad the function to load the address of the OpenGL function pointers which is OS-specific.
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;

    // Positions of vertexes
    float position[6] = {
        -0.5f,-0.5f,
         0.0f,0.5f,
         0.5f,-0.5f
    };

    // Generate 1 buffer and gives us id for the buffer as a reference
    unsigned int buffer;
    glGenBuffers(1, &buffer);
    // Select that buffer as our current array buffer
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), position,GL_STATIC_DRAW);
     
    /* Game Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw 3 vertices starting from index 0
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}