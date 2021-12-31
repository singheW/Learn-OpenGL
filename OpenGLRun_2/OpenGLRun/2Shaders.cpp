//
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include <iostream>
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
//}
////0.创建顶点和片段着色器const char* vertexShaderSource =“”
//const char* vertexShaderSource = "#version 330 core\n"
//"layout (location = 0) in vec3 aPos;\n"//位置 属性位置值为0
//"layout (location = 1) in vec3 aColor;\n"//颜色 属性位置值为1
//"out vec3 ourColor;\n"//向片段着色器输出一个颜色
//"void main()\n"
//"{\n"
//"gl_Position = vec4(aPos,1.0);\n"
//"ourColor = aColor;\n"//设置颜色
//"}\0";
//const char* fragmentShaderSource = "#version 330 core\n"
//"out vec4 FragColor;\n"
//"in vec3 ourColor;\n"//从顶点着色器传入颜色
//"void main()\n"
//"{\n"
//"FragColor = vec4(ourColor,1.0f);\n"
//"}\n\0";
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
//    GLFWwindow* WindowPtr = glfwCreateWindow(1024, 768, "LearnOpenGL", nullptr, nullptr);
//    if (WindowPtr == NULL)
//    {
//        std::cout << "Failed to create GLFW window" << std::endl;
//        glfwTerminate();
//        return -1;
//    }
//    glfwMakeContextCurrent(WindowPtr);
//
//    //3.初始化glad:gladLoadGLLoader()glfwGetProcAddress)
//    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//    {
//        std::cout << "Failed to initialize GLAD" << std::endl;
//        return -1;
//    }
//    // 4.创建编译着色器对象:glCreateShader；glShaderSource；glCompileShader；
//    unsigned int vertexShader;
//    vertexShader = glCreateShader(GL_VERTEX_SHADER);
//    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
//    glCompileShader(vertexShader);
//
//    unsigned int fragmentShader;
//    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
//    glCompileShader(fragmentShader);
//
//    // 5.链接激活后删除：glCreateProgram；glAttachShader；glLinkProgram；glDeleteShader
//    unsigned int shaderProgram;
//    shaderProgram = glCreateProgram();
//    glAttachShader(shaderProgram, vertexShader);
//    glAttachShader(shaderProgram, fragmentShader);
//    glLinkProgram(shaderProgram);
//    //链接完毕后删除着色器对象
//    glDeleteShader(vertexShader);
//    glDeleteShader(fragmentShader);
//    // 6.顶点输入 float vertices[] = {}
//    float vertices[] = {
//        //位置                  //颜色
//     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
//    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
//     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // 顶部
//    };
//    //8.创建VBO管理顶点缓存，VAO储存顶点属性，EBO储存索引缓冲
//    unsigned int VBO, VAO;
//    glGenVertexArrays(1, &VAO);//使用glGenVertexArrays函数和一个缓冲ID生成一个VAO对象：
//    glGenBuffers(1, &VBO);//使用glGenBuffers函数和一个缓冲ID生成一个EBO对象：
//    glBindVertexArray(VAO);//使用glBindVertexArray绑定VAO
//
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);;//使用glBindBuffer函数把新创建的缓冲绑定到GL_ARRAY_BUFFER目标上
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//调用glBufferData函数，它会把之前定义的顶点数据复制到缓冲的内存中
//    //9.链接顶点位置以及颜色属性
//    //位置属性
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);//告诉OpenGL该如何解析顶点数据（应用到逐个顶点属性上）
//    glEnableVertexAttribArray(0);//以顶点属性位置值作为参数，启用顶点属性；顶点属性默认是禁用的。
////颜色属性
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));//重新计算步长值。向右移动6个float，其中3个是位置值，另外3个是颜色值。
//    glEnableVertexAttribArray(1);
//
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//    glBindVertexArray(0);
//    // 告诉OpenGL渲染窗口的尺寸大小 前两个参数控制窗口左下角的位置。第三个和第四个参数控制渲染窗口的宽度和高度（像素）。
//    glViewport(0, 0, 1024, 768);
//
//    // 设置每当窗口调整大小的时候调用这个函数 重新设置opengl渲染窗口尺寸大小
//    glfwSetFramebufferSizeCallback(WindowPtr, Global_Framebuffer_Size_Callback);
//
//    //10.渲染循环glfwWindowShouldClose {输入控制；颜色清空；交换缓冲；检查事件}
//    while (!glfwWindowShouldClose(WindowPtr))
//    {
//        // 检测输入事件
//        Global_ProcessInput(WindowPtr);
//
//        // 清空每一帧屏幕
//        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        glUseProgram(shaderProgram);//在glUseProgram函数调用之后，每个着色器调用和渲染调用都会使用这个程序对象（也就是之前写的着色器)了
//        glBindVertexArray(VAO);
//        glDrawArrays(GL_TRIANGLES, 0, 3);//使用glDrawElements时，我们会使用当前绑定的索引缓冲对象中的索引进行绘制：
//
//        // 交换颜色缓冲
//        glfwSwapBuffers(WindowPtr);
//        // 检查事件
//        glfwPollEvents();
//    }
//    glDeleteVertexArrays(1, &VAO);
//    glDeleteBuffers(1, &VBO);
//    glDeleteProgram(shaderProgram);
//    // 循环结束后释放资源glfwTerminate();
//    glfwTerminate();
//
//    return 0;
//}
//
