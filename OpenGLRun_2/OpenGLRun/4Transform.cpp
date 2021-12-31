 //
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include <iostream>
//#include "stb_image.h"//Texture�����ͷ�ļ�
//
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
//"layout (location = 2) in vec2 aTexCoord;\n"//Texture������������ɫ����Ƭ����ɫ��
//"out vec3 ourColor;\n"//��Ƭ����ɫ�����һ����ɫ
//"out vec2 TexCoord;\n"
//"uniform mat4 transform;\n"//Transform�ڶ���:�޸Ķ�����ɫ���������һ��mat4��uniform������Ȼ�����þ���uniform����λ������
//"void main()\n"
//"{\n"
//"gl_Position = transform * vec4(aPos,1.0);\n"
//"ourColor = aColor;\n"//������ɫ
//"TexCoord = aTexCoord;\n"
//"}\0";
//const char* fragmentShaderSource = "#version 330 core\n"
//"out vec4 FragColor;\n"
//"in vec3 ourColor;\n"//�Ӷ�����ɫ��������ɫ
//"in vec2 TexCoord;\n"
//"uniform sampler2D texture1;\n"//����ԪGL_TEXTURE0Ĭ�����Ǳ�����
//"uniform sampler2D texture2;\n"
//"void main()\n"
//"{\n"
////"FragColor = texture(ourTexture,TexCoord)*vec4(ourColor,1.0);\n"// texture(���������, ��Ӧ����������);
//"FragColor = mix(texture(texture1,TexCoord),texture(texture2,TexCoord),0.2);\n"//mix������Ҫ��������ֵ��Ϊ�������������Ǹ��ݵ����������������Բ�ֵ��0.2�᷵����������Ļ��ɫ��
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
//
//
//
//    // 6.�������� float vertices[] = {}
//    float vertices[] = {//Texture���޸Ķ�������
//        //     ---- λ�� ----       ---- ��ɫ ----     - �������� -
//             0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // ����
//             0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // ����
//            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // ����
//            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // ����
//    };
//    unsigned int indices[] = {
//        0,1,3,
//        1,2,3
//    };
//    //8.����VBO�����㻺�棬VAO���涥�����ԣ�EBO������������
//    unsigned int VBO, VAO, EBO;
//    glGenVertexArrays(1, &VAO);//ʹ��glGenVertexArrays������һ������ID����һ��VAO����
//    glGenBuffers(1, &VBO);//ʹ��glGenBuffers������һ������ID����һ��EBO����
//    glGenBuffers(1, &EBO);
//
//    glBindVertexArray(VAO);//ʹ��glBindVertexArray��VAO
//
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);;//ʹ��glBindBuffer�������´����Ļ���󶨵�GL_ARRAY_BUFFERĿ����
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//����glBufferData�����������֮ǰ����Ķ������ݸ��Ƶ�������ڴ���
//
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//
//    //9.���Ӷ���λ��,��ɫ��������������
//    //λ������
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);//����OpenGL����ν����������ݣ�Ӧ�õ�������������ϣ�
//    glEnableVertexAttribArray(0);//�Զ�������λ��ֵ��Ϊ���������ö������ԣ���������Ĭ���ǽ��õġ�
////��ɫ����
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));//���¼��㲽��ֵ�������ƶ�6��float������3����λ��ֵ������3������ɫֵ��
//    glEnableVertexAttribArray(1);
//    //Texture������������������
//    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
//    glEnableVertexAttribArray(2);
//
//
//    //Texture�����ɰ�������������map�ͷ�����
//    unsigned int texture1, texture2;
//    glGenTextures(1, &texture1);//glGenTextures����������Ҫ�������������������Ȼ������Ǵ����ڵڶ���������unsigned int������
//    glBindTexture(GL_TEXTURE_2D, texture1);//������Ҫ��������֮���κε�����ָ��������õ�ǰ�󶨵�����
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//    int width, height, nrChannels;//Texture������ͼƬ��������
//    stbi_set_flip_vertically_on_load(true);
//    unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
//    if (data)
//    {
//        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);//��������glTexImage2D(����Ŀ�꣬mip���𣬴����ʽ����ߣ�0��Դͼ��ʽ���������ͣ�������ͼ������)
//        glGenerateMipmap(GL_TEXTURE_2D);//Ϊ��ǰ�󶨵������Զ�����������Ҫ�Ķ༶��Զ����
//    }
//    else {
//        std::cout << "Failed to load texture" << std::endl;
//    }
//    stbi_image_free(data);//�������������Ӧ�Ķ༶��Զ������ͷ�ͼ����ڴ�
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
//    //Texture�����ڴ���ͨ��uniform variable �Ͷ�Ӧ��shader������ID
//    glUseProgram(shaderProgram);
//    glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);//ʹ��glUniform1i����ÿ���������ķ�ʽ����OpenGLÿ����ɫ�������������ĸ�����Ԫ��
//    glUniform1i(glGetUniformLocation(shaderProgram, "texture2"), 1);//���ڴ���ʹ�� glGetuniformLocation�������õ��������֣�Ӧ��shader�е�uniform sampler2D variable����������Ӧ����һ�£�����ֻʹ����һ������Ԫ��
//
//    // ����OpenGL��Ⱦ���ڵĳߴ��С ǰ�����������ƴ������½ǵ�λ�á��������͵��ĸ�����������Ⱦ���ڵĿ�Ⱥ͸߶ȣ����أ���
//    glViewport(0, 0, 1024, 768);
//
//    // ����ÿ�����ڵ�����С��ʱ������������ ��������opengl��Ⱦ���ڳߴ��С
//    glfwSetFramebufferSizeCallback(WindowPtr, Global_Framebuffer_Size_Callback);
//
//
//    //
//     //10.��Ⱦѭ��glfwWindowShouldClose {������ƣ���ɫ��գ��������壻����¼�}
//    while (!glfwWindowShouldClose(WindowPtr))
//    {
//        // ��������¼�
//        Global_ProcessInput(WindowPtr);
//
//        // ���ÿһ֡��Ļ
//        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        //Texture�����������
//        glActiveTexture(GL_TEXTURE0);//���ʹ��һ�������Բ��ü��������ܡ����ʹ�ö����������ʹ��ǰ���������ܣ����󶨶�Ӧ������ID
//        glBindTexture(GL_TEXTURE_2D, texture1);
//        glActiveTexture(GL_TEXTURE1);
//        glBindTexture(GL_TEXTURE_2D, texture2);
//
//        glm::mat4 transform = glm::mat4(1.0f);//Transform��һ��:�����任����
//        transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));//translateλ��
//        transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));//ʹ��GLFW��ʱ�亯������ȡ��ͬʱ��ĽǶȡ�������ÿһ�ε����д��������Ӷ���֤�����ܹ����ϸ�����ת�Ƕȡ�
//
//
//     //Transform������:�ѱ任���󴫵ݸ���ɫ����
//        unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");//���Ȳ�ѯuniform�����ĵ�ַ
//        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));//�Ѿ������ݷ��͸���ɫ����glUniformMatrix4fv(uniformλ��ֵ�����;����������Ƿ��û���������������)
//
//        glUseProgram(shaderProgram);//��glUseProgram��������֮��ÿ����ɫ�����ú���Ⱦ���ö���ʹ������������Ҳ����֮ǰд����ɫ��)��
//
//        glBindVertexArray(VAO);
//        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);//ʹ��glDrawElementsʱ�����ǻ�ʹ�õ�ǰ�󶨵�������������е��������л��ƣ�
//
//        // ������ɫ����
//        glfwSwapBuffers(WindowPtr);
//        // ����¼�
//        glfwPollEvents();
//    }
//    glDeleteVertexArrays(1, &VAO);
//    glDeleteBuffers(1, &VBO);
//    glDeleteBuffers(1, &EBO);
//    //glDeleteProgram(shaderProgram);
//    // ѭ���������ͷ���ԴglfwTerminate();
//    glfwTerminate();
//
//    return 0;
//}
