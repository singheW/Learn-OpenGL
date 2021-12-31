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

struct Vertex {//ÿ���������һ��λ��������һ����������һ����������������һ������Ӧ�ð��������������Ƶ�����
	//λ��
	glm::vec3 Position;
	//����
	glm::vec3 Normal;
	//��������
	glm::vec2 TexCoords;
	//����
	glm::vec3 Tangent;
	//bitangent
	glm::vec3 Bitangent;
	//����Ӱ��������������
	int m_BoneIDs[MAX_BONE_INFLUENCE];
	//ÿ��������Ȩ��
	float m_Weights[MAX_BONE_INFLUENCE];

};

struct Texture {//һ������Ӧ�ð���������ʽ�Ĳ�������
	unsigned int id;//���������id
	string type;//�����������ͣ���������������ͼ�����Ǿ������ͼ��
	string path; // ���Ǵ��������·������������������бȽ�.���ڸ��������ʡ����
};

class Mesh {
public:
	//��������
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;
	unsigned int VAO;

	//����:�����б�������ݸ��������
	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures)
	{
		this->vertices = vertices;
		this->indices = indices;
		this->textures = textures;

		//���������������ݣ����ö��㻺������Ķ�������
		setupMesh();//��setupMesh�����г�ʼ������
	}
	void Draw(Shader& shader) {//����ʹ��Draw��������������
		//����������
		unsigned int diffuseNr = 1;
		unsigned int specularNr = 1;
		unsigned int normalNr = 1;
		unsigned int heightNr = 1;
		for (unsigned int i = 0; i < textures.size(); i++)//������������
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
			//glUniform1i(Ҫ���ĵ�uniform������λ��, Ҫ���ĵ�Ԫ�ظ���N��ָ��һ������N����ֵ������ָ��);
			// glGetUniformLocation������Uniform���ƻ�ȡUniform��λ��
			glBindTexture(GL_TEXTURE_2D, textures[i].id);
		}
		glBindVertexArray(VAO);//���glBindBuffer��ҪglBindVertexArray VAOָ��
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);//��һ��������������ȡ������Ⱦ����ͼԪ
		//glDrawElements�����Ƶ�ģʽ��������ƶ���ĸ��������������ͣ�ָ�����������ָ�룩
		//ʹ�� glDrawArrays�ķ�ʽ������һ���԰����ж��㴫����Ⱦ���ߣ����ҿ���ѡ����ƵĿ�ʼ�ͽ�β�㣬������ֻҪһ���������ͺ��ˣ������������Ҫ��ռ���ڴ�ռ��ˡ�
		glBindVertexArray(0);//���VAO��ע���VAOʱҲ���Զ���EBO

		glActiveTexture(GL_TEXTURE0);// ����glActiveTexture��������Ԫ����ʼ��ΪGL_TEXTURE0����Ȼ�󽫣�һ��������������Ŀ�ꡱ�󶨵�������Ԫ
	}
private:
	//��Ⱦ����
	unsigned int VBO, EBO;

	//��������setupMesh�����г�ʼ������
	void setupMesh()
	{
		//һ��VAO�ж��VBO��VAO��һ�����󣬰���һ��������VBO��VBO���ڴ滺�������������涥�㣬��ɫ�����ߣ���������������ȡ�
		//glGenBuffers ����N����ǰδʹ�õĻ���������ƣ������浽buffer�����У����ﷵ�ص�����ֻ�����������������������ڰ�֮��ֻ���¼һ�����õ�״̬��
		//glBindBuffer ���仺�������֮�󣬾Ϳ���ʹ��glBindBuffer������Ϊ��ͬ�Ļ������
		//glBufferData ��ʼ�����㻺�����֮��ͨ��glBufferData�Ѷ������ݴӶ����䵽��������С�������1.���䶥����������洢�ռ䡣2.�����ݴӳ�������鿽�����ڴ���
		//glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
		//glBufferData�������������ͣ��洢������������=�����д洢Ԫ������*��λԪ�ش洢�ռ䣩��ָ���Ա��ʼ������������ݶ�д��ʽ��
		//glEnableVertexAttribArray(1);  VAO�ɿ���һ�����飬1��������Կ�������������������Ӧlayout (location = 1) �����������ǽ���״̬��Ϊenabled����ʱ��ɫ����ȡֵ������Ч
		//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
		//glVertexAttribPointer(������1��ʼȡ�����붥����ɫ����layout(location=1)��Ӧ��
		//�������Դ�С3��position����3����x,y,z������ɫ��4����r,g,b,a������������float������׼������׼����ֻ��ʾ���򲻱�ʾ��С),
		// �����������������Լ�ļ�� sizeof(Vertex)��ƫ������λ���������ڴ滺������ʼλ�õ�ƫ�������¸����λ��)

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);//ʹ��glBufferData��ΪBuffer�����ڴ档

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);//GL_ELEMENT_ARRAY_BUFFER ������������
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
		//����λ��
		glEnableVertexAttribArray(0);//Ҫ���û��߽��ö����������飬�������index��
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);//�������ݸ�ʽ
		//���㷨��
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
		//������������
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
		//��������
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
		//����bitangent
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));
		//��������
		glEnableVertexAttribArray(5);
		glVertexAttribIPointer(5, 4, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, m_BoneIDs));
		//����Ȩ��
		glEnableVertexAttribArray(6);
		glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_Weights));

		glBindVertexArray(0);//���VAO

	}

};
#endif
