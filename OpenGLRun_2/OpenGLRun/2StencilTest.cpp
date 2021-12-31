//
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include "stb_image.h"
//
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
//#include "shader_m.h"
//#include "camera.h"
//#include "model.h"
//
//#include <iostream>
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void processInput(GLFWwindow* window);
//unsigned int loadTexture(const char* path);
//
//// settings
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
//
//// camera
//Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
//float lastX = (float)SCR_WIDTH / 2.0;
//float lastY = (float)SCR_HEIGHT / 2.0;
//bool firstMouse = true;
//
//// timing
//float deltaTime = 0.0f;
//float lastFrame = 0.0f;
//
//int main()
//{
//    // glfw: initialize and configure
//    // ------------------------------
//    glfwInit();
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//#ifdef __APPLE__
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//#endif
//
//    // glfw window creation
//    // --------------------
//    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
//    if (window == NULL)
//    {
//        std::cout << "Failed to create GLFW window" << std::endl;
//        glfwTerminate();
//        return -1;
//    }
//    glfwMakeContextCurrent(window);
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//    glfwSetCursorPosCallback(window, mouse_callback);
//    glfwSetScrollCallback(window, scroll_callback);
//
//    // tell GLFW to capture our mouse
//    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//
//    // glad: load all OpenGL function pointers
//    // ---------------------------------------
//    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//    {
//        std::cout << "Failed to initialize GLAD" << std::endl;
//        return -1;
//    }
//
//    // configure global opengl state
//    // -----------------------------
//    glEnable(GL_DEPTH_TEST);//启用深度测试
//    glDepthFunc(GL_LESS);//glDepthFunc设置比较运算符（或者说深度函数)//GL_LESS在片段深度值小于缓冲的深度值时通过测试
//    //启用模板测试，并设置测试通过或失败时的行为：
//    glEnable(GL_STENCIL_TEST);//启用模板测试
//    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);//glStencilFunc(func设置模板测试函数，ref设置模板测试的参考值，mask设置一个掩码（用于与参考值比较）)
//    glStencilOp(GL_KEEP, GL_REPLACE, GL_REPLACE);//glStencilOp(sfail模板测试失败时的行为，dpfail模板测试通过但深度测试失败时的行为，dppass都通过时的行为)
//                                              //GL_KEEP保持当前存储 GL_REPLACE， GL_REPLACE将模板值设置为glStencilFunc函数设置的ref值
//  
//    // build and compile shaders
//    // -------------------------
//    Shader shader("stencil_test.vert", "stencil_test.frag");
//    Shader shaderColor("stencil_outline.vert", "stencil_outline.frag");
//
//    // set up vertex data (and buffer(s)) and configure vertex attributes
//    // ------------------------------------------------------------------
//    float cubeVertices[] = {
//        // positions          // texture Coords
//        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
//         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//
//        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
//        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//
//        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
//         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
//        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
//         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//
//        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
//        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
//    };
//    float planeVertices[] = {
//        // positions          // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
//         5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
//        -5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
//        -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
//
//         5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
//        -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
//         5.0f, -0.5f, -5.0f,  2.0f, 2.0f
//    };
//    // cube VAO
//    unsigned int cubeVAO, cubeVBO;
//    glGenVertexArrays(1, &cubeVAO);
//    glGenBuffers(1, &cubeVBO);
//    glBindVertexArray(cubeVAO);
//    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(1);
//    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//    glBindVertexArray(0);
//    // plane VAO
//    unsigned int planeVAO, planeVBO;
//    glGenVertexArrays(1, &planeVAO);
//    glGenBuffers(1, &planeVBO);
//    glBindVertexArray(planeVAO);
//    glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(1);
//    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//    glBindVertexArray(0);
//
//    // load textures
//    // -------------
//    unsigned int cubeTexture = loadTexture("marble.jpg");
//    unsigned int floorTexture = loadTexture("metal.jpeg");
//
//    // shader configuration
//    // --------------------
//    shader.use();
//    shader.setInt("texture1", 0);
//
//    // render loop
//    // -----------
//    while (!glfwWindowShouldClose(window))
//    {
//        // per-frame time logic
//        // --------------------
//        float currentFrame = glfwGetTime();
//        deltaTime = currentFrame - lastFrame;
//        lastFrame = currentFrame;
//
//        // input
//        // -----
//        processInput(window);
//
//        // render
//        // ------
//        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);//使用GL_STENCIL_BUFFER_BIT清除模板缓冲
//
//        shaderColor.use();
//        glm::mat4 model = glm::mat4(1.0f);
//        glm::mat4 view = camera.GetViewMatrix();
//        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//        shaderColor.setMat4("view", view);
//        shaderColor.setMat4("projection", projection);
//
//
//        shader.use();
//        shader.setMat4("view", view);
//        shader.setMat4("projection", projection);
//       
//        //将模板缓冲清除为0，对箱子中所有绘制的片段，将模板值更新为1：
//        glStencilMask(0x00);// 每一位在写入模板缓冲时都会变成0（禁用写入）,保证我们在绘制地板的时候不会更新模板缓冲
//        // floor
//        glBindVertexArray(planeVAO);
//        glBindTexture(GL_TEXTURE_2D, floorTexture);
//        shader.setMat4("model", glm::mat4(1.0f));
//        glDrawArrays(GL_TRIANGLES, 0, 6);
//        glBindVertexArray(0);
//
//        //1.绘制物体
//        glStencilFunc(GL_ALWAYS, 1, 0xFF);// 所有的片段都应该更新模板缓冲 //使用GL_ALWAYS模板测试函数，保证每个片段都会将模板缓冲的模板值更新为1。因为片段永远会通过模板测试，在绘制片段的地方，模板缓冲会被更新为参考值。
//      //glStencilFunc(func设置模板测试函数，ref设置模板测试的参考值，mask设置一个掩码（用于与参考值比较）)
//        glStencilMask(0xFF);// 启用模板缓冲写入, 每一位写入模板缓冲时都保持原样
//
//        glBindVertexArray(cubeVAO);
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, cubeTexture);
//        model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
//        shader.setMat4("model", model);
//        glDrawArrays(GL_TRIANGLES, 0, 36);
//        model = glm::mat4(1.0f);
//        model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
//        shader.setMat4("model", model);
//        glDrawArrays(GL_TRIANGLES, 0, 36);
//        //2.现在模板缓冲在箱子被绘制的地方都更新为1了，我们将要绘制放大的箱子，但这次要禁用模板缓冲的写入,让他看起来像边缘
//        glStencilFunc(GL_NOTEQUAL, 1, 0xFF);//GL_NOTEQUA会保证我们只绘制模板值不为1即箱子在之前绘制的箱子之外的部分。禁用了深度测试让放大的箱子即边框不会被地板所覆盖。
//        glStencilMask(0x00); // 禁止模板缓冲的写入
//        glDisable(GL_DEPTH_TEST);
//        shaderColor.use();
//        float scale = 1.1;
//        
//        glBindVertexArray(cubeVAO);
//        glBindTexture(GL_TEXTURE_2D,cubeTexture);
//        model = glm::mat4(1.0f);
//        model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
//        model = glm::scale(model, glm::vec3(scale, scale, scale));
//        shaderColor.setMat4("model", model);
//        glDrawArrays(GL_TRIANGLES, 0, 36);
//        model = glm::mat4(1.0f);
//        model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
//        model = glm::scale(model, glm::vec3(scale, scale, scale));
//        shaderColor.setMat4("model", model);
//        glDrawArrays(GL_TRIANGLES, 0, 36);
//
//        glBindVertexArray(0);
//        glStencilMask(0xFF);
//        glStencilFunc(GL_ALWAYS, 0, 0xFF);
//        glEnable(GL_DEPTH_TEST);//完成之后重新启用深度缓冲。
//
//        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
//        // -------------------------------------------------------------------------------
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//
//    // optional: de-allocate all resources once they've outlived their purpose:
//    // ------------------------------------------------------------------------
//    glDeleteVertexArrays(1, &cubeVAO);
//    glDeleteVertexArrays(1, &planeVAO);
//    glDeleteBuffers(1, &cubeVBO);
//    glDeleteBuffers(1, &planeVBO);
//
//    glfwTerminate();
//    return 0;
//}
//
//// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
//// ---------------------------------------------------------------------------------------------------------
//void processInput(GLFWwindow* window)
//{
//    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//        glfwSetWindowShouldClose(window, true);
//
//    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//        camera.ProcessKeyboard(FORWARD, deltaTime);
//    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//        camera.ProcessKeyboard(BACKWARD, deltaTime);
//    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//        camera.ProcessKeyboard(LEFT, deltaTime);
//    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//        camera.ProcessKeyboard(RIGHT, deltaTime);
//}
//
//// glfw: whenever the window size changed (by OS or user resize) this callback function executes
//// ---------------------------------------------------------------------------------------------
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//    // make sure the viewport matches the new window dimensions; note that width and 
//    // height will be significantly larger than specified on retina displays.
//    glViewport(0, 0, width, height);
//}
//
//// glfw: whenever the mouse moves, this callback is called
//// -------------------------------------------------------
//void mouse_callback(GLFWwindow* window, double xpos, double ypos)
//{
//    if (firstMouse)
//    {
//        lastX = xpos;
//        lastY = ypos;
//        firstMouse = false;
//    }
//
//    float xoffset = xpos - lastX;
//    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
//
//    lastX = xpos;
//    lastY = ypos;
//
//    camera.ProcessMouseMovement(xoffset, yoffset);
//}
//
//// glfw: whenever the mouse scroll wheel scrolls, this callback is called
//// ----------------------------------------------------------------------
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
//{
//    camera.ProcessMouseScroll(yoffset);
//}
//
//// utility function for loading a 2D texture from file
//// ---------------------------------------------------
//unsigned int loadTexture(char const* path)
//{
//    unsigned int textureID;
//    glGenTextures(1, &textureID);
//
//    int width, height, nrComponents;
//    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
//    if (data)
//    {
//        GLenum format;
//        if (nrComponents == 1)
//            format = GL_RED;
//        else if (nrComponents == 3)
//            format = GL_RGB;
//        else if (nrComponents == 4)
//            format = GL_RGBA;
//
//        glBindTexture(GL_TEXTURE_2D, textureID);
//        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
//        glGenerateMipmap(GL_TEXTURE_2D);
//
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//        stbi_image_free(data);
//    }
//    else
//    {
//        std::cout << "Texture failed to load at path: " << path << std::endl;
//        stbi_image_free(data);
//    }
//
//    return textureID;
//}
