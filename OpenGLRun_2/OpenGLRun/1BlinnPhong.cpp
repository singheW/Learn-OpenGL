//
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include "stb_image.h"//Texture�����ͷ�ļ�
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
//bool blinn = false;
//bool blinnKeyPressed = false;
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
//
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
//
//	if (glfwGetKey(WindowPtr, GLFW_KEY_B) == GLFW_PRESS && !blinnKeyPressed)
//	{
//		blinn = !blinn;
//		blinnKeyPressed = true;
//
//	}
//	if (glfwGetKey(WindowPtr, GLFW_KEY_B) == GLFW_RELEASE)
//	{
//		blinnKeyPressed = false;
//	}
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
//
//	glEnable(GL_DEPTH_TEST);
//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//
//	Shader lightingShader("BlinnPhong.vert", "BlinnPhong.frag");
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
//	//����VBO�����㻺�棬VAO���涥�����ԣ�EBO������������
//	unsigned int VBO, cubeVAO;
//	glGenVertexArrays(1, &cubeVAO);//ʹ��glGenVertexArrays������һ������ID����һ��VAO����
//	glGenBuffers(1, &VBO);//ʹ��glGenBuffers������һ������ID����һ��VBO����
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);//ʹ��glBindBuffer�������´����Ļ���󶨵�GL_ARRAY_BUFFERĿ����
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//����glBufferData�����������֮ǰ����Ķ������ݸ��Ƶ�������ڴ���
//
//	glBindVertexArray(cubeVAO);;//ʹ��glBindVertexArray��VAO
//
//	//λ������
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);//����OpenGL����ν����������ݣ�Ӧ�õ�������������ϣ�
//	glEnableVertexAttribArray(0);//�Զ�������λ��ֵ��Ϊ���������ö������ԣ���������Ĭ���ǽ��õġ�
//	//��������
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//	glEnableVertexAttribArray(1);
//	//��������
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
//	//  unsigned int specularMap = loadTexture("lighting_maps_specular_color.png");//�ڶ��⣺ʹ�ò�ɫ�ľ������ͼ
//	unsigned int emissionMap = loadTexture("matrix.jpg");
//	lightingShader.use();
//	lightingShader.setInt("material.diffuse", 0);
//	lightingShader.setInt("material.specular", 1);
//	lightingShader.setInt("material.emission", 2);
//
//
//	// ����OpenGL��Ⱦ���ڵĳߴ��С ǰ�����������ƴ������½ǵ�λ�á��������͵��ĸ�����������Ⱦ���ڵĿ�Ⱥ͸߶ȣ����أ���
//	glViewport(0, 0, 1024, 768);
//	// ����ÿ�����ڵ�����С��ʱ������������ ��������opengl��Ⱦ���ڳߴ��С
//	glfwSetFramebufferSizeCallback(WindowPtr, Global_Framebuffer_Size_Callback);
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
//		lightingShader.use();////��glUseProgram��������֮��ÿ����ɫ�����ú���Ⱦ���ö���ʹ������������Ҳ����֮ǰд����ɫ��)��
//	  //  lightingShader.setVec3("light.position", lightPos);//������������Ҫ�õ���Դλ������Ʒλ�õĲ���Ϊ�����������÷�������������
//		//lightingShader.setVec3("light.direction", -0.2f, -1.0f, -0.3f);//��-0.2f, -1.0f, -0.3f)ƽ�й�
//		lightingShader.setVec3("viewPos", camera.Position);//����߹���Ҫ�۲췽�򣬼���Ӧ�������λ�����꣬����Ƭ����ɫ����
//		lightingShader.setFloat("material.shininess", 32.0f);
//		lightingShader.setFloat("matrixlight", (1.0 + sin(glfwGetTime())) / 2 + 0.5);
//		lightingShader.setFloat("matrixmove", glfwGetTime());
//
//		// �����
//		lightingShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
//		lightingShader.setVec3("dirLight.ambient", 0.3f, 0.24f, 0.14f);
//		lightingShader.setVec3("dirLight.diffuse", 0.7f, 0.42f, 0.26f);
//		lightingShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
//		// ���Դ1
//		lightingShader.setVec3("pointLights[0].position", pointLightPositions[0]);
//		lightingShader.setVec3("pointLights[0].ambient", pointLightColors[0].x*0.1, pointLightColors[0].y*0.1, pointLightColors[0].z*0.1);
//		lightingShader.setVec3("pointLights[0].diffuse", pointLightColors[0]);
//		lightingShader.setVec3("pointLights[0].specular", pointLightColors[0]);
//		lightingShader.setFloat("pointLights[0].constant", 1.0f);
//		lightingShader.setFloat("pointLights[0].linear", 0.09);
//		lightingShader.setFloat("pointLights[0].quadratic", 0.032);
//		// ���Դ2
//		lightingShader.setVec3("pointLights[1].position", pointLightPositions[1]);
//		lightingShader.setVec3("pointLights[0].ambient", pointLightColors[1].x * 0.1, pointLightColors[1].y * 0.1, pointLightColors[1].z * 0.1);
//		lightingShader.setVec3("pointLights[0].diffuse", pointLightColors[1]);
//		lightingShader.setVec3("pointLights[0].specular", pointLightColors[1]);
//		lightingShader.setFloat("pointLights[1].constant", 1.0f);
//		lightingShader.setFloat("pointLights[1].linear", 0.09);
//		lightingShader.setFloat("pointLights[1].quadratic", 0.032);
//		// ���Դ3
//		lightingShader.setVec3("pointLights[0].position", pointLightPositions[2]);
//		lightingShader.setVec3("pointLights[0].ambient", pointLightColors[2].x * 0.1, pointLightColors[2].y * 0.1, pointLightColors[2].z * 0.1);
//		lightingShader.setVec3("pointLights[0].diffuse", pointLightColors[2]);
//		lightingShader.setVec3("pointLights[0].specular", pointLightColors[2]);
//		lightingShader.setFloat("pointLights[2].constant", 1.0f);
//		lightingShader.setFloat("pointLights[2].linear", 0.09);
//		lightingShader.setFloat("pointLights[2].quadratic", 0.032);
//		// ���Դ4
//		lightingShader.setVec3("pointLights[0].position", pointLightPositions[3]);
//		lightingShader.setVec3("pointLights[0].ambient", pointLightColors[3].x * 0.1, pointLightColors[3].y * 0.1, pointLightColors[3].z * 0.1);
//		lightingShader.setVec3("pointLights[0].diffuse", pointLightColors[3]);
//		lightingShader.setVec3("pointLights[0].specular", pointLightColors[3]);
//		lightingShader.setFloat("pointLights[3].constant", 1.0f);
//		lightingShader.setFloat("pointLights[3].linear", 0.09);
//		lightingShader.setFloat("pointLights[3].quadratic", 0.032);
//		// �۹��
//		lightingShader.setVec3("spotLight.position", camera.Position);
//		lightingShader.setVec3("spotLight.direction", camera.Front);
//		lightingShader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
//		lightingShader.setVec3("spotLight.diffuse", 0.8f, 0.80f, 0.0f);
//		lightingShader.setVec3("spotLight.specular", 0.8f, 0.8f, 0.0f);
//		lightingShader.setFloat("spotLight.constant", 1.0f);
//		lightingShader.setFloat("spotLight.linear", 0.09);
//		lightingShader.setFloat("spotLight.quadratic", 0.032);
//		lightingShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
//		lightingShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
//
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
//		//��diffuse��ͼ
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, diffuseMap);
//		//��specular��ͼ
//		glActiveTexture(GL_TEXTURE1);
//		glBindTexture(GL_TEXTURE_2D, specularMap);
//		//��emission��ͼ
//		glActiveTexture(GL_TEXTURE2);
//		glBindTexture(GL_TEXTURE_2D, emissionMap);
//
//		glBindVertexArray(cubeVAO);
//		for (unsigned int i = 0; i < 10; i++)
//		{
//			glm::mat4 model = glm::mat4(1.0f);
//			model = glm::translate(model, cubePositions[i]);
//			float angle = glfwGetTime() * 10.0f * (i + 1);
//		//	model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
//			lightingShader.setMat4("model", model);
//			glDrawArrays(GL_TRIANGLES, 0, 36);
//		}
//
//		lightCubeShader.use();
//		lightCubeShader.setMat4("projection", projection);
//		lightCubeShader.setMat4("view", view);
//
//		glBindVertexArray(lightCubeVAO);
//		for (unsigned int i = 0; i < 4; i++)
//		{
//		model = glm::mat4(1.0f);
//		model = glm::translate(model, pointLightPositions[i]);
//		model = glm::scale(model, glm::vec3(0.2f));
//	//	float angle = glfwGetTime() * 25.0f;
//	//	model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
//		lightCubeShader.setMat4("model", model);
//		glDrawArrays(GL_TRIANGLES, 0, 36);
//		}
//		//  glBindVertexArray(lightCubeVAO);
//	   //   glDrawArrays(GL_TRIANGLES, 0, 36);
//		std::cout << (blinn ? "Blinn-Phong" : "Phong") << std::endl;
//
//		glfwSwapBuffers(WindowPtr);
//		glfwPollEvents();
//	}
//
//
//	glDeleteVertexArrays(1, &cubeVAO);
//	glDeleteVertexArrays(1, &lightCubeVAO);
//	glDeleteBuffers(1, &VBO);
//	// ѭ���������ͷ���ԴglfwTerminate();
//	glfwTerminate();
//	return 0;
//}
