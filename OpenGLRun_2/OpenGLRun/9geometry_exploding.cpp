//
//#include<filesystem>
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include "stb_image.h"//Texture：添加头文件
//
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
//#include "shader_m.h"
//#include "camera.h"
//#include <iostream>
//#include "model.h"
//
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
//	//在模型加载前告诉stb_image.h 加载纹理时翻转Y轴 
//	//stbi_set_flip_vertically_on_load(true);
//	glEnable(GL_DEPTH_TEST);
//
//	Shader shader("default.vert", "default.frag");
//	Shader ourShader("geometry_exploding.vert", "geometry_exploding.frag","geometry_exploding.geom");
//	Model ourModel("nanosuit/nanosuit.obj");
//
//
//	glm::vec3 pointLightPositions[] = {
//	   glm::vec3(0.7f,  0.2f,  2.0f),
//	   glm::vec3(2.3f, -3.3f, -4.0f),
//	   glm::vec3(-4.0f,  2.0f, -12.0f),
//	   glm::vec3(0.0f,  0.0f, -3.0f)
//	};
//	glm::vec3 pointLightColors[] = {
//	glm::vec3(1.0f, 0.6f, 0.0f),
//	glm::vec3(1.0f, 0.0f, 0.0f),
//	glm::vec3(1.0f, 1.0, 0.0),
//	glm::vec3(0.2f, 0.2f, 1.0f)
//	};
//
//	// 告诉OpenGL渲染窗口的尺寸大小 前两个参数控制窗口左下角的位置。第三个和第四个参数控制渲染窗口的宽度和高度（像素）。
//	glViewport(0, 0, 1024, 768);
//	// 设置每当窗口调整大小的时候调用这个函数 重新设置opengl渲染窗口尺寸大小
//	glfwSetFramebufferSizeCallback(WindowPtr, Global_Framebuffer_Size_Callback);
//
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
//		glClearColor(0.75f, 0.52f, 0.3f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//清除颜色和深度缓冲
//
//		//lightPos.x = 1.0f + sin(glfwGetTime()) * 2.0f;//第一题：使用sin或cos函数让光源在场景中来回移动。观察光照随时间的改变
//	   // lightPos.y = sin(glfwGetTime() / 2.0f) * 1.0f;
//
//		//人
//		{
//
//		ourShader.use();
//		// 方向光
//		ourShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
//		ourShader.setVec3("dirLight.ambient", 0.3f, 0.24f, 0.14f);
//		ourShader.setVec3("dirLight.diffuse", 0.7f, 0.42f, 0.26f);
//		ourShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
//		// 点光源1
//		ourShader.setVec3("pointLights[0].position", pointLightPositions[0]);
//		ourShader.setVec3("pointLights[0].ambient", 0.0f, 0.0f, 0.0f);
//		ourShader.setVec3("pointLights[0].diffuse", 1.0f, 1.0f, 1.0f);
//		ourShader.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
//		ourShader.setFloat("pointLights[0].constant", 1.0f);
//		ourShader.setFloat("pointLights[0].linear", 0.09);
//		ourShader.setFloat("pointLights[0].quadratic", 0.032);
//		// 点光源2
//		ourShader.setVec3("pointLights[1].position", pointLightPositions[1]);
//		ourShader.setVec3("pointLights[1].ambient", 0.0f, 0.0f, 0.0f);
//		ourShader.setVec3("pointLights[1].diffuse", 1.0f, 1.0f, 1.0f);
//		ourShader.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
//		ourShader.setFloat("pointLights[1].constant", 1.0f);
//		ourShader.setFloat("pointLights[1].linear", 0.09);
//		ourShader.setFloat("pointLights[1].quadratic", 0.032);
//		// 点光源3
//		ourShader.setVec3("pointLights[2].position", pointLightPositions[2]);
//		ourShader.setVec3("pointLights[2].ambient", 0.0f, 0.0f, 0.0f);
//		ourShader.setVec3("pointLights[2].diffuse", 1.0f, 1.0f, 1.0f);
//		ourShader.setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
//		ourShader.setFloat("pointLights[2].constant", 1.0f);
//		ourShader.setFloat("pointLights[2].linear", 0.09);
//		ourShader.setFloat("pointLights[2].quadratic", 0.032);
//		// 点光源4
//		ourShader.setVec3("pointLights[3].position", pointLightPositions[3]);
//		ourShader.setVec3("pointLights[3].ambient", 0.0f, 0.0f, 0.0f);
//		ourShader.setVec3("pointLights[3].diffuse", 1.0f, 1.0f, 1.0f);
//		ourShader.setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
//		ourShader.setFloat("pointLights[3].constant", 1.0f);
//		ourShader.setFloat("pointLights[3].linear", 0.09);
//		ourShader.setFloat("pointLights[3].quadratic", 0.032);
//		// 聚光灯
//		ourShader.setVec3("spotLight.position", camera.Position);
//		ourShader.setVec3("spotLight.direction", camera.Front);
//		ourShader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
//		ourShader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
//		ourShader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
//		ourShader.setFloat("spotLight.constant", 1.0f);
//		ourShader.setFloat("spotLight.linear", 0.09);
//		ourShader.setFloat("spotLight.quadratic", 0.032);
//		ourShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
//		ourShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
//
//		ourShader.setVec3("viewPos", camera.Position);
//		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 1.0f, 100.0f);
//		glm::mat4 view = camera.GetViewMatrix();
//		ourShader.setMat4("projection", projection);
//		ourShader.setMat4("view", view);
//
//
//		glm::mat4 model = glm::mat4(1.0f);
//		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 1.2f));
//		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.08f));
//		ourShader.setMat4("model", model);
//
//		ourShader.setFloat("time", glfwGetTime());
//		ourModel.Draw(ourShader);
//
//		shader.use();
//		shader.setMat4("projection", projection);
//		shader.setMat4("view", view);
//		shader.setMat4("model", model);
//
//		ourModel.Draw(shader);
//
//		}
//
//
//		//  glBindVertexArray(lightCubeVAO);
//	   //   glDrawArrays(GL_TRIANGLES, 0, 36);
//
//		glfwSwapBuffers(WindowPtr);
//		glfwPollEvents();
//	}
//
//
//
//	// 循环结束后释放资源glfwTerminate();
//	glfwTerminate();
//	return 0;
//}
