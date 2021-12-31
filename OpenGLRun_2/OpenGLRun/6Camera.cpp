//
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include "stb_image.h"//Texture：添加头文件
//
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//#include "shader_m.h"
//
//#include <iostream>
//glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
//glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
//glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
//float deltaTime = 0.0f; // 当前帧与上一帧的时间差
//float lastFrame = 0.0f; // 上一帧的时间
//
//bool firstMouse = true;
//float yaw = -90.0f;
//float pitch = 0.0f;
//float lastX = 800.0f / 2.0;
//float lastY = 600.0 / 2.0;
//float fov = 45.0f;
//void mouse_callback(GLFWwindow* window, double xpos, double ypos)////为了计算俯仰角和偏航角，我们需要让GLFW监听鼠标移动事件。
//{
//    if (firstMouse)//如果第一次获取鼠标输入，那么把鼠标的初始位置更新为xpos和ypos值，这样就能解决窗口第一次获取焦点的时候摄像机会突然跳一下
//    {
//        lastX = xpos;
//        lastY = ypos;
//        firstMouse = false;
//    }
//    //计算当前帧和上一帧鼠标位置的偏移量：
//    float xoffset = xpos - lastX;
//    float yoffset = lastY - ypos;
//    lastX = xpos;
//    lastY = ypos;
//    //我们把偏移量乘以了sensitivity（灵敏度）值。如果我们忽略这个值，鼠标移动就会太大了；
//    float sensitivity = 0.1f;
//    xoffset *= sensitivity;
//    yoffset *= sensitivity;
//    //把偏移量加到全局变量pitch和yaw上：
//    yaw += xoffset;
//    pitch += yoffset;
//    //给摄像机添加一些限制，这样摄像机就不会发生奇怪的移动了
//    if (pitch > 89.0f)
//        pitch = 89.0f;
//    if (pitch < -89.0f)
//        pitch = -89.0f;
//    //通过俯仰角和偏航角来计算以得到真正的方向向量：
//    glm::vec3 front;
//    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));//把俯仰角和偏航角转化为用来自由旋转视角的摄像机的3维方向向量
//    front.y = sin(glm::radians(pitch));
//    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
//    cameraFront = glm::normalize(front);
//}
//
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)//一个鼠标滚轮的回调函数：
//{//yoffset值代表我们竖直滚动的大小。当scroll_callback函数被调用后，我们改变全局变量fov变量的内容。因为45.0f是默认的视野值，我们将会把缩放级别(Zoom Level)限制在1.0f到45.0f。
//    fov -= (float)yoffset;
//    if (fov < 1.0f)
//        fov = 1.0f;
//    if (fov > 45.0f)
//        fov = 45.0f;
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
//        // ESC 退出
//        glfwSetWindowShouldClose(WindowPtr, true);
//    }
//
//    float cameraSpeed = 2.5 * deltaTime;
//    if (glfwGetKey(WindowPtr, GLFW_KEY_W) == GLFW_PRESS)
//        cameraPos += cameraSpeed * cameraFront;
//    if (glfwGetKey(WindowPtr, GLFW_KEY_S) == GLFW_PRESS)
//        cameraPos -= cameraSpeed * cameraFront;
//    if (glfwGetKey(WindowPtr, GLFW_KEY_A) == GLFW_PRESS)
//        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
//    if (glfwGetKey(WindowPtr, GLFW_KEY_D) == GLFW_PRESS)
//        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
//}
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
//    GLFWwindow* WindowPtr = glfwCreateWindow(1024, 768, "LearnOpenGL", nullptr, nullptr);
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
//    Shader ourShader("coordinate_systems.vs", "coordinate_systems.fs");
//
//
//    float vertices[] = {
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
//    // world space positions of our cubes
//    glm::vec3 cubePositions[] = {
//        glm::vec3(0.0f,  0.0f,  0.0f),
//        glm::vec3(2.0f,  5.0f, -15.0f),
//        glm::vec3(-1.5f, -2.2f, -2.5f),
//        glm::vec3(-3.8f, -2.0f, -12.3f),
//        glm::vec3(2.4f, -0.4f, -3.5f),
//        glm::vec3(-1.7f,  3.0f, -7.5f),
//        glm::vec3(1.3f, -2.0f, -2.5f),
//        glm::vec3(1.5f,  2.0f, -2.5f),
//        glm::vec3(1.5f,  0.2f, -1.5f),
//        glm::vec3(-1.3f,  1.0f, -1.5f)
//    };
//    //8.创建VBO管理顶点缓存，VAO储存顶点属性，EBO储存索引缓冲
//    unsigned int VBO, VAO;
//    glGenVertexArrays(1, &VAO);//使用glGenVertexArrays函数和一个缓冲ID生成一个VAO对象：
//    glGenBuffers(1, &VBO);//使用glGenBuffers函数和一个缓冲ID生成一个EBO对象：
//
//    glBindVertexArray(VAO);//使用glBindVertexArray绑定VAO
//
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);;//使用glBindBuffer函数把新创建的缓冲绑定到GL_ARRAY_BUFFER目标上
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//调用glBufferData函数，它会把之前定义的顶点数据复制到缓冲的内存中
//
//    //9.链接顶点位置,颜色及纹理坐标属性
//    //位置属性
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);//告诉OpenGL该如何解析顶点数据（应用到逐个顶点属性上）
//    glEnableVertexAttribArray(0);//以顶点属性位置值作为参数，启用顶点属性；顶点属性默认是禁用的。
//    //Texture：链接纹理坐标属性
//    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//    glEnableVertexAttribArray(1);
//
//
//    //Texture：生成绑定配置载入生成map释放纹理
//    unsigned int texture1, texture2;
//    glGenTextures(1, &texture1);//glGenTextures函数首先需要输入生成纹理的数量，然后把它们储存在第二个参数的unsigned int数组中
//    glBindTexture(GL_TEXTURE_2D, texture1);//我们需要绑定它，让之后任何的纹理指令都可以配置当前绑定的纹理
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//    int width, height, nrChannels;//Texture：载入图片生成纹理
//    stbi_set_flip_vertically_on_load(true);
//    unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
//    if (data)
//    {
//        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);//生成纹理，glTexImage2D(纹理目标，mip级别，储存格式，宽高，0，源图格式和数据类型，真正的图像数据)
//        glGenerateMipmap(GL_TEXTURE_2D);//为当前绑定的纹理自动生成所有需要的多级渐远纹理
//    }
//    else {
//        std::cout << "Failed to load texture" << std::endl;
//    }
//    stbi_image_free(data);//生成了纹理和相应的多级渐远纹理后，释放图像的内存
//
//    glGenTextures(1, &texture2);
//    glBindTexture(GL_TEXTURE_2D, texture2);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//    data = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);
//    if (data)
//    {
//        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
//        glGenerateMipmap(GL_TEXTURE_2D);
//    }
//    else {
//        std::cout << "Failed to load texture" << std::endl;
//    }
//    stbi_image_free(data);
//    //Texture：在内存中通过uniform variable 和对应的shader关联此ID
//    ourShader.use();
//    ourShader.setInt("texture1", 0);
//    ourShader.setInt("texture2", 1);
//    // 告诉OpenGL渲染窗口的尺寸大小 前两个参数控制窗口左下角的位置。第三个和第四个参数控制渲染窗口的宽度和高度（像素）。
//    glViewport(0, 0, 1024, 768);
//    // 设置每当窗口调整大小的时候调用这个函数 重新设置opengl渲染窗口尺寸大小
//    glfwSetFramebufferSizeCallback(WindowPtr, Global_Framebuffer_Size_Callback);
//
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
//        //Texture：激活绑定纹理
//        glActiveTexture(GL_TEXTURE0);//如果使用一个，可以不用激活纹理功能。如果使用多个，必须在使用前激活纹理功能，并绑定对应的纹理ID
//        glBindTexture(GL_TEXTURE_2D, texture1);
//        glActiveTexture(GL_TEXTURE1);
//        glBindTexture(GL_TEXTURE_2D, texture2);
//
//        ourShader.use();//在glUseProgram函数调用之后，每个着色器调用和渲染调用都会使用这个程序对象（也就是之前写的着色器)了
//
//
//        glm::mat4 projection = glm::mat4(1.0f);
//        //projection = glm::perspective(glm::radians(75.0f), ((float)width / (float)height) * 5 / 4, 0.1f, 100.0f);
//        projection = glm::perspective(glm::radians(fov), 800.0f / 600.0f, 0.1f, 100.0f);    //在每一帧都必须把透视投影矩阵上传到GPU，但现在使用fov变量作为它的视野：
//
//        glm::mat4 view;
//        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
//
//        ourShader.setMat4("projection", projection);
//        ourShader.setMat4("view", view);
//
//        glBindVertexArray(VAO);
//        for (unsigned int i = 0; i < 10; i++)
//        {
//
//            glm::mat4 model = glm::mat4(1.0f);
//            model = glm::translate(model, cubePositions[i]);
//            float angle = 20.0f * i;
//           // if (i % 3 == 0)    angle = glfwGetTime() * 25.0f;
//            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
//            ourShader.setMat4("model", model);
//
//            glDrawArrays(GL_TRIANGLES, 0, 36);
//        }
//
//        glfwSwapBuffers(WindowPtr);
//        glfwPollEvents();
//    }
//
//
//    glDeleteVertexArrays(1, &VAO);
//    glDeleteBuffers(1, &VBO);
//    // 循环结束后释放资源glfwTerminate();
//    glfwTerminate();
//    return 0;
//}
