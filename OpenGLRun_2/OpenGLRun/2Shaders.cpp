//
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include <iostream>
//// �����ӿڴ�Сframebuffer_size_callback{glViewport()}
//void Global_Framebuffer_Size_Callback(GLFWwindow* WindowPtr, int Width, int Height)
//{
//    glViewport(0, 0, Width, Height);
//}
////�������processInput{glfwGetKey();glfwSetWindowShouldClose()}
//void Global_ProcessInput(GLFWwindow* WindowPtr)
//{
//    if (glfwGetKey(WindowPtr, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//    {
//        // ESC �˳�
//        glfwSetWindowShouldClose(WindowPtr, true);
//    }
//}
////0.���������Ƭ����ɫ��const char* vertexShaderSource =����
//const char* vertexShaderSource = "#version 330 core\n"
//"layout (location = 0) in vec3 aPos;\n"//λ�� ����λ��ֵΪ0
//"layout (location = 1) in vec3 aColor;\n"//��ɫ ����λ��ֵΪ1
//"out vec3 ourColor;\n"//��Ƭ����ɫ�����һ����ɫ
//"void main()\n"
//"{\n"
//"gl_Position = vec4(aPos,1.0);\n"
//"ourColor = aColor;\n"//������ɫ
//"}\0";
//const char* fragmentShaderSource = "#version 330 core\n"
//"out vec4 FragColor;\n"
//"in vec3 ourColor;\n"//�Ӷ�����ɫ��������ɫ
//"void main()\n"
//"{\n"
//"FragColor = vec4(ourColor,1.0f);\n"
//"}\n\0";
//
//int main()
//{//1.��ʼ��glfw���������ã�glfwInit(); glfwWindowHint
//    // ��ʼ��GLFW
//    glfwInit();
//    // �趨 opengl�汾Ϊ 3.3
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    // ʹ�ú���ģʽ
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//    // 2.�������ڣ�glfwCreateWindow()�� glfwSetFramebufferSizeCallback();
//    GLFWwindow* WindowPtr = glfwCreateWindow(1024, 768, "LearnOpenGL", nullptr, nullptr);
//    if (WindowPtr == NULL)
//    {
//        std::cout << "Failed to create GLFW window" << std::endl;
//        glfwTerminate();
//        return -1;
//    }
//    glfwMakeContextCurrent(WindowPtr);
//
//    //3.��ʼ��glad:gladLoadGLLoader()glfwGetProcAddress)
//    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//    {
//        std::cout << "Failed to initialize GLAD" << std::endl;
//        return -1;
//    }
//    // 4.����������ɫ������:glCreateShader��glShaderSource��glCompileShader��
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
//    // 5.���Ӽ����ɾ����glCreateProgram��glAttachShader��glLinkProgram��glDeleteShader
//    unsigned int shaderProgram;
//    shaderProgram = glCreateProgram();
//    glAttachShader(shaderProgram, vertexShader);
//    glAttachShader(shaderProgram, fragmentShader);
//    glLinkProgram(shaderProgram);
//    //������Ϻ�ɾ����ɫ������
//    glDeleteShader(vertexShader);
//    glDeleteShader(fragmentShader);
//    // 6.�������� float vertices[] = {}
//    float vertices[] = {
//        //λ��                  //��ɫ
//     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // ����
//    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // ����
//     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // ����
//    };
//    //8.����VBO�����㻺�棬VAO���涥�����ԣ�EBO������������
//    unsigned int VBO, VAO;
//    glGenVertexArrays(1, &VAO);//ʹ��glGenVertexArrays������һ������ID����һ��VAO����
//    glGenBuffers(1, &VBO);//ʹ��glGenBuffers������һ������ID����һ��EBO����
//    glBindVertexArray(VAO);//ʹ��glBindVertexArray��VAO
//
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);;//ʹ��glBindBuffer�������´����Ļ���󶨵�GL_ARRAY_BUFFERĿ����
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//����glBufferData�����������֮ǰ����Ķ������ݸ��Ƶ�������ڴ���
//    //9.���Ӷ���λ���Լ���ɫ����
//    //λ������
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);//����OpenGL����ν����������ݣ�Ӧ�õ�������������ϣ�
//    glEnableVertexAttribArray(0);//�Զ�������λ��ֵ��Ϊ���������ö������ԣ���������Ĭ���ǽ��õġ�
////��ɫ����
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));//���¼��㲽��ֵ�������ƶ�6��float������3����λ��ֵ������3������ɫֵ��
//    glEnableVertexAttribArray(1);
//
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//    glBindVertexArray(0);
//    // ����OpenGL��Ⱦ���ڵĳߴ��С ǰ�����������ƴ������½ǵ�λ�á��������͵��ĸ�����������Ⱦ���ڵĿ�Ⱥ͸߶ȣ����أ���
//    glViewport(0, 0, 1024, 768);
//
//    // ����ÿ�����ڵ�����С��ʱ������������ ��������opengl��Ⱦ���ڳߴ��С
//    glfwSetFramebufferSizeCallback(WindowPtr, Global_Framebuffer_Size_Callback);
//
//    //10.��Ⱦѭ��glfwWindowShouldClose {������ƣ���ɫ��գ��������壻����¼�}
//    while (!glfwWindowShouldClose(WindowPtr))
//    {
//        // ��������¼�
//        Global_ProcessInput(WindowPtr);
//
//        // ���ÿһ֡��Ļ
//        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        glUseProgram(shaderProgram);//��glUseProgram��������֮��ÿ����ɫ�����ú���Ⱦ���ö���ʹ������������Ҳ����֮ǰд����ɫ��)��
//        glBindVertexArray(VAO);
//        glDrawArrays(GL_TRIANGLES, 0, 3);//ʹ��glDrawElementsʱ�����ǻ�ʹ�õ�ǰ�󶨵�������������е��������л��ƣ�
//
//        // ������ɫ����
//        glfwSwapBuffers(WindowPtr);
//        // ����¼�
//        glfwPollEvents();
//    }
//    glDeleteVertexArrays(1, &VAO);
//    glDeleteBuffers(1, &VBO);
//    glDeleteProgram(shaderProgram);
//    // ѭ���������ͷ���ԴglfwTerminate();
//    glfwTerminate();
//
//    return 0;
//}
//
