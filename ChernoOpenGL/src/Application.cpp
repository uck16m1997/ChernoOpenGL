
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

    // Generate 1 buffer and gives us id for the buffer (as buffer is an out variable)
    unsigned int buffer;
    glGenBuffers(1, &buffer);

    // Enable the vertex attrib indexed at 0 
    glEnableVertexAttribArray(0);
    // 0 for first attribute, 2 floats per vertex, Don't normalize, Size of all attributes until next vertex, Size of attributes until our specified attribute
    glVertexAttribPointer(0,2, GL_FLOAT,GL_FALSE,sizeof(float) * 2,0);

    // Select/Bind that buffer as our current array buffer
    glBindBuffer(GL_ARRAY_BUFFER, buffer);

    // To our array buffer, that will contain size of 6 floats in bytes, copy they array of position array,  we won't change this data(STATIC) and read it for drawing (DRAW)
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