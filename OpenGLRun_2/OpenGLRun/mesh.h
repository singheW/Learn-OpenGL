#ifndef MESH_H
#define MESH_H

#include <glad/glad.h> // holds all OpenGL type declarations

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <vector>
#include "shader_m.h"
using namespace std;

#define MAX_BONE_INFLUENCE 4

const unsigned int WIDTH = 1024;
const unsigned int HEIGHT = 768;

struct Vertex {//每个顶点包含一个位置向量、一个法向量和一个纹理坐标向量。一个网格还应该包含用于索引绘制的索引
	//位置
	glm::vec3 Position;
	//法线
	glm::vec3 Normal;
	//纹理坐标
	glm::vec2 TexCoords;
	//切线
	glm::vec3 Tangent;
	//bitangent
	glm::vec3 Bitangent;
	//可以影响骨骼顶点的索引
	int m_BoneIDs[MAX_BONE_INFLUENCE];
	//每根骨骼的权重
	float m_Weights[MAX_BONE_INFLUENCE];

};

struct Texture {//一个网格还应该包含纹理形式的材质数据
	unsigned int id;//储存纹理的id
	string type;//储存它的类型，比如是漫反射贴图或者是镜面光贴图。
	string path; // 我们储存纹理的路径用于与其它纹理进行比较.便于复用纹理节省性能
};

class Mesh {
public:
	//网格数据
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;
	unsigned int VAO;

	//函数:将所有必须的数据赋予给网格
	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures)
	{
		this->vertices = vertices;
		this->indices = indices;
		this->textures = textures;

		//有了所有所需数据，设置顶点缓冲和他的顶点属性
		setupMesh();//在setupMesh函数中初始化缓冲
	}
	void Draw(Shader& shader) {//最终使用Draw函数来绘制网格
		//绑定纹理属性
		unsigned int diffuseNr = 1;
		unsigned int specularNr = 1;
		unsigned int normalNr = 1;
		unsigned int heightNr = 1;
		for (unsigned int i = 0; i < textures.size(); i++)//激活绑定相关纹理
		{
			glActiveTexture(GL_TEXTURE0 + i);
			string number;
			string name = textures[i].type;
			if (name == "texture_diffuse")
				number = std::to_string(diffuseNr++);
			else if (name == "texture_specular")
				number = std::to_string(specularNr++);
			else if (name == "texture_normal")
				number = std::to_string(normalNr++);
			else if (name == "texture_height")
				number = std::to_string(heightNr++);

			glUniform1i(glGetUniformLocation(shader.ID, (name + number).c_str()), i);
			//glUniform1i(要更改的uniform变量的位置, 要更改的元素个数N，指定一个具有N个数值的数组指针);
			// glGetUniformLocation将根据Uniform名称获取Uniform的位置
			glBindTexture(GL_TEXTURE_2D, textures[i].id);
		}
		glBindVertexArray(VAO);//多个glBindBuffer需要glBindVertexArray VAO指定
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);//从一个数据数组中提取数据渲染基本图元
		//glDrawElements（绘制的模式，打算绘制顶点的个数，索引的类型，指向索引数组的指针）
		//使用 glDrawArrays的方式，可以一次性把所有顶点传到渲染管线，并且可以选择绘制的开始和结尾点，这样就只要一个缓冲区就好了，不过代码就是要多占用内存空间了。
		glBindVertexArray(0);//解绑VAO，注意绑定VAO时也会自动绑定EBO

		glActiveTexture(GL_TEXTURE0);// 调用glActiveTexture设置纹理单元（初始化为GL_TEXTURE0），然后将（一个或多个）“纹理目标”绑定到该纹理单元
	}
private:
	//渲染数据
	unsigned int VBO, EBO;

	//函数：在setupMesh函数中初始化缓冲
	void setupMesh()
	{
		//一个VAO有多个VBO，VAO是一个对象，包含一个或更多的VBO。VBO是内存缓冲区，用来保存顶点，颜色，法线，纹理坐标和索引等。
		//glGenBuffers 返回N个当前未使用的缓存对象名称，并保存到buffer数组中，这里返回的名称只用与分配其他缓存对象，他们在绑定之后只会记录一个可用的状态。
		//glBindBuffer 分配缓存的名称之后，就可以使用glBindBuffer绑定他们为不同的缓存对象。
		//glBufferData 初始化顶点缓冲对象之后，通过glBufferData把顶点数据从对象传输到缓存对象当中。两步：1.分配顶点数据所需存储空间。2.将数据从程序的数组拷贝到内存中
		//glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
		//glBufferData（顶点数据类型，存储数据总数量（=数据中存储元素总数*单位元素存储空间），指针以便初始化缓存对象，数据读写方式）
		//glEnableVertexAttribArray(1);  VAO可看成一个数组，1这个数可以看成这个数组的索引，对应layout (location = 1) 。它的作用是将该状态置为enabled，此时着色器读取值才能生效
		//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
		//glVertexAttribPointer(从索引1开始取数据与顶点着色器中layout(location=1)对应，
		//顶点属性大小3如position是由3个（x,y,z），颜色是4个（r,g,b,a），数据类型float，不标准化（标准化是只表示方向不表示大小),
		// 步长：连续顶点属性间的间隔 sizeof(Vertex)，偏移量：位置数据在内存缓冲区起始位置的偏移量，下个组的位置)

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);//使用glBufferData来为Buffer分配内存。

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);//GL_ELEMENT_ARRAY_BUFFER 索引数据类型
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
		//顶点位置
		glEnableVertexAttribArray(0);//要启用或者禁用顶点属性数组，传入参数index。
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);//设置数据格式
		//顶点法线
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
		//顶点纹理坐标
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
		//顶点切线
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
		//顶点bitangent
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));
		//骨骼索引
		glEnableVertexAttribArray(5);
		glVertexAttribIPointer(5, 4, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, m_BoneIDs));
		//骨骼权重
		glEnableVertexAttribArray(6);
		glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_Weights));

		glBindVertexArray(0);//解绑VAO

	}

};
#endif
