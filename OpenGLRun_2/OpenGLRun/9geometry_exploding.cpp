//
//#include<filesystem>
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include "stb_image.h"//Texture�����ͷ�ļ�
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
//float deltaTime = 0.0f; // ��ǰ֡����һ֡��ʱ���
//float lastFrame = 0.0f; // ��һ֡��ʱ��
//glm::vec3 lightPos(1.2f, 1.0f, 2.0f);//��Դλ�ã�������������
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
//// �����ӿڴ�Сframebuffer_size_callback{glViewport()}
//void Global_Framebuffer_Size_Callback(GLFWwindow* WindowPtr, int Width, int Height)
//{
//	glViewport(0, 0, Width, Height);
//}
////�������processInput{glfwGetKey();glfwSetWindowShouldClose()}
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
//unsigned int loadTexture(char const* path)//����������ͼ����
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
//{//��ʼ��glfw���������ã�glfwInit(); glfwWindowHint
//	// ��ʼ��GLFW
//	glfwInit();
//	// �趨 opengl�汾Ϊ 3.3
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	// ʹ�ú���ģʽ
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//	// 2.�������ڣ�glfwCreateWindow()�� glfwSetFramebufferSizeCallback();
//	GLFWwindow* WindowPtr = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
//	if (WindowPtr == NULL)
//	{
//		std::cout << "Failed to create GLFW window" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//	glfwMakeContextCurrent(WindowPtr);
//	glfwSetFramebufferSizeCallback(WindowPtr, Global_Framebuffer_Size_Callback);
//	glfwSetCursorPosCallback(WindowPtr, mouse_callback);//���һ�ƶ�mouse_callback�����ͻᱻ���ã�
//	glfwSetScrollCallback(WindowPtr, scroll_callback);//ע�������ֵĻص�������
//	glfwSetInputMode(WindowPtr, GLFW_CURSOR, GLFW_CURSOR_DISABLED);//���ع�꣬����׽(Capture)��
//	//��ʼ��glad:gladLoadGLLoader()glfwGetProcAddress)
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//	{
//		std::cout << "Failed to initialize GLAD" << std::endl;
//		return -1;
//	}
//	//��ģ�ͼ���ǰ����stb_image.h ��������ʱ��תY�� 
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
//	// ����OpenGL��Ⱦ���ڵĳߴ��С ǰ�����������ƴ������½ǵ�λ�á��������͵��ĸ�����������Ⱦ���ڵĿ�Ⱥ͸߶ȣ����أ���
//	glViewport(0, 0, 1024, 768);
//	// ����ÿ�����ڵ�����С��ʱ������������ ��������opengl��Ⱦ���ڳߴ��С
//	glfwSetFramebufferSizeCallback(WindowPtr, Global_Framebuffer_Size_Callback);
//
//
//	//��Ⱦѭ��glfwWindowShouldClose
//	while (!glfwWindowShouldClose(WindowPtr))
//	{
//		float currentFrame = glfwGetTime();
//		deltaTime = currentFrame - lastFrame;
//		lastFrame = currentFrame;
//		// ��������¼�
//		Global_ProcessInput(WindowPtr);
//
//		// ���ÿһ֡��Ļ
//		glClearColor(0.75f, 0.52f, 0.3f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//�����ɫ����Ȼ���
//
//		//lightPos.x = 1.0f + sin(glfwGetTime()) * 2.0f;//��һ�⣺ʹ��sin��cos�����ù�Դ�ڳ����������ƶ����۲������ʱ��ĸı�
//	   // lightPos.y = sin(glfwGetTime() / 2.0f) * 1.0f;
//
//		//��
//		{
//
//		ourShader.use();
//		// �����
//		ourShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
//		ourShader.setVec3("dirLight.ambient", 0.3f, 0.24f, 0.14f);
//		ourShader.setVec3("dirLight.diffuse", 0.7f, 0.42f, 0.26f);
//		ourShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
//		// ���Դ1
//		ourShader.setVec3("pointLights[0].position", pointLightPositions[0]);
//		ourShader.setVec3("pointLights[0].ambient", 0.0f, 0.0f, 0.0f);
//		ourShader.setVec3("pointLights[0].diffuse", 1.0f, 1.0f, 1.0f);
//		ourShader.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
//		ourShader.setFloat("pointLights[0].constant", 1.0f);
//		ourShader.setFloat("pointLights[0].linear", 0.09);
//		ourShader.setFloat("pointLights[0].quadratic", 0.032);
//		// ���Դ2
//		ourShader.setVec3("pointLights[1].position", pointLightPositions[1]);
//		ourShader.setVec3("pointLights[1].ambient", 0.0f, 0.0f, 0.0f);
//		ourShader.setVec3("pointLights[1].diffuse", 1.0f, 1.0f, 1.0f);
//		ourShader.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
//		ourShader.setFloat("pointLights[1].constant", 1.0f);
//		ourShader.setFloat("pointLights[1].linear", 0.09);
//		ourShader.setFloat("pointLights[1].quadratic", 0.032);
//		// ���Դ3
//		ourShader.setVec3("pointLights[2].position", pointLightPositions[2]);
//		ourShader.setVec3("pointLights[2].ambient", 0.0f, 0.0f, 0.0f);
//		ourShader.setVec3("pointLights[2].diffuse", 1.0f, 1.0f, 1.0f);
//		ourShader.setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
//		ourShader.setFloat("pointLights[2].constant", 1.0f);
//		ourShader.setFloat("pointLights[2].linear", 0.09);
//		ourShader.setFloat("pointLights[2].quadratic", 0.032);
//		// ���Դ4
//		ourShader.setVec3("pointLights[3].position", pointLightPositions[3]);
//		ourShader.setVec3("pointLights[3].ambient", 0.0f, 0.0f, 0.0f);
//		ourShader.setVec3("pointLights[3].diffuse", 1.0f, 1.0f, 1.0f);
//		ourShader.setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
//		ourShader.setFloat("pointLights[3].constant", 1.0f);
//		ourShader.setFloat("pointLights[3].linear", 0.09);
//		ourShader.setFloat("pointLights[3].quadratic", 0.032);
//		// �۹��
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
//	// ѭ���������ͷ���ԴglfwTerminate();
//	glfwTerminate();
//	return 0;
//}
