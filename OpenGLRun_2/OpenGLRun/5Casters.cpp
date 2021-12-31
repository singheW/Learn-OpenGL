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
//
//const unsigned int WIDTH = 1024;
//const unsigned int HEIGHT = 768;
//
//
//Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
//float lastX = WIDTH / 2.0f;
//float lastY = HEIGHT / 2.0f;
//bool firstMouse = true;
//
//float deltaTime = 0.0f; // 当前帧与上一帧的时间差
//float lastFrame = 0.0f; // 上一帧的时间
//glm::vec3 lightPos(1.2f, 1.0f, 2.0f);//光源位置，计算漫反射用
//
//void Global_Framebuffer_Size_Callback(GLFWwindow* window, int width, int height);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void Global_ProcessInput(GLFWwindow* WindowPtr);
//
//void mouse_callback(GLFWwindow* window, double xpos, double ypos)
//{
//	if (firstMouse)
//	{
//		lastX = xpos;
//		lastY = ypos;
//		firstMouse = false;
//	}
//
//	float xoffset = xpos - lastX;
//	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
//
//	lastX = xpos;
//	lastY = ypos;
//
//	camera.ProcessMouseMovement(xoffset, yoffset);
//}
//
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
//{
//	camera.ProcessMouseScroll(yoffset);
//}
//// 调整视口大小framebuffer_size_callback{glViewport()}
//void Global_Framebuffer_Size_Callback(GLFWwindow* WindowPtr, int Width, int Height)
//{
//	glViewport(0, 0, Width, Height);
//}
////输入控制processInput{glfwGetKey();glfwSetWindowShouldClose()}
//void Global_ProcessInput(GLFWwindow* WindowPtr)
//{
//	if (glfwGetKey(WindowPtr, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//	{
//		glfwSetWindowShouldClose(WindowPtr, true);
//	}
//	if (glfwGetKey(WindowPtr, GLFW_KEY_W) == GLFW_PRESS)
//		camera.ProcessKeyboard(FORWARD, deltaTime);
//	if (glfwGetKey(WindowPtr, GLFW_KEY_S) == GLFW_PRESS)
//		camera.ProcessKeyboard(BACKWARD, deltaTime);
//	if (glfwGetKey(WindowPtr, GLFW_KEY_A) == GLFW_PRESS)
//		camera.ProcessKeyboard(LEFT, deltaTime);
//	if (glfwGetKey(WindowPtr, GLFW_KEY_D) == GLFW_PRESS)
//		camera.ProcessKeyboard(RIGHT, deltaTime);
//}
//unsigned int loadTexture(char const* path)//加载纹理贴图函数
//{
//	unsigned int textureID;
//	glGenTextures(1, &textureID);
//
//	int width, height, nrComponents;
//	unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
//	if (data)
//	{
//		GLenum format;
//		if (nrComponents == 1)
//			format = GL_RED;
//		else if (nrComponents == 3)
//			format = GL_RGB;
//		else if (nrComponents == 4)
//			format = GL_RGBA;
//
//		glBindTexture(GL_TEXTURE_2D, textureID);
//		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
//		glGenerateMipmap(GL_TEXTURE_2D);
//
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//		stbi_image_free(data);
//	}
//	else
//	{
//		std::cout << "Texture failed to load at path: " << path << std::endl;
//		stbi_image_free(data);
//	}
//
//	return textureID;
//}
//int main()
//{//初始化glfw并进行配置：glfwInit(); glfwWindowHint
//	// 初始化GLFW
//	glfwInit();
//	// 设定 opengl版本为 3.3
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	// 使用核心模式
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//	// 2.创建窗口：glfwCreateWindow()； glfwSetFramebufferSizeCallback();
//	GLFWwindow* WindowPtr = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
//	if (WindowPtr == NULL)
//	{
//		std::cout << "Failed to create GLFW window" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//	glfwMakeContextCurrent(WindowPtr);
//	glfwSetFramebufferSizeCallback(WindowPtr, Global_Framebuffer_Size_Callback);
//	glfwSetCursorPosCallback(WindowPtr, mouse_callback);//鼠标一移动mouse_callback函数就会被调用：
//	glfwSetScrollCallback(WindowPtr, scroll_callback);//注册鼠标滚轮的回调函数：
//	glfwSetInputMode(WindowPtr, GLFW_CURSOR, GLFW_CURSOR_DISABLED);//隐藏光标，并捕捉(Capture)它
//	//初始化glad:gladLoadGLLoader()glfwGetProcAddress)
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//	{
//		std::cout << "Failed to initialize GLAD" << std::endl;
//		return -1;
//	}
//
//	glEnable(GL_DEPTH_TEST);
//
//	Shader lightingShader("light_casters.vert", "light_casters.frag");
//	//Shader lightingShader("BaseLight-practives3.vs", "BaseLight-practice3.fs");
//	Shader lightCubeShader("light_cube.vs", "light_cube.fs");
//
//	float vertices[] = {
//		// positions          // normals           // texture coords
//		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
//		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
//		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
//		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
//		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
//		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
//
//		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
//		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
//		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
//		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
//		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
//		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
//
//		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
//		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
//		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
//		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
//		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
//		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
//
//		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
//		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
//		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
//		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
//		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
//		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
//
//		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
//		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
//		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
//		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
//		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
//		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
//
//		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
//		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
//		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
//		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
//		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
//		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
//	};
//	glm::vec3 cubePositions[] = {
//	glm::vec3(0.0f,  0.0f,  0.0f),
//	glm::vec3(2.0f,  5.0f, -15.0f),
//	glm::vec3(-1.5f, -2.2f, -2.5f),
//	glm::vec3(-3.8f, -2.0f, -12.3f),
//	glm::vec3(2.4f, -0.4f, -3.5f),
//	glm::vec3(-1.7f,  3.0f, -7.5f),
//	glm::vec3(1.3f, -2.0f, -2.5f),
//	glm::vec3(1.5f,  2.0f, -2.5f),
//	glm::vec3(1.5f,  0.2f, -1.5f),
//	glm::vec3(-1.3f,  1.0f, -1.5f)
//	};
//	//创建VBO管理顶点缓存，VAO储存顶点属性，EBO储存索引缓冲
//	unsigned int VBO, cubeVAO;
//	glGenVertexArrays(1, &cubeVAO);//使用glGenVertexArrays函数和一个缓冲ID生成一个VAO对象：
//	glGenBuffers(1, &VBO);//使用glGenBuffers函数和一个缓冲ID生成一个VBO对象：
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);//使用glBindBuffer函数把新创建的缓冲绑定到GL_ARRAY_BUFFER目标上
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//调用glBufferData函数，它会把之前定义的顶点数据复制到缓冲的内存中
//
//	glBindVertexArray(cubeVAO);;//使用glBindVertexArray绑定VAO
//
//	//位置属性
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);//告诉OpenGL该如何解析顶点数据（应用到逐个顶点属性上）
//	glEnableVertexAttribArray(0);//以顶点属性位置值作为参数，启用顶点属性；顶点属性默认是禁用的。
//	//法线属性
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//	glEnableVertexAttribArray(1);
//	//纹理属性
//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
//	glEnableVertexAttribArray(2);
//
//	unsigned int lightCubeVAO;
//	glGenVertexArrays(1, &lightCubeVAO);
//	glBindVertexArray(lightCubeVAO);
//
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//
//
//	unsigned int diffuseMap = loadTexture("container2.png");
//	unsigned int specularMap = loadTexture("container2_specular.png");
//	//  unsigned int specularMap = loadTexture("lighting_maps_specular_color.png");//第二题：使用彩色的镜面光贴图
//	unsigned int emissionMap = loadTexture("matrix.jpg");
//	lightingShader.use();
//	lightingShader.setInt("material.diffuse", 0);
//	lightingShader.setInt("material.specular", 1);
//	lightingShader.setInt("material.emission", 2);
//
//
//	// 告诉OpenGL渲染窗口的尺寸大小 前两个参数控制窗口左下角的位置。第三个和第四个参数控制渲染窗口的宽度和高度（像素）。
//	glViewport(0, 0, 1024, 768);
//	// 设置每当窗口调整大小的时候调用这个函数 重新设置opengl渲染窗口尺寸大小
//	glfwSetFramebufferSizeCallback(WindowPtr, Global_Framebuffer_Size_Callback);
//
//	//渲染循环glfwWindowShouldClose 
//	while (!glfwWindowShouldClose(WindowPtr))
//	{
//		float currentFrame = glfwGetTime();
//		deltaTime = currentFrame - lastFrame;
//		lastFrame = currentFrame;
//		// 检测输入事件
//		Global_ProcessInput(WindowPtr);
//
//		// 清空每一帧屏幕
//		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//清除颜色和深度缓冲
//
//		//lightPos.x = 1.0f + sin(glfwGetTime()) * 2.0f;//第一题：使用sin或cos函数让光源在场景中来回移动。观察光照随时间的改变
//	   // lightPos.y = sin(glfwGetTime() / 2.0f) * 1.0f;
//
//		lightingShader.use();////在glUseProgram函数调用之后，每个着色器调用和渲染调用都会使用这个程序对象（也就是之前写的着色器)了
//	  //  lightingShader.setVec3("light.position", lightPos);//计算漫反射需要用到光源位置与物品位置的差作为方向向量，拿法向量进而计算
//		//lightingShader.setVec3("light.direction", -0.2f, -1.0f, -0.3f);//（-0.2f, -1.0f, -0.3f)平行光
//		lightingShader.setVec3("viewPos", camera.Position);//计算高光需要观察方向，即相应的摄像机位置坐标，传给片段着色器：
//
//		lightingShader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
//		lightingShader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
//		lightingShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
//		//实现衰减公式中的常数项、一次项和二次项
//		lightingShader.setFloat("light.constant", 1.0f);
//		lightingShader.setFloat("light.linear", 0.09f);
//		lightingShader.setFloat("light.quadratic", 0.032f);
//
//		// lightingShader.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
//		lightingShader.setFloat("material.shininess", 64.0f);
//		lightingShader.setFloat("matrixlight", (1.0 + sin(glfwGetTime())) / 2 + 0.5);
//		lightingShader.setFloat("matrixmove", glfwGetTime());
//
//		//聚光灯：位置向量，方向向量和切光角
//		lightingShader.setVec3("light.position", camera.Position);
//		lightingShader.setVec3("light.direction", camera.Front);
//		lightingShader.setFloat("light.cutOff", glm::cos(glm::radians(12.5f)));
//		lightingShader.setFloat("light.outerCutOff", glm::cos(glm::radians(17.5f)));
//
//		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
//		glm::mat4 view = camera.GetViewMatrix();
//		lightingShader.setMat4("projection", projection);
//		lightingShader.setMat4("view", view);
//
//		glm::mat4 model = glm::mat4(1.0f);
//		float angles = glfwGetTime() * 45.0f;
//		model = glm::rotate(model, glm::radians(angles), glm::vec3(1.0f, 0.3f, 0.5f));
//		lightingShader.setMat4("model", model);
//		//绑定diffuse贴图
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, diffuseMap);
//		//绑定specular贴图
//		glActiveTexture(GL_TEXTURE1);
//		glBindTexture(GL_TEXTURE_2D, specularMap);
//		//绑定emission贴图
//		glActiveTexture(GL_TEXTURE2);
//		glBindTexture(GL_TEXTURE_2D, emissionMap);
//
//		glBindVertexArray(cubeVAO);
//		//glDrawArrays(GL_TRIANGLES, 0, 36); 
//
//		//lightCubeShader.use();
//		//lightCubeShader.setMat4("projection", projection);
//		//lightCubeShader.setMat4("view", view);
//		//
//		//model = glm::mat4(1.0f);
//		//model = glm::translate(model, lightPos);
//		//model = glm::scale(model, glm::vec3(0.2f));
//		//float angle = glfwGetTime() * 25.0f;
//		//model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
//		//lightCubeShader.setMat4("model", model);
//		//
//		for (unsigned int i = 0; i < 10; i++)
//		{
//			glm::mat4 model = glm::mat4(1.0f);
//			model = glm::translate(model, cubePositions[i]);
//			float angle = glfwGetTime() * 10.0f * (i + 1);
//			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
//			lightingShader.setMat4("model", model);
//
//			//   glBindVertexArray(lightCubeVAO);
//			glDrawArrays(GL_TRIANGLES, 0, 36);
//		}
//		//  glBindVertexArray(lightCubeVAO);
//	   //   glDrawArrays(GL_TRIANGLES, 0, 36);
//
//		glfwSwapBuffers(WindowPtr);
//		glfwPollEvents();
//	}
//
//
//	glDeleteVertexArrays(1, &cubeVAO);
//	glDeleteVertexArrays(1, &lightCubeVAO);
//	glDeleteBuffers(1, &VBO);
//	// 循环结束后释放资源glfwTerminate();
//	glfwTerminate();
//	return 0;
//}
