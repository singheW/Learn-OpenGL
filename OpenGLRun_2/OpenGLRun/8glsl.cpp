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
//unsigned int loadCubemap(vector<std::string> faces);
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
//    glEnable(GL_DEPTH_TEST);
//    //glDepthFunc(GL_ALWAYS); // always pass the depth test (same effect as glDisable(GL_DEPTH_TEST))
//   glEnable(GL_PROGRAM_POINT_SIZE);//顶点着色器中修改点大小的功能
//   // // build and compile shaders
//    // -------------------------
//    Shader shaderRed("glsl.vert", "red.frag");
//    Shader shaderGreen("glsl.vert", "green.frag");
//    Shader shaderBlue("glsl.vert", "blue.frag");
//    Shader shaderYellow("glsl.vert", "yellow.frag");
//
//    unsigned int frontTexture = loadTexture("container.jpg");
//    unsigned int backTexture = loadTexture("awesomeface.png");
//
//    
//    float cubeVertices[] = {
//        // positions         
//        -0.5f, -0.5f, -0.5f,
//         0.5f, -0.5f, -0.5f,
//         0.5f,  0.5f, -0.5f,
//         0.5f,  0.5f, -0.5f,
//        -0.5f,  0.5f, -0.5f,
//        -0.5f, -0.5f, -0.5f,
//
//        -0.5f, -0.5f,  0.5f,
//         0.5f, -0.5f,  0.5f,
//         0.5f,  0.5f,  0.5f,
//         0.5f,  0.5f,  0.5f,
//        -0.5f,  0.5f,  0.5f,
//        -0.5f, -0.5f,  0.5f,
//
//        -0.5f,  0.5f,  0.5f,
//        -0.5f,  0.5f, -0.5f,
//        -0.5f, -0.5f, -0.5f,
//        -0.5f, -0.5f, -0.5f,
//        -0.5f, -0.5f,  0.5f,
//        -0.5f,  0.5f,  0.5f,
//
//         0.5f,  0.5f,  0.5f,
//         0.5f,  0.5f, -0.5f,
//         0.5f, -0.5f, -0.5f,
//         0.5f, -0.5f, -0.5f,
//         0.5f, -0.5f,  0.5f,
//         0.5f,  0.5f,  0.5f,
//
//        -0.5f, -0.5f, -0.5f,
//         0.5f, -0.5f, -0.5f,
//         0.5f, -0.5f,  0.5f,
//         0.5f, -0.5f,  0.5f,
//        -0.5f, -0.5f,  0.5f,
//        -0.5f, -0.5f, -0.5f,
//
//        -0.5f,  0.5f, -0.5f,
//         0.5f,  0.5f, -0.5f,
//         0.5f,  0.5f,  0.5f,
//         0.5f,  0.5f,  0.5f,
//        -0.5f,  0.5f,  0.5f,
//        -0.5f,  0.5f, -0.5f,
//    };
//    //cube VAO
//    unsigned int cubeVAO, cubeVBO;
//    glGenVertexArrays(1, &cubeVAO);
//    glGenBuffers(1, &cubeVBO);
//    glBindVertexArray(cubeVAO);
//    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//
//    //如何在着色器中定义uniform块并设定他们的内容布局。首先，调用glGenBuffers,创建一个uniform缓冲对象，绑定到GL_UNIFORM_BUFFER，并调用glBufferData分配足够内存
//  //配置uniform缓存对象
//    //第一步，获取相关索引块
//    unsigned int uniformBlockIndexRed = glGetUniformBlockIndex(shaderRed.ID, "Matrices");//通过调用glGetUniformBlockIndex来获取"着色器中已定义Uniform块的位置值索引"
//    unsigned int uniformBlockIndexGreen = glGetUniformBlockIndex(shaderGreen.ID, "Matrices");
//    unsigned int uniformBlockIndexBlue = glGetUniformBlockIndex(shaderBlue.ID, "Matrices");
//    unsigned int uniformBlockIndexYellow = glGetUniformBlockIndex(shaderYellow.ID, "Matrices");
////然后链接每个shader uniform block 到 uniform绑定点,将顶点着色器的Uniform块设置为绑定点0。注意我们需要对每个着色器都设置一遍。
//    //glUniformBlockBinding（程序对象，uniform块索引，链接到的绑定点）;
//    glUniformBlockBinding(shaderRed.ID, uniformBlockIndexRed, 0);
//    glUniformBlockBinding(shaderGreen.ID, uniformBlockIndexGreen, 0);
//    glUniformBlockBinding(shaderBlue.ID, uniformBlockIndexBlue, 0);
//    glUniformBlockBinding(shaderYellow.ID, uniformBlockIndexYellow, 0);
//    //现在真正创建缓冲,创建Uniform缓冲对象本身，并将其绑定到绑定点0：
//    unsigned int uboMatrices;
//    glGenBuffers(1, &uboMatrices);//首先，调用glGenBuffers,创建一个uniform缓冲对象
//    glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);//绑定到GL_UNIFORM_BUFFER
//    glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_STATIC_DRAW);//并调用glBufferData分配足够内存
//    glBindBuffer(GL_UNIFORM_BUFFER, 0);
//    //定义链接到uniform binding point的缓存范围
//    glBindBufferRange(GL_UNIFORM_BUFFER, 0, uboMatrices, 0, 2 * sizeof(glm::mat4));//使用glBindBufferRange函数让多个不同的Uniform块绑定到同一个Uniform缓冲对象上。
//    //剩余的就是填充这个缓冲了。因为我们已经为缓冲对象分配了足够的内存，我们可以使用glBufferSubData在进入渲染循环之前存储投影矩阵：
//    //存储投影矩阵
//    glm::mat4 projection = glm::perspective(45.0f, (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projection));
//    glBindBuffer(GL_UNIFORM_BUFFER, 0);
//    
//    shaderGreen.use();
//    shaderGreen.setInt("frontTexture", 0);
//    shaderGreen.setInt("backTexture", 1);
//    
//    
//    // render loop
//    // -----------
// 
//    while (!glfwWindowShouldClose(window))
//    {
//        float currentFrame = glfwGetTime();
//        deltaTime = currentFrame - lastFrame;
//        lastFrame = currentFrame;
//
//        //input 
//        processInput(window);
//
//        //render
//        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//        //将投影矩阵储存在Uniform缓冲的前半部分。在每次渲染迭代中绘制物体之前，我们会将观察矩阵更新到缓冲的后半部分：
//        //在uniform block中设置视角和投影矩阵
//        glm::mat4 view = camera.GetViewMatrix();
//        glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
//        glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view));
//        glBindBuffer(GL_UNIFORM_BUFFER, 0);
//
//       //绘制四个正方体
//        //红
//        glBindVertexArray(cubeVAO);
//        shaderRed.use();
//        glm::mat4 model = glm::mat4(1.0f);
//        model = glm::translate(model,glm::vec3(-0.75f, 0.75f, 0.0f));
//        shaderRed.setMat4("model", model);
//        glDrawArrays(GL_TRIANGLES, 0, 36);
//        //绿
//        shaderGreen.use();
//        glBindTexture(GL_TEXTURE_2D, frontTexture);
//        glBindTexture(GL_TEXTURE_2D, backTexture);
//        model = glm::mat4(1.0f);
//        model = glm::translate(model, glm::vec3(0.75f, 0.75f, 0.0f));
//        shaderGreen.setMat4("model", model);
//        glDrawArrays(GL_TRIANGLES, 0, 36);
//        //蓝
//        shaderBlue.use();
//        model = glm::mat4(1.0f);
//        model = glm::translate(model, glm::vec3(-0.75f, -0.75f, 0.0f));
//        shaderBlue.setMat4("model", model);
//        glDrawArrays(GL_TRIANGLES, 0, 36);
//        //黄
//        shaderYellow.use();
//        model = glm::mat4(1.0f);
//        model = glm::translate(model, glm::vec3(0.75f, -0.75f, 0.0f));
//        shaderYellow.setMat4("model", model);
//        glDrawArrays(GL_TRIANGLES, 0, 36);
//
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//
//    }
//
//    // optional: de-allocate all resources once they've outlived their purpose:
//    // ------------------------------------------------------------------------
//    glDeleteVertexArrays(1, &cubeVAO);
//    glDeleteBuffers(1, &cubeVBO);//完成所有的帧缓冲操作之后，删除这个帧缓冲对象
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
//
//unsigned int loadCubemap(vector<std::string> faces)
//{
//    unsigned int textureID;
//    glGenTextures(1, &textureID);
//    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
//
//   
//    int width, height, nrChannels;
//    for (unsigned int i = 0; i < faces.size(); i++)
//    {
//
//        
//
//        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
//        if (data)
//        {//从GL_TEXTURE_CUBE_MAP_POSITIVE_X开始遍历六个面，在每个迭代中对枚举值加1，遍历了整个纹理目标
//            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//            stbi_image_free(data);
//        }
//        else
//        {
//            std::cout << "Cubemap texture failed to load at path:" << faces[i] << std::endl;
//            stbi_image_free(data);
//
//        }
//    }//设定立方体贴图的环绕和过滤方式
//    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);//通过使用GL_CLAMP_TO_EDGE，OpenGL将在我们对两个面之间采样的时候，永远返回它们的边界值
//    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
//
//    return textureID;
//}