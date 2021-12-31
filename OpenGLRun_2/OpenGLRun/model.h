#ifndef MODEL_H
#define MODEL_H

#include <glad/glad.h> // holds all OpenGL type declarations

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
//#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "mesh.h"
#include "shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
//#include "shader_m.h"
using namespace std;

unsigned int TextureFromFile(const char* path, const string& directory, bool gamma = false);
class Model
{
public:
	//ģ������
	vector<Texture> textures_loaded;//�����м��ع�������������һ��vector�У���ģ����Ķ�������Ϊһ��˽�б�����
	vector<Mesh> meshes;
	string directory;
	bool gammaCorrection;

	//����
	Model(string const& path, bool gamma = false) :gammaCorrection(gamma)
	{
		loadModel(path);
	}

	//����ģ�ͣ���������������
	void Draw(Shader& shader)
	{
		for (unsigned int i = 0; i < meshes.size(); i++)
			meshes[i].Draw(shader);//����һϵ�еĶ�����������ݣ����ǿ�������ͨ��glDrawElements��������������

	}

private:
	//����Assimp֧�ֵ�ģ��
	void loadModel(string const& path)//��loadModel�У�����ʹ��Assimp������ģ����Assimp���ݽӿڵĸ�����scene��Ȼ����ܷ��ʵ����غ��ģ�������������������
	{
		//��Assimp��ȡ�ļ�
		Assimp::Importer importer;//��������Assimp�����ռ��ڵ�һ��Importer��֮�����������ReadFile���������������Ҫһ���ļ�·��
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
		//const aiScene* scene = importer.ReadFile(�ļ�·��, ��ģ�����е�ͼԪ��״�任Ϊ������ | Ϊÿ�����㴴������ | ��תy����������� | �Զ���������);

				//�����󣺼�����ģ�ͺ��鳡��������ڵ㲻Ϊnull�����Ҽ��������һ�����(Flag)�����鿴���ص������ǲ��ǲ������ġ�
		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)//�����Ϊ��
		{
			cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;//ͨ����������GetErrorString������������󲢷���
			return;
		}
		//����filepathĿ¼·��
		directory = path.substr(0, path.find_last_of('/'));//��ȡ���ļ�·����Ŀ¼·����

