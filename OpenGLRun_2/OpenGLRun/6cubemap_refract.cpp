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
//
//    // build and compile shaders
//    // -------------------------
//    Shader shader("framebuffers.vert", "framebuffers.frag");
//    Shader screenShader("framebuffers_screen.vert", "framebuffers_screen.frag");
//    Shader skyboxShader("skybox.vert", "skybox.frag");
//    Shader cubemapShader("cubemaps.vert", "cubemaps.frag");
//    Model ourModel("nanosuit/nanosuit.obj");
//
//    // set up vertex data (and buffer(s)) and configure vertex attributes
//    // ------------------------------------------------------------------
//    float cubeVertices[] = {
//        // positions       // normal
//     -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//
//    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//
//    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
//    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
//    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
//    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
//    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
//    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
//
//     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
//     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
//     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
//     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
//     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
//     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
//
//    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
//     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
//     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
//     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
//    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
//    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
//
//    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
//     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
//     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
//     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
//    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
//    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
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
//    float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
//        // positions   // texCoords
//        -1.0f,  1.0f,  0.0f, 1.0f,
//        -1.0f, -1.0f,  0.0f, 0.0f,
//         1.0f, -1.0f,  1.0f, 0.0f,
//
//        -1.0f,  1.0f,  0.0f, 1.0f,
//         1.0f, -1.0f,  1.0f, 0.0f,
//         1.0f,  1.0f,  1.0f, 1.0f
//    };
//    float skyboxVertices[] = {
//        // positions          
//        -1.0f,  1.0f, -1.0f,
//        -1.0f, -1.0f, -1.0f,
//         1.0f, -1.0f, -1.0f,
//         1.0f, -1.0f, -1.0f,
//         1.0f,  1.0f, -1.0f,
//        -1.0f,  1.0f, -1.0f,
//
//        -1.0f, -1.0f,  1.0f,
//        -1.0f, -1.0f, -1.0f,
//        -1.0f,  1.0f, -1.0f,
//        -1.0f,  1.0f, -1.0f,
//        -1.0f,  1.0f,  1.0f,
//        -1.0f, -1.0f,  1.0f,
//
//         1.0f, -1.0f, -1.0f,
//         1.0f, -1.0f,  1.0f,
//         1.0f,  1.0f,  1.0f,
//         1.0f,  1.0f,  1.0f,
//         1.0f,  1.0f, -1.0f,
//         1.0f, -1.0f, -1.0f,
//
//        -1.0f, -1.0f,  1.0f,
//        -1.0f,  1.0f,  1.0f,
//         1.0f,  1.0f,  1.0f,
//         1.0f,  1.0f,  1.0f,
//         1.0f, -1.0f,  1.0f,
//        -1.0f, -1.0f,  1.0f,
//
//        -1.0f,  1.0f, -1.0f,
//         1.0f,  1.0f, -1.0f,
//         1.0f,  1.0f,  1.0f,
//         1.0f,  1.0f,  1.0f,
//        -1.0f,  1.0f,  1.0f,
//        -1.0f,  1.0f, -1.0f,
//
//        -1.0f, -1.0f, -1.0f,
//        -1.0f, -1.0f,  1.0f,
//         1.0f, -1.0f, -1.0f,
//         1.0f, -1.0f, -1.0f,
//        -1.0f, -1.0f,  1.0f,
//         1.0f, -1.0f,  1.0f
//    };
//    // cube VAO
//    unsigned int cubeVAO, cubeVBO;
//    glGenVertexArrays(1, &cubeVAO);
//    glGenBuffers(1, &cubeVBO);
//    glBindVertexArray(cubeVAO);
//    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(1);
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
//    //glBindVertexArray(0);
//    // 
//    //// plane VAO
//    //unsigned int planeVAO, planeVBO;
//    //glGenVertexArrays(1, &planeVAO);
//    //glGenBuffers(1, &planeVBO);
//    //glBindVertexArray(planeVAO);
//    //glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
//    //glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);
//    //glEnableVertexAttribArray(0);
//    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//    //glEnableVertexAttribArray(1);
//    //glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//    //glBindVertexArray(0);
//
//    ////screen quad VAO
//    //unsigned int quadVAO, quadVBO;
//    //glGenVertexArrays(1, &quadVAO);
//    //glGenBuffers(1, &quadVBO);
//    //glBindVertexArray(quadVAO);
//    //glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
//    //glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
//    //glEnableVertexAttribArray(0);
//    //glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
//    //glEnableVertexAttribArray(1);
//    //glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
//
//    //skybox
//    unsigned int skyboxVAO, skyboxVBO;
//    glGenVertexArrays(1, &skyboxVAO);
//    glGenBuffers(1, &skyboxVBO);
//    glBindVertexArray(skyboxVAO);
//    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//    // load textures
//    // -------------
//    unsigned int cubeTexture = loadTexture("container.jpg");
//    unsigned int floorTexture = loadTexture("metal.jpeg");
//
//
//    vector<std::string>faces
//    {
//        "skybox/right.jpg",
//        "skybox/left.jpg",
//        "skybox/top.jpg",
//        "skybox/bottom.jpg",
//        "skybox/front.jpg",
//        "skybox/back.jpg"
//    };
//    unsigned int cubemapTexture = loadCubemap(faces);
//
//    // shader configuration
//    // --------------------
//    shader.use();
//    shader.setInt("texture1", 0);
//
//    screenShader.use();
//    screenShader.setInt("screenTexture", 0);
//
//    skyboxShader.use();
//    skyboxShader.setInt("skybox", 0);
//    //将场景渲染到一个附加到帧缓冲对象上的颜色纹理中，之后将在一个横跨整个屏幕的四边形上绘制这个纹理。
//    // 
//   // //创建一个帧缓冲对象，并绑定它
//   // unsigned int framebuffer;
//   // glGenFramebuffers(1, &framebuffer);
//   // glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);// 绑定为激活的(Active)帧缓冲
//   ////为帧缓冲创建一个纹理,将它作为一个颜色附件附加到帧缓冲上
//   // unsigned int texture;
//   // glGenTextures(1, &texture);
//   // glBindTexture(GL_TEXTURE_2D, texture);
//   // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
//   // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//   // glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//   // //将创建好的一个纹理附加到帧缓冲上
//   // glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
//
//   // //我们还希望OpenGL能够进行深度测试（如果你需要的话还有模板测试），所以我们还需要添加一个深度（和模板）附件到帧缓冲中。
//   // // 
//   // //创建一个渲染缓冲对象
//   // unsigned int rbo;
//   // glGenRenderbuffers(1, &rbo);
//   // glBindRenderbuffer(GL_RENDERBUFFER, rbo);//绑定这个渲染缓冲对象，让之后所有的渲染缓冲操作影响当前的rbo
//   // glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCR_WIDTH, SCR_HEIGHT);//创建一个深度和模板渲染缓冲对象
//   // //创建一个渲染缓冲对象和纹理对象类似，但不是纹理那样的通用数据缓冲，选择GL_DEPTH24_STENCIL8作为内部格式，它封装了24位的深度和8位的模板缓冲。
//   // glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);//完成帧缓冲之前的最后一步，将rbo附加到帧缓冲的深度和模板附件上：
//
//   // //最后，检查帧缓冲是否是完整的，如果不是，打印错误信息。
//   // if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)//如果它返回的是GL_FRAMEBUFFER_COMPLETE，帧缓冲就是完整的
//   //     cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << endl;
//   // //为渲染缓冲对象分配了足够的内存之后，可以解绑这个渲染缓冲。解绑帧缓冲，保证我们不会不小心渲染到错误的帧缓冲上。
//   // glBindFramebuffer(GL_FRAMEBUFFER, 0);//。要保证所有的渲染操作在主窗口中有视觉效果，我们需要再次激活默认帧缓冲，将它绑定到0。
//
//   //// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//使用线框模式
//
//
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
//        //第一阶段（Pass)
//        // 
//        //绑定到帧缓冲，绘制场景
//       // glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
//       // glEnable(GL_DEPTH_TEST);
//
//        // render
//        // ------
//        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//        //cubemap 反射
//        cubemapShader.use();
//        glm::mat4 model = glm::mat4(1.0f);
//        glm::mat4 view = camera.GetViewMatrix();
//        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//        model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
//
//        cubemapShader.setMat4("view", view);
//        cubemapShader.setMat4("model", model);
//        cubemapShader.setMat4("projection", projection);
//        cubemapShader.setVec3("cameraPos", camera.Position);
//
//        ourModel.Draw(cubemapShader);
//
//
//        glBindVertexArray(cubeVAO);
//        glActiveTexture(GL_TEXTURE0);
//        // glBindTexture(GL_TEXTURE_2D, cubeTexture);
//        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
//        glDrawArrays(GL_TRIANGLES, 0, 36);
//        glBindVertexArray(0);
//
//
//        /*    shader.use();
//            glm::mat4 model = glm::mat4(1.0f);
//            glm::mat4 view = camera.GetViewMatrix();
//            glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//            shader.setMat4("view", view);
//            shader.setMat4("projection", projection);
//            shader.setVec3("cameraPos", camera.Position);
//            // cubes
//
//            model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
//            shader.setMat4("model", model);
//            glDrawArrays(GL_TRIANGLES, 0, 36);
//            model = glm::mat4(1.0f);
//            model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
//            shader.setMat4("model", model);
//           */
//
//           //将天空盒移到最远
//        glDepthFunc(GL_LEQUAL);
//        skyboxShader.use();
//        view = glm::mat4(glm::mat3(camera.GetViewMatrix()));
//        skyboxShader.setMat4("view", view);
//        skyboxShader.setMat4("projection", projection);
//        //将天空盒变为场景中的第一个渲染的物体，并且禁用深度写入。这样天空盒就会永远被绘制在其它物体的背后了。
//        //glDepthMask(GL_FALSE);
//        glBindVertexArray(skyboxVAO);
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
//        glDrawArrays(GL_TRIANGLES, 0, 36);
//        glBindVertexArray(0);
//        glDepthFunc(GL_LESS);
//
//        //第二处理阶段
//        //绑定默认帧缓冲绘制四边形
//       // glBindFramebuffer(GL_FRAMEBUFFER, 0);//返回默认
//       // glDisable(GL_DEPTH_TEST);//绘制一个简单的四边形，并不需要关系深度测试。
//
//      //  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
//      //  glClear(GL_COLOR_BUFFER_BIT);
//
//      //  screenShader.use();
//      //  glBindVertexArray(quadVAO);
//      //  glBindTexture(GL_TEXTURE_2D, texture);
//     //   glDrawArrays(GL_TRIANGLES, 0, 6);
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
//    //glDeleteVertexArrays(1, &planeVAO);
//    //glDeleteVertexArrays(1, &quadVAO);
//    glDeleteVertexArrays(1, &skyboxVAO);
//    glDeleteBuffers(1, &cubeVBO);//完成所有的帧缓冲操作之后，删除这个帧缓冲对象
//    //glDeleteBuffers(1, &planeVBO);
//    //glDeleteBuffers(1, &quadVBO);
//    glDeleteBuffers(1, &skyboxVBO);
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
//unsigned int loadCubemap(vector<std::string> faces)
//{
//    unsigned int textureID;
//    glGenTextures(1, &textureID);
//    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
//
//    int width, height, nrComponents;
//
//    for (unsigned int i = 0; i < faces.size(); i++)
//    {
//        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrComponents, 0);
//        if (data)
//        {
//            glTexImage2D(
//                GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
//                0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
//            );
//            stbi_image_free(data);
//        }
//        else
//        {
//            std::cout << "cubemap texture failed to load at path:" << faces[i] << std::endl;
//            stbi_image_free(data);
//        }
//    }
//
//    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
//
//    return textureID;
//}
