 //
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include <iostream>
//#include "stb_image.h"//Texture：添加头文件
//
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
//"layout (location = 2) in vec2 aTexCoord;\n"//Texture：调整顶点着色器及片段着色器
//"out vec3 ourColor;\n"//向片段着色器输出一个颜色
//"out vec2 TexCoord;\n"
//"uniform mat4 transform;\n"//Transform第二步:修改顶点着色器让其接收一个mat4的uniform变量，然后再用矩阵uniform乘以位置向量
//"void main()\n"
//"{\n"
//"gl_Position = transform * vec4(aPos,1.0);\n"
//"ourColor = aColor;\n"//设置颜色
//"TexCoord = aTexCoord;\n"
//"}\0";
//const char* fragmentShaderSource = "#version 330 core\n"
//"out vec4 FragColor;\n"
//"in vec3 ourColor;\n"//从顶点着色器传入颜色
//"in vec2 TexCoord;\n"
//"uniform sampler2D texture1;\n"//纹理单元GL_TEXTURE0默认总是被激活
//"uniform sampler2D texture2;\n"
//"void main()\n"
//"{\n"
////"FragColor = texture(ourTexture,TexCoord)*vec4(ourColor,1.0);\n"// texture(纹理采样器, 对应的纹理坐标);
//"FragColor = mix(texture(texture1,TexCoord),texture(texture2,TexCoord),0.2);\n"//mix函数需要接受两个值作为参数，并对它们根据第三个参数进行线性插值。0.2会返回两个纹理的混合色。
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
//
//
//
//    // 6.顶点输入 float vertices[] = {}
//    float vertices[] = {//Texture：修改顶点输入
//        //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
//             0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
//             0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
//            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
//            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
//    };
//    unsigned int indices[] = {
//        0,1,3,
//        1,2,3
//    };
//    //8.创建VBO管理顶点缓存，VAO储存顶点属性，EBO储存索引缓冲
//    unsigned int VBO, VAO, EBO;
//    glGenVertexArrays(1, &VAO);//使用glGenVertexArrays函数和一个缓冲ID生成一个VAO对象：
//    glGenBuffers(1, &VBO);//使用glGenBuffers函数和一个缓冲ID生成一个EBO对象：
//    glGenBuffers(1, &EBO);
//
//    glBindVertexArray(VAO);//使用glBindVertexArray绑定VAO
//
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);;//使用glBindBuffer函数把新创建的缓冲绑定到GL_ARRAY_BUFFER目标上
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//调用glBufferData函数，它会把之前定义的顶点数据复制到缓冲的内存中
//
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//
//    //9.链接顶点位置,颜色及纹理坐标属性
//    //位置属性
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);//告诉OpenGL该如何解析顶点数据（应用到逐个顶点属性上）
//    glEnableVertexAttribArray(0);//以顶点属性位置值作为参数，启用顶点属性；顶点属性默认是禁用的。
////颜色属性
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));//重新计算步长值。向右移动6个float，其中3个是位置值，另外3个是颜色值。
//    glEnableVertexAttribArray(1);
//    //Texture：链接纹理坐标属性
//    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
//    glEnableVertexAttribArray(2);
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
//    glUseProgram(shaderProgram);
//    glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);//使用glUniform1i设置每个采样器的方式告诉OpenGL每个着色器采样器属于哪个纹理单元。
//    glUniform1i(glGetUniformLocation(shaderProgram, "texture2"), 1);//在内存中使用 glGetuniformLocation函数设置的纹理名字，应和shader中的uniform sampler2D variable声明的名称应保持一致，除非只使用了一个纹理单元。
//
//    // 告诉OpenGL渲染窗口的尺寸大小 前两个参数控制窗口左下角的位置。第三个和第四个参数控制渲染窗口的宽度和高度（像素）。
//    glViewport(0, 0, 1024, 768);
//
//    // 设置每当窗口调整大小的时候调用这个函数 重新设置opengl渲染窗口尺寸大小
//    glfwSetFramebufferSizeCallback(WindowPtr, Global_Framebuffer_Size_Callback);
//
//
//    //
//     //10.渲染循环glfwWindowShouldClose {输入控制；颜色清空；交换缓冲；检查事件}
//    while (!glfwWindowShouldClose(WindowPtr))
//    {
//        // 检测输入事件
//        Global_ProcessInput(WindowPtr);
//
//        // 清空每一帧屏幕
//        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        //Texture：激活绑定纹理
//        glActiveTexture(GL_TEXTURE0);//如果使用一个，可以不用激活纹理功能。如果使用多个，必须在使用前激活纹理功能，并绑定对应的纹理ID
//        glBindTexture(GL_TEXTURE_2D, texture1);
//        glActiveTexture(GL_TEXTURE1);
//        glBindTexture(GL_TEXTURE_2D, texture2);
//
//        glm::mat4 transform = glm::mat4(1.0f);//Transform第一步:创建变换矩阵
//        transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));//translate位移
//        transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));//使用GLFW的时间函数来获取不同时间的角度。必须在每一次迭代中创建它，从而保证我们能够不断更新旋转角度。
//
//
//     //Transform第三步:把变换矩阵传递给着色器：
//        unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");//首先查询uniform变量的地址
//        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));//把矩阵数据发送给着色器。glUniformMatrix4fv(uniform位置值，发送矩阵数量，是否置换，真正矩阵数据)
//
//        glUseProgram(shaderProgram);//在glUseProgram函数调用之后，每个着色器调用和渲染调用都会使用这个程序对象（也就是之前写的着色器)了
//
//        glBindVertexArray(VAO);
//        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);//使用glDrawElements时，我们会使用当前绑定的索引缓冲对象中的索引进行绘制：
//
//        // 交换颜色缓冲
//        glfwSwapBuffers(WindowPtr);
//        // 检查事件
//        glfwPollEvents();
//    }
//    glDeleteVertexArrays(1, &VAO);
//    glDeleteBuffers(1, &VBO);
//    glDeleteBuffers(1, &EBO);
//    //glDeleteProgram(shaderProgram);
//    // 循环结束后释放资源glfwTerminate();
//    glfwTerminate();
//
//    return 0;
//}