		//�ݹ�ش���ASSIMP�ĸ��ڵ�
		processNode(scene->mRootNode, scene);//���ʲô����û�з���������ϣ���������е����нڵ�
	}
	//
	void processNode(aiNode* node, const aiScene* scene)//ÿ���ڵ㣨���ܣ��ж���ӽڵ㣬���ȴ�������еĽڵ㣬�ٴ���ýڵ����е��ӽڵ㣬�Դ����ơ���������һ���ݹ�ṹ���������ǽ�����һ���ݹ麯����
	{
		for (unsigned int i = 0; i < node->mNumMeshes; i++)  // ����ڵ����е���������еĻ���
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];//���ȼ��ÿ���ڵ������������������������mMeshes��������ȡ��Ӧ������
			meshes.push_back(processMesh(mesh, scene));//���ص����񽫻ᴫ�ݵ�processMesh�����У����᷵��һ��Mesh�������ǿ��Խ����洢��meshes�б�/vector��
		}
		for (unsigned int i = 0; i < node->mNumChildren; i++)//�������������ӽڵ��ظ���һ����
		{
			processNode(node->mChildren[i], scene);//�������񶼱�����֮�����ǻ�����ڵ�������ӽڵ㣬�����ǵ�����ͬ��processMesh��������һ���ڵ㲻�����κ��ӽڵ�֮�������������ִֹͣ�С�
		}

	}
	//��ȡ�������ݣ�����һ��Vertex�ṹ�壬ÿ�����������ӵ�vertices�����С����ǻ���������е����ж��㣨ʹ��mesh->mNumVertices����ȡ������ÿ�������������е���������������ṹ�塣
	Mesh processMesh(aiMesh* mesh, const aiScene* scene)//��Assimp�����ݽ������Ͻڴ�����Mesh����
	{
		//�������
		vector<Vertex> vertices;
		vector<unsigned int> indices;
		vector<Texture> textures;

		//����ÿ������Ķ���
		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex vertex;
			glm::vec3 vector;//Ϊ�˴���Assimp�����ݶ���һ��vec3����ʱ������ԭ����Assimp�������������ַ����ȶ����Լ���һ���������ͣ���������������ת����GLM�����������С�
			//����λ�ô���
			vector.x = mesh->mVertices[i].x;
			vector.y = mesh->mVertices[i].y;
			vector.z = mesh->mVertices[i].z;
			vertex.Position = vector;
			//�����ߵĲ���
			if (mesh->HasNormals())
			{
				vector.x = mesh->mNormals[i].x;
				vector.y = mesh->mNormals[i].y;
				vector.z = mesh->mNormals[i].z;
				vertex.Normal = vector;
			}
			//��������
			if (mesh->mTextureCoords[0])//mesh�Ƿ�����������ꣿ
			{
				glm::vec2 vec;
				//Assimp����һ��ģ����һ�������������8����ͬ����������
				vec.x = mesh->mTextureCoords[0][i].x;
				vec.y = mesh->mTextureCoords[0][i].y;
				vertex.TexCoords = vec;
				//����Tangent
				vector.x = mesh->mTangents[i].x;
				vector.y = mesh->mTangents[i].y;
				vector.z = mesh->mTangents[i].z;
				vertex.Tangent = vector;
				//bitangent
				vector.x = mesh->mBitangents[i].x;
				vector.y = mesh->mBitangents[i].y;
				vector.z = mesh->mBitangents[i].z;
				vertex.Bitangent = vector;
			}
			else
				vertex.TexCoords = glm::vec2(0.0f, 0.0f);
			vertices.push_back(vertex);
		}
		//Assimp�Ľӿڶ�����ÿ��������һ����(Face)���飬ÿ�������һ��ͼԪ��������aiPro_Tri���������Ρ�
		//һ������������������������ÿ��ͼԪ�У�����ʲô˳������ĸ����㣬�������е��沢�������������indices���vector�оͿ����ˡ�
		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];

			for (unsigned int j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}
		//һ������ֻ������һ��ָ����ʶ���������������Ҫ��ȡ���������Ĳ��ʣ����ǻ���Ҫ����������mMaterials���顣�����������λ������mMaterialIndex������
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];//���ȴӳ�����mMaterials�����л�ȡaiMaterial���󡣽��������������������������ͼ��
		//��������ͼ
		//һ�����ʶ�����ڲ���ÿ���������Ͷ��洢��һ������λ�����顣��ͬ���������Ͷ���aiTextureType_Ϊǰ׺��
		//ʹ��loadMaterialTextures�����Ӳ����л�ȡ��������������᷵��һ��Texture�ṹ���vector�����ǽ���ģ�͵�textures vector��β��֮��洢����
		vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		//�߹���ͼ
		vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		//������ͼ
		std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_NORMALS, "texture_normal");
		textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
		//�߶�ͼ
		std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_height");
		textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

		std::vector<Texture> ambientMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_reflect");
		textures.insert(textures.end(), ambientMaps.begin(), ambientMaps.end());
		return Mesh(vertices, indices, textures);//����һϵ�еĶ�����������ݣ����ǿ�������ͨ��glDrawElements��mesh.h��draw�����У���������������		

	}
	//loadMaterialTextures���������˸����������͵���������λ�ã���ȡ��������ļ�λ�ã������ز�����������������Ϣ��������һ��Vertex�ṹ���С�
	vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName)
	{
		vector<Texture> textures;
		for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)//����ͨ��GetTextureCount������鴢���ڲ��������������
		{
			aiString str;
			mat->GetTexture(type, i, &str);//ʹ��GetTexture��ȡÿ��������ļ�λ�ã����Ὣ���������һ��aiString��

			bool skip = false;
			for (unsigned int j = 0; j < textures_loaded.size(); j++)
			{
				if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
				{
					textures.push_back(textures_loaded[j]);
					skip = true;
					break;

				}
			}
			//�������·���봢����textures_loaded���vector�е���������Ƚϣ�����ǰ����·���Ƿ�������һ����ͬ���ǵĻ�ֱ��ʹ����������
			if (!skip) { // �������û�б����أ��������
				Texture texture;
				texture.id = TextureFromFile(str.C_Str(), this->directory);//ʹ��TextureFromFile���������ᣨ��stb_image.h������һ���������ظ������ID��
				texture.type = typeName;
				texture.path = str.C_Str();
				textures.push_back(texture);
				textures_loaded.push_back(texture);
			}
		}
		return textures;
	}
};
unsigned int TextureFromFile(const char* path, const string& directory, bool gamma)
{
	string filename = string(path);
	filename = directory + '/' + filename;

	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path:" << path << std::endl;
		stbi_image_free(data);
	}
	return textureID;
}
#endif

