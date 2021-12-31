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
	//模型数据
	vector<Texture> textures_loaded;//将所有加载过的纹理储存在另一个vector中，在模型类的顶部声明为一个私有变量：
	vector<Mesh> meshes;
	string directory;
	bool gammaCorrection;

	//函数
	Model(string const& path, bool gamma = false) :gammaCorrection(gamma)
	{
		loadModel(path);
	}

	//绘制模型，和他的所有网格
	void Draw(Shader& shader)
	{
		for (unsigned int i = 0; i < meshes.size(); i++)
			meshes[i].Draw(shader);//有了一系列的顶点和索引数据，它们可以用来通过glDrawElements函数来绘制网格。

	}

private:
	//加载Assimp支持的模型
	void loadModel(string const& path)//在loadModel中，我们使用Assimp来加载模型至Assimp数据接口的根对象scene。然后就能访问到加载后的模型中所有所需的数据了
	{
		//用Assimp读取文件
		Assimp::Importer importer;//首先声明Assimp命名空间内的一个Importer，之后调用了它的ReadFile函数。这个函数需要一个文件路径
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
		//const aiScene* scene = importer.ReadFile(文件路径, 将模型所有的图元形状变换为三角形 | 为每个顶点创建法线 | 翻转y轴的纹理坐标 | 自动生成切线);

				//检查错误：加载了模型后检查场景和其根节点不为null，并且检查了它的一个标记(Flag)，来查看返回的数据是不是不完整的。
		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)//如果不为零
		{
			cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;//通过导入器的GetErrorString函数来报告错误并返回
			return;
		}
		//检索filepath目录路径
		directory = path.substr(0, path.find_last_of('/'));//获取了文件路径的目录路径。

		//递归地处理ASSIMP的根节点
		processNode(scene->mRootNode, scene);//如果什么错误都没有发生，我们希望处理场景中的所有节点
	}
	//
	void processNode(aiNode* node, const aiScene* scene)//每个节点（可能）有多个子节点，首先处理参数中的节点，再处理该节点所有的子节点，以此类推。这正符合一个递归结构，所以我们将定义一个递归函数。
	{
		for (unsigned int i = 0; i < node->mNumMeshes; i++)  // 处理节点所有的网格（如果有的话）
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];//首先检查每个节点的网格索引，并索引场景的mMeshes数组来获取对应的网格。
			meshes.push_back(processMesh(mesh, scene));//返回的网格将会传递到processMesh函数中，它会返回一个Mesh对象，我们可以将它存储在meshes列表/vector。
		}
		for (unsigned int i = 0; i < node->mNumChildren; i++)//接下来对它的子节点重复这一过程
		{
			processNode(node->mChildren[i], scene);//所有网格都被处理之后，我们会遍历节点的所有子节点，对它们调用相同的processMesh函数。当一个节点不再有任何子节点之后，这个函数将会停止执行。
		}

	}
	//获取顶点数据，定义一个Vertex结构体，每个迭代后将它加到vertices数组中。我们会遍历网格中的所有顶点（使用mesh->mNumVertices来获取）。在每个迭代中用所有的相关数据填充这个结构体。
	Mesh processMesh(aiMesh* mesh, const aiScene* scene)//将Assimp的数据解析到上节创建的Mesh类中
	{
		//填充数据
		vector<Vertex> vertices;
		vector<unsigned int> indices;
		vector<Texture> textures;

		//遍历每个网格的顶点
		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex vertex;
			glm::vec3 vector;//为了传输Assimp的数据定义一个vec3的临时变量。原因是Assimp对向量、矩阵、字符串等都有自己的一套数据类型，它并不能完美地转换到GLM的数据类型中。
			//顶点位置处理
			vector.x = mesh->mVertices[i].x;
			vector.y = mesh->mVertices[i].y;
			vector.z = mesh->mVertices[i].z;
			vertex.Position = vector;
			//处理法线的步骤
			if (mesh->HasNormals())
			{
				vector.x = mesh->mNormals[i].x;
				vector.y = mesh->mNormals[i].y;
				vector.z = mesh->mNormals[i].z;
				vertex.Normal = vector;
			}
			//纹理坐标
			if (mesh->mTextureCoords[0])//mesh是否包含纹理坐标？
			{
				glm::vec2 vec;
				//Assimp允许一个模型在一个顶点上有最多8个不同的纹理坐标
				vec.x = mesh->mTextureCoords[0][i].x;
				vec.y = mesh->mTextureCoords[0][i].y;
				vertex.TexCoords = vec;
				//切线Tangent
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
		//Assimp的接口定义了每个网格都有一个面(Face)数组，每个面代表一个图元，（由于aiPro_Tri）是三角形。
		//一个面包含多个索引，它定义在每个图元中，该以什么顺序绘制哪个顶点，遍历所有的面并储存面的索引到indices这个vector中就可以了。
		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];

			for (unsigned int j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}
		//一个网格只包含了一个指向材质对象的索引。如果想要获取网格真正的材质，我们还需要索引场景的mMaterials数组。网格材质索引位于它的mMaterialIndex属性中
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];//首先从场景的mMaterials数组中获取aiMaterial对象。接下来加载网格的漫反射或镜面光贴图。
		//漫反射贴图
		//一个材质对象的内部对每种纹理类型都存储了一个纹理位置数组。不同的纹理类型都以aiTextureType_为前缀。
		//使用loadMaterialTextures函数从材质中获取纹理。这个函数将会返回一个Texture结构体的vector，我们将在模型的textures vector的尾部之后存储它。
		vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		//高光贴图
		vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		//法线贴图
		std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_NORMALS, "texture_normal");
		textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
		//高度图
		std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_height");
		textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

		std::vector<Texture> ambientMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_reflect");
		textures.insert(textures.end(), ambientMaps.begin(), ambientMaps.end());
		return Mesh(vertices, indices, textures);//有了一系列的顶点和索引数据，它们可以用来通过glDrawElements（mesh.h的draw函数中）函数来绘制网格。		

	}
	//loadMaterialTextures函数遍历了给定纹理类型的所有纹理位置，获取了纹理的文件位置，并加载并和生成了纹理，将信息储存在了一个Vertex结构体中。
	vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName)
	{
		vector<Texture> textures;
		for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)//首先通过GetTextureCount函数检查储存在材质中纹理的数量
		{
			aiString str;
			mat->GetTexture(type, i, &str);//使用GetTexture获取每个纹理的文件位置，它会将结果储存在一个aiString中

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
			//将纹理的路径与储存在textures_loaded这个vector中的所有纹理比较，看当前纹理路径是否与其中一个相同。是的话直接使用其中纹理。
			if (!skip) { // 如果纹理还没有被加载，则加载它
				Texture texture;
				texture.id = TextureFromFile(str.C_Str(), this->directory);//使用TextureFromFile函数，它会（用stb_image.h）加载一个纹理并返回该纹理的ID。
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

