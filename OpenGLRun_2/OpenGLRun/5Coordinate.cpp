//
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include "stb_image.h"//Texture�����ͷ�ļ�
//
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//#include "shader_m.h"
//
//#include <iostream>
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
//    //8.����VBO�����㻺�棬VAO���涥�����ԣ�EBO������������
//    unsigned int VBO, VAO;
//    glGenVertexArrays(1, &VAO);//ʹ��glGenVertexArrays������һ������ID����һ��VAO����
//    glGenBuffers(1, &VBO);//ʹ��glGenBuffers������һ������ID����һ��EBO����
//
//    glBindVertexArray(VAO);//ʹ��glBindVertexArray��VAO
//
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);;//ʹ��glBindBuffer�������´����Ļ���󶨵�GL_ARRAY_BUFFERĿ����
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//����glBufferData�����������֮ǰ����Ķ������ݸ��Ƶ�������ڴ���
//
//    //9.���Ӷ���λ��,��ɫ��������������
//    //λ������
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);//����OpenGL����ν����������ݣ�Ӧ�õ�������������ϣ�
//    glEnableVertexAttribArray(0);//�Զ�������λ��ֵ��Ϊ���������ö������ԣ���������Ĭ���ǽ��õġ�
//    //Texture������������������
//    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//    glEnableVertexAttribArray(1);
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
//    ourShader.use();
//    ourShader.setInt("texture1", 0);
//    ourShader.setInt("texture2", 1);
//    // ����OpenGL��Ⱦ���ڵĳߴ��С ǰ�����������ƴ������½ǵ�λ�á��������͵��ĸ�����������Ⱦ���ڵĿ�Ⱥ͸߶ȣ����أ���
//    glViewport(0, 0, 1024, 768);
//
//    // ����ÿ�����ڵ�����С��ʱ������������ ��������opengl��Ⱦ���ڳߴ��С
//    glfwSetFramebufferSizeCallback(WindowPtr, Global_Framebuffer_Size_Callback);
//
//    //10.��Ⱦѭ��glfwWindowShouldClose
//    while (!glfwWindowShouldClose(WindowPtr))
//    {
//        // ��������¼�
//        Global_ProcessInput(WindowPtr);
//
//        // ���ÿһ֡��Ļ
//        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//�����ɫ����Ȼ���
//        //Texture�����������
//        glActiveTexture(GL_TEXTURE0);//���ʹ��һ�������Բ��ü��������ܡ����ʹ�ö����������ʹ��ǰ���������ܣ����󶨶�Ӧ������ID
//        glBindTexture(GL_TEXTURE_2D, texture1);
//        glActiveTexture(GL_TEXTURE1);
//        glBindTexture(GL_TEXTURE_2D, texture2);
//
//        ourShader.use();//��glUseProgram��������֮��ÿ����ɫ�����ú���Ⱦ���ö���ʹ������������Ҳ����֮ǰд����ɫ��)��
//
//        glm::mat4 view = glm::mat4(1.0f);
//        glm::mat4 projection = glm::mat4(1.0f);
//        projection = glm::perspective(glm::radians(75.0f),( (float)width / (float)height)*5/4, 0.1f, 100.0f);
//        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -1.50f));
//
//        ourShader.setMat4("projection", projection);
//        ourShader.setMat4("view", view);
//
//        glBindVertexArray(VAO);
//        for (unsigned int i = 0; i < 10; i++)
//        {
//                    glm::mat4 model = glm::mat4(1.0f);
//                    model = glm::translate(model, cubePositions[i]);
//                    float angle = 20.0f * i;
//                    if (i % 3 == 0)    angle = glfwGetTime() * 25.0f;
//                    model = glm::rotate(model,  glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
//                    ourShader.setMat4("model", model);
//
//                    glDrawArrays(GL_TRIANGLES, 0, 36);
//        }
//
//        glfwSwapBuffers(WindowPtr);
//        glfwPollEvents();
//    }
//
//
//    glDeleteVertexArrays(1, &VAO);
//    glDeleteBuffers(1, &VBO);
//    // ѭ���������ͷ���ԴglfwTerminate();
//    glfwTerminate();
//    return 0;
//}
