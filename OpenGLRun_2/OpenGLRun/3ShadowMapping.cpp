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
//void renderScene(const Shader& shader);
//void renderCube();
//void renderQuad();
//
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
//GLboolean shadows = true;
//// meshes
//unsigned int planeVAO;
//
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
//    Shader shader("shadow_mapping.vert", "shadow_mapping.frag");
//    Shader simpleDepthShader("shadow_mapping_depth.vert", "shadow_mapping_depth.frag");
//    Shader debugDepthQuad("debug_quad.vert", "debug_quad_depth.frag");
//
//    // set up vertex data (and buffer(s)) and configure vertex attributes
//    // ------------------------------------------------------------------
//    float planeVertices[] = {
//        // positions            // normals         // texcoords
//         25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
//        -25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
//        -25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,
//
//         25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
//        -25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,
//         25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,  25.0f, 10.0f
//    };
//
//    // plane VAO
//    unsigned int planeVBO;
//    glGenVertexArrays(1, &planeVAO);
//    glGenBuffers(1, &planeVBO);
//    glBindVertexArray(planeVAO);
//    glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(1);
//    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//    glEnableVertexAttribArray(2);
//    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
//    glBindVertexArray(0);
//    
//    unsigned int woodTexture = loadTexture("container2.png");
//    //第一步生成一张深度贴图，深度贴图是从光的透视图里渲染的深度纹理，用它计算阴影。因为需要将场景的渲染结果储存到一个纹理中，所以需要帧缓冲
//    //配置深度贴图FBO
//    const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
//    unsigned int depthMapFBO; //为渲染的深度贴图创建一个帧缓冲对象
//    glGenFramebuffers(1, &depthMapFBO);
//    //创建深度贴图     //创建一个2D纹理,提供给帧缓冲的深度缓冲使用：
//    unsigned int depthMap;
//    glGenTextures(1, &depthMap);
//    glBindTexture(GL_TEXTURE_2D, depthMap);
//    glTexImage2D(GL_TEXTURE_2D, 0,GL_DEPTH_COMPONENT,SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);//纹理格式指定为GL_DEPTH_COMPONENT
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//    GLfloat borderColor[] = { 1.0,1.0,1.0,1.0 };//让所有超出深度贴图的坐标的深度范围是1.0，这样超出坐标永远不再阴影中。
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);//储存一个边框颜色，然后把深度贴图的纹理环绕选项设为GL_CLAMP_TO_BORDER
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
//   glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
//    //将生成的深度纹理作为FBO的深度缓存
//    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);// 绑定为激活的(Active)帧缓冲
//    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0); //将创建好的一个纹理附加到帧缓冲上
//    glDrawBuffer(GL_NONE);//我们需要的只是在从光的透视图下渲染场景时的深度信息，所以不需要颜色缓冲，但不包含颜色缓冲的帧缓冲是不完整的，
//    glReadBuffer(GL_NONE);//所以我们需要告诉opengl不用任何颜色数据进行渲染。我们将调用glDrawBuffer和glReadBuffer把读和绘制设置为GL_NONE做这事
//    glBindFramebuffer(GL_FRAMEBUFFER, 0);//要保证所有的渲染操作在主窗口中有视觉效果，我们需要再次激活默认帧缓冲，将它绑定到0。
//   // glClearColor(0.1f,0.1f,0.1f,1.0f);
//
//    //shader 配置
//    shader.use();
//    shader.setInt("diffuseTexture", 0);
//    shader.setInt("shadowMap", 1);
//    debugDepthQuad.use();
//    debugDepthQuad.setInt("depthMap", 0);
//
//    //灯光信息
//    glm::vec3 lightPos(-2.0f, 4.0f, -1.0f);
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
// 
//        // render
//        // ------
//        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//        //渲染场景深度到贴图（从光源透视）
//        glm::mat4 lightProjection, lightView;
//        glm::mat4 lightSpaceMatrix;
//        float near_plane = 1.0f, far_plane = 7.5f;//因为使用的是一个所有光线都平行的定向光。所以为光源使用正交投影矩阵，透视图将没有任何变形
//        lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f,10.0f,near_plane, far_plane);
//        //创建视图矩阵变换每个物体，把他们变换到从光源视角可见的空间中，使用lookat函数从光源位置看向场景中央
//        lightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
//        //二者相结合为我们提供了一个光空间的变换矩阵，它将每个世界空间坐标变换到光源处所见到的那个空间，这是渲染深度贴图所需要的。
//        lightSpaceMatrix = lightProjection * lightView;//有了light space matrix只要给shader提供光空间的投影和视图矩阵，就能渲染场景了。
//
//        //从视野中的灯光点到渲染场景
//        simpleDepthShader.use();
//        simpleDepthShader.setMat4("lightSpaceMatrix", lightSpaceMatrix);
//
//        glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
//        glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
//        glClear(GL_DEPTH_BUFFER_BIT);
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, woodTexture);
//        renderScene(simpleDepthShader);
//        glBindFramebuffer(GL_FRAMEBUFFER, 0);
//
//        //重置视图
//        glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//        //使用生成的深度/阴影贴图 正常渲染场景
//        glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//        shader.use();
//        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//        glm::mat4 view = camera.GetViewMatrix();
//        shader.setMat4("projection", projection);
//        shader.setMat4("view", view);
//        //set light uniforms
//        shader.setVec3("viewPos",camera.Position);
//        shader.setVec3("lightPos", lightPos);
//        shader.setMat4("lightSpaceMatrix", lightSpaceMatrix);
//        //通过‘空格键’启用/禁用 shadows
//        shader.setInt("shadows", shadows);
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, woodTexture);
//        glActiveTexture(GL_TEXTURE1);
//        glBindTexture(GL_TEXTURE_2D, depthMap);
//        renderScene(shader);
//
//        //渲染深度贴图到quad for visual debugging
//        debugDepthQuad.use();
//        debugDepthQuad.setFloat("near_plane", near_plane);
//        debugDepthQuad.setFloat("far_plane", far_plane);
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, depthMap);
//      //  renderQuad();
//               
//        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
//        // -------------------------------------------------------------------------------
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//
//    // optional: de-allocate all resources once they've outlived their purpose:
//    // ------------------------------------------------------------------------
//
//    glDeleteVertexArrays(1, &planeVAO);
//    glDeleteBuffers(1, &planeVBO);
//
//
//    glfwTerminate();
//    return 0;
//}
//
//void renderScene(const Shader& shader)
//{
//    //地板
//    glm::mat4 model = glm::mat4(1.0f);
//    shader.setMat4("model", model);
//    glBindVertexArray(planeVAO);
//    glDrawArrays(GL_TRIANGLES, 0, 6);
//    //cubes
//    model = glm::mat4(1.0f);
//    model = glm::translate(model, glm::vec3(0.0f, 1.5f, 0.0));
//    model = glm::scale(model, glm::vec3(0.5f));
//    shader.setMat4("model", model);
//    renderCube();
//    model = glm::mat4(1.0f);
//    model = glm::translate(model, glm::vec3(2.0f, 0.0f, 1.0));
//    model = glm::scale(model, glm::vec3(0.5f));
//    shader.setMat4("model", model);
//    renderCube();
//    model = glm::mat4(1.0f);
//    model = glm::translate(model, glm::vec3(2.0f, 0.0f, 1.0));
//    model = glm::scale(model, glm::vec3(0.5f));
//    shader.setMat4("model", model);
//    renderCube();
//    model = glm::mat4(1.0f);
//    model = glm::translate(model, glm::vec3(2.0f, 0.0f, 1.0));
//    model = glm::scale(model, glm::vec3(0.5f));
//    shader.setMat4("model", model);
//    renderCube();
//    model = glm::mat4(1.0f);
//    model = glm::translate(model, glm::vec3(2.0f, 0.0f, 1.0));
//    model = glm::scale(model, glm::vec3(0.5f));
//    shader.setMat4("model", model);
//    renderCube();
//    model = glm::mat4(1.0f);
//    model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 2.0));
//    model = glm::rotate(model, glm::radians(60.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
//    model = glm::scale(model, glm::vec3(0.25));
//    shader.setMat4("model", model);
//    renderCube();
//
//}
//
////rendercube()渲染 标准坐标控件下的 1*1 3D立方体
//
//unsigned int cubeVAO = 0;
//unsigned int cubeVBO = 0;
//void renderCube()
//{
//    // initialize (if necessary)
//    if (cubeVAO == 0)
//    {
//        float vertices[] = {
//            // back face
//            -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
//             1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
//             1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f, // bottom-right         
//             1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
//            -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
//            -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, // top-left
//            // front face
//            -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
//             1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, // bottom-right
//             1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
//             1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
//            -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f, // top-left
//            -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
//            // left face
//            -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
//            -1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-left
//            -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
//            -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
//            -1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-right
//            -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
//            // right face
//             1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
//             1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
//             1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-right         
//             1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
//             1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
//             1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-left     
//            // bottom face
//            -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
//             1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f, // top-left
//             1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
//             1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
//            -1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f, // bottom-right
//            -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
//            // top face
//            -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
//             1.0f,  1.0f , 1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
//             1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f, // top-right     
//             1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
//            -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
//            -1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f  // bottom-left        
//        };
//        glGenVertexArrays(1, &cubeVAO);
//        glGenBuffers(1, &cubeVBO);
//        //填充缓冲
//        glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
//        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//        //链接顶点属性
//        glBindVertexArray(cubeVAO);
//        glEnableVertexAttribArray(0);
//        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//        glEnableVertexAttribArray(1);
//        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//        glEnableVertexAttribArray(2);
//        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
//        glBindBuffer(GL_ARRAY_BUFFER, 0);
//        glBindVertexArray(0);
//
//
//    }
//    //渲染立方体
//    glBindVertexArray(cubeVAO);
//    glDrawArrays(GL_TRIANGLES, 0, 36);
//    glBindVertexArray(0);
//}
////renderQuad() 渲染 标准坐标空间 的 1*1 XY Quad
//unsigned int quadVAO = 0;
//unsigned int quadVBO;
//void renderQuad()
//{
//    if (quadVAO == 0)
//    {
//        float quadVertices[] = {
//            // positions        // texture Coords
//            -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
//            -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
//             1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
//             1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
//        };
//        //设置plane VAO
//        glGenVertexArrays(1, &quadVAO);
//        glGenBuffers(1, &quadVBO);
//        glBindVertexArray(quadVAO);
//        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
//        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
//        glEnableVertexAttribArray(0);
//        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//        glEnableVertexAttribArray(1);
//        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//
//    }
//    glBindVertexArray(quadVAO);
//    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
//    glBindVertexArray(0);
//
//}
//// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
//// ---------------------------------------------------------------------------------------------------------
//bool KeysPressed[1024];
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
//    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
//    {
//        shadows = !shadows;
//        KeysPressed[GLFW_KEY_SPACE] = true;
//        
//    }
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
