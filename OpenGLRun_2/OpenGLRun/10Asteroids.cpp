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
//		camera.ProcessKeyboard(FORWARD, deltaTime * 10);
//	if (glfwGetKey(WindowPtr, GLFW_KEY_S) == GLFW_PRESS)
//		camera.ProcessKeyboard(BACKWARD, deltaTime*10);
//	if (glfwGetKey(WindowPtr, GLFW_KEY_A) == GLFW_PRESS)
//		camera.ProcessKeyboard(LEFT, deltaTime * 10);
//	if (glfwGetKey(WindowPtr, GLFW_KEY_D) == GLFW_PRESS)
//		camera.ProcessKeyboard(RIGHT, deltaTime * 10);
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
//
//
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
//	//Shader shader("asteroids.vert", "asteroids.frag");
//	//Shader planetShader("planet.vert", "planet.frag");
//	Shader shader("asteroids.vert", "asteroids.frag");
//	Shader planetShader("planet.vert", "planet.frag");
//
//	Model rock("rock/rock.obj");
//	Model planet("planet/planet.obj");
//	
//	//生成一长列半随机模型变换矩阵
//	unsigned int amount = 100000;
//	glm::mat4* modelMatrices;
//	modelMatrices = new glm::mat4[amount];
//	srand(glfwGetTime());//初始化随机种子
//	float radius = 150.0;
//	float offset = 25.0f;
//	for (unsigned int i = 0; i < amount; i++)
//	{
//		glm::mat4 model = glm::mat4(1.0f);
//		//1.位移：分布在半径为radius的圆形上，偏移的范围是[-offset,offset]
//		float angle = (float)i / (float)amount * 360.0f;
//		float displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
//		float x = sin(angle) * radius + displacement;
//		displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
//		float y = displacement * 0.4f;
//		displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
//		float z = cos(angle) * radius + displacement;
//		model = glm::translate(model, glm::vec3(x, y, z));
//		//2.缩放：在0.05和0.25f之间缩放
//		float scale = (rand() % 20) / 100.0f + 0.05;
//		model = glm::scale(model, glm::vec3(scale));
//		//3.旋转：绕着一个（半）随机选择的旋转轴向量进行随机的旋转
//		float rotAngle = (rand() % 360);
//		model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));
//		//4.添加到矩阵的数组中
//		modelMatrices[i] = model;
//	}
//
//	//配置实例数组 // 顶点缓冲对象
//	unsigned int buffer;
//	glGenBuffers(1, &buffer);
//	glBindBuffer(GL_ARRAY_BUFFER, buffer);
//	glBufferData(GL_ARRAY_BUFFER, amount * sizeof(glm::mat4), &modelMatrices[0], GL_STATIC_DRAW);
//
//	for (unsigned int i = 0; i < rock.meshes.size(); i++)
//	{
//		unsigned int VAO = rock.meshes[i].VAO; //将Mesh的VAO从私有变量改为了公有变量，让我们能够访问它的顶点数组对象。
//		glBindVertexArray(VAO);
//		// 顶点属性
//		GLsizei vec4Size = sizeof(glm::vec4);
//		glEnableVertexAttribArray(3);
//		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)0);
//		glEnableVertexAttribArray(4);
//		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(vec4Size));
//		glEnableVertexAttribArray(5);
//		glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(2 * vec4Size));
//		glEnableVertexAttribArray(6);
//		glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(3 * vec4Size));
//
//		glVertexAttribDivisor(3, 1);
//		glVertexAttribDivisor(4, 1);
//		glVertexAttribDivisor(5, 1);
//		glVertexAttribDivisor(6, 1);
//
//		glBindVertexArray(0);
//	}
//
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
//		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//		//配置变换矩阵
//		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 1000.0f);
//		glm::mat4 view = camera.GetViewMatrix();;
//		shader.use();
//		shader.setMat4("projection", projection);
//		shader.setMat4("view", view);
//
//		planetShader.use();
//		planetShader.setMat4("projection", projection);
//		planetShader.setMat4("view", view);
//		// 绘制行星
//		glm::mat4 model = glm::mat4(1.0f);
//		model = glm::translate(model, glm::vec3(0.0f, -3.0f, 0.0f));
//		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
//		planetShader.setMat4("model", model);
//		planet.Draw(planetShader);
//
//		//绘制 小行星
//		shader.use();
//		shader.setInt("texture_diffuse1", 0);
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, rock.textures_loaded[0].id);
//		for (unsigned int i = 0; i < rock.meshes.size(); i++)
//		{
//			//shader.setMat4("model", modelMatrices[i]);
//			//rock.Draw(shader);
//			glBindVertexArray(rock.meshes[i].VAO);
//			glDrawElementsInstanced(GL_TRIANGLES, rock.meshes[i].indices.size(), GL_UNSIGNED_INT, 0, amount);
//			glBindVertexArray(0);
//
//
//		}
//
//		//  glBindVertexArray(lightCubeVAO);
//	   //   glDrawArrays(GL_TRIANGLES, 0, 36);
//
//		glfwSwapBuffers(WindowPtr);
//		glfwPollEvents();
//	}
//
//	// 循环结束后释放资源glfwTerminate();
//	glfwTerminate();
//	return 0;
//}
