//
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include "stb_image.h"//Texture：添加头文件
//
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//#include "shader_m.h"
//#include "camera.h"
//#include <iostream>
//
//glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
//glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
//glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
//
//const unsigned int WIDTH = 1024;
//const unsigned int HEIGHT = 768;
//
//
//Camera camera(glm::vec3(0.0f, 0.0f, 6.0f));
//float lastX = WIDTH / 2.0f;
//float lastY = HEIGHT / 2.0f;
//bool firstMouse = true;
//
//float deltaTime = 0.0f; // 当前帧与上一帧的时间差
//float lastFrame = 0.0f; // 上一帧的时间
//glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
//
//void Global_Framebuffer_Size_Callback(GLFWwindow* window, int width, int height);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void Global_ProcessInput(GLFWwindow* WindowPtr);
//
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
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
//{
//    camera.ProcessMouseScroll(yoffset);
//}
//// 调整视口大小framebuffer_size_callback{glViewport()}
//void Global_Framebuffer_Size_Callback(GLFWwindow* WindowPtr, int Width, int Height)
//{
//    glViewport(0, 0, Width, Height);
//}
////输入控制processInput{glfwGetKey();glfwSetWindowShouldClose()}
//void Global_ProcessInput(GLFWwindow* WindowPtr)
//{
//    if (glfwGetKey(WindowPtr, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//    {
//        glfwSetWindowShouldClose(WindowPtr, true);
//    }
//    if (glfwGetKey(WindowPtr, GLFW_KEY_W) == GLFW_PRESS)
//        camera.ProcessKeyboard(FORWARD, deltaTime);
//    if (glfwGetKey(WindowPtr, GLFW_KEY_S) == GLFW_PRESS)
//        camera.ProcessKeyboard(BACKWARD, deltaTime);
//    if (glfwGetKey(WindowPtr, GLFW_KEY_A) == GLFW_PRESS)
//        camera.ProcessKeyboard(LEFT, deltaTime);
//    if (glfwGetKey(WindowPtr, GLFW_KEY_D) == GLFW_PRESS)
//        camera.ProcessKeyboard(RIGHT, deltaTime);
//}
//
//int main()
//{//1.初始化glfw并进行配置：glfwInit(); glfwWindowHint
//    // 初始化GLFW
//    glfwInit();
//    // 设定 opengl版本为 3.3
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    // 使用核心模式
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//    // 2.创建窗口：glfwCreateWindow()； glfwSetFramebufferSizeCallback();
//    GLFWwindow* WindowPtr = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
//    if (WindowPtr == NULL)
//    {
//        std::cout << "Failed to create GLFW window" << std::endl;
//        glfwTerminate();
//        return -1;
//    }
//    glfwMakeContextCurrent(WindowPtr);
//    glfwSetFramebufferSizeCallback(WindowPtr, Global_Framebuffer_Size_Callback);
//    glfwSetCursorPosCallback(WindowPtr, mouse_callback);//鼠标一移动mouse_callback函数就会被调用：
//    glfwSetScrollCallback(WindowPtr, scroll_callback);//注册鼠标滚轮的回调函数：
//    glfwSetInputMode(WindowPtr, GLFW_CURSOR, GLFW_CURSOR_DISABLED);//隐藏光标，并捕捉(Capture)它
//    //3.初始化glad:gladLoadGLLoader()glfwGetProcAddress)
//    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//    {
//        std::cout << "Failed to initialize GLAD" << std::endl;
//        return -1;
//    }
//
//    glEnable(GL_DEPTH_TEST);
//
//    Shader lightingShader("color.vs", "color.fs");
//    Shader lightCubeShader("light_cube.vs", "light_cube.fs");
//
//    float vertices[] = {
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
//    //创建VBO管理顶点缓存，VAO储存顶点属性，EBO储存索引缓冲
//    unsigned int VBO, cubeVAO;
//    glGenVertexArrays(1, &cubeVAO);//使用glGenVertexArrays函数和一个缓冲ID生成一个VAO对象：
//    glGenBuffers(1, &VBO);//使用glGenBuffers函数和一个缓冲ID生成一个VBO对象：
//
//    glBindVertexArray(cubeVAO);;//使用glBindVertexArray绑定VAO
//
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);//使用glBindBuffer函数把新创建的缓冲绑定到GL_ARRAY_BUFFER目标上
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//调用glBufferData函数，它会把之前定义的顶点数据复制到缓冲的内存中
//
//    //位置属性
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);//告诉OpenGL该如何解析顶点数据（应用到逐个顶点属性上）
//    glEnableVertexAttribArray(0);//以顶点属性位置值作为参数，启用顶点属性；顶点属性默认是禁用的。
//
//    unsigned int lightCubeVAO;
//    glGenVertexArrays(1, &lightCubeVAO);
//    glBindVertexArray(lightCubeVAO);
//
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);
//    // 告诉OpenGL渲染窗口的尺寸大小 前两个参数控制窗口左下角的位置。第三个和第四个参数控制渲染窗口的宽度和高度（像素）。
//    glViewport(0, 0, 1024, 768);
//    // 设置每当窗口调整大小的时候调用这个函数 重新设置opengl渲染窗口尺寸大小
//    glfwSetFramebufferSizeCallback(WindowPtr, Global_Framebuffer_Size_Callback);
//
//    //10.渲染循环glfwWindowShouldClose
//    while (!glfwWindowShouldClose(WindowPtr))
//    {
//        float currentFrame = glfwGetTime();
//        deltaTime = currentFrame - lastFrame;
//        lastFrame = currentFrame;
//        // 检测输入事件
//        Global_ProcessInput(WindowPtr);
//
//        // 清空每一帧屏幕
//        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//清除颜色和深度缓冲
//
//        lightingShader.use();////在glUseProgram函数调用之后，每个着色器调用和渲染调用都会使用这个程序对象（也就是之前写的着色器)了
//        lightingShader.setVec3("objectColor", 0.8f, 0.2f, 0.8f);
//        lightingShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
//
//        glm::mat4 projection = projection = glm::perspective(glm::radians(camera.Zoom), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
//        glm::mat4 view = camera.GetViewMatrix();
//
//        lightingShader.setMat4("projection", projection);
//        lightingShader.setMat4("view", view);
//
//        glm::mat4 model = glm::mat4(1.0f);
//        lightingShader.setMat4("model", model);
//
//        glBindVertexArray(cubeVAO);
//        glDrawArrays(GL_TRIANGLES, 0, 36);
//
//
//        lightCubeShader.use();
//        lightCubeShader.setMat4("projection", projection);
//        lightCubeShader.setMat4("view", view);
//        model = glm::mat4(1.0f);
//        model = glm::translate(model, lightPos);
//        model = glm::scale(model, glm::vec3(0.1f));
//        lightCubeShader.setMat4("model", model);
//
//        glBindVertexArray(lightCubeVAO);
//        glDrawArrays(GL_TRIANGLES, 0, 36);
//
//
//        glfwSwapBuffers(WindowPtr);
//        glfwPollEvents();
//    }
//
//
//    glDeleteVertexArrays(1, &cubeVAO);
//    glDeleteVertexArrays(1, &lightCubeVAO);
//    glDeleteBuffers(1, &VBO);
//    // 循环结束后释放资源glfwTerminate();
//    glfwTerminate();
//    return 0;
//}
//
