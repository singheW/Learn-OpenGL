#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 FragPos;//顶点坐标
out vec3 Normal;//法向量，计算漫反射用

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));//把顶点属性乘以模型矩阵以变换到世界空间坐标
    Normal = mat3(transpose(inverse(model))) * aNormal;  //使用inverse和transpose函数生成法线矩阵，最后强制转换为3×3矩阵，保证失去位移属性及能乘以vec3的法向量。
    
    gl_Position = projection * view * vec4(FragPos, 1.0);
}