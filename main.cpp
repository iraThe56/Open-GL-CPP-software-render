#include <glad/glad.h>
#include <GLFW/glfw3.h>



#include <iostream>
#include "shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "classes and helper functions/FPSCounter.h"
#include "classes and helper functions/GameBoard.h"



void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 800;




// int get_cell_buffer_index(int curent_x, int curent_y,int bufferWidth,int buffer_height){
//     curent_x=curent_x % bufferWidth;
//     curent_y=curent_y % buffer_height;
//     return (curent_y * bufferWidth + curent_x)  ;
// };

// int check_neighbor_cell(int curent_x,int curent_y,int shift_y, int shift_x,old_buffer,  cell_buffer) {
//
//     int position=get_cell_buffer_index(curent_x,)
//
//
// };
auto fpsCounter=FPSCounter();
int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    Shader blitShader("shaders/blit.vsh", "shaders/blit.fsh");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float blitvertices[] = {
        // positions       // texture coords
        -1.0f,  -1.0f, 0.0f, 0.0f, 0.0f, // top right
        -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, // bottom right
        1.0f, 1.0f, 0.0f, 1.0f, 1.0f, // bottom left
        1.0f,  -1.0f, 0.0f, 1.0f, 0.0f // top left
};
    unsigned int blitindices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
};

    unsigned int blitVBO, blitVAO, blitEBO;
    glGenVertexArrays(1, &blitVAO);
    glGenBuffers(1, &blitVBO);
    glGenBuffers(1, &blitEBO);

    glBindVertexArray(blitVAO);

    glBindBuffer(GL_ARRAY_BUFFER, blitVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(blitvertices), blitvertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, blitEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(blitindices), blitindices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    int bufferWidth = 300;
    int bufferHeight = 300;
    auto *imageData = new unsigned char[bufferWidth * bufferHeight * 4];
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bufferWidth, bufferHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

    glGenerateMipmap(GL_TEXTURE_2D);

    // render loop
    // -----------

    int number = 0;
    glfwInit();


 // cell state buffer
    auto cell_buffer = GameBoard(bufferWidth,bufferWidth);

    for (int y = 0; y < bufferHeight; y++) {
        for (int x = 0; x < bufferWidth; x++) {
            bool value=x&y;
            cell_buffer.set_cell_value(x,y,value);
        }
    }



    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        number=(glfwGetTimerValue()/(glfwGetTimerFrequency()/5));

        fpsCounter.calculate_fps();

        double xpos, ypos;
        //getting cursor position
        glfwGetCursorPos(window, &xpos, &ypos);
        int xpos_int=xpos;int int_ypos=ypos;
        int time=glfwGetTime();
        // std::cout<< number  <<std::endl;

        for (int y = 0; y < bufferHeight; y++) {
            for (int x = 0; x < bufferWidth; x++) {
                int index = (y * bufferWidth + x) * 4; // 4 channels (RGBA)


                int value=1;

                int moved_x=x-150;
                int moved_y=y-150;
                value=cell_buffer.return_cell_value(x,y)*255;


                imageData[index] = value;     // Red
                imageData[index + 1] = value; // Green
                imageData[index + 2] = value; // Blue
                imageData[index + 3] = 255; // Alpha
            }
        }

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bufferWidth, bufferHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
        glGenerateMipmap(GL_TEXTURE_2D);

        // render
        // ------
        glClearColor(1.0f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);

        // render container
        blitShader.use();
        glBindVertexArray(blitVAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &blitVAO);
    glDeleteBuffers(1, &blitVBO);
    glDeleteBuffers(1, &blitEBO);

    glDeleteTextures(1, &texture);

    delete[] imageData;




    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}