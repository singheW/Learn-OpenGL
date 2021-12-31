#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in mat4 instanceMatrix;//Ϊ�������Ԥ��4���������ԡ���Ϊ���ǽ�����λ��ֵ����Ϊ3������ÿһ�еĶ�������λ��ֵ����3��4��5��6��
out vec2 TexCoords;

uniform mat4 projection;
uniform mat4 view;
//uniform mat4 model;//����ʹ��ģ��uniform��������Ϊһ��mat4�Ķ������ԣ��������ܹ��洢һ��ʵ��������ı任����

void main()
{
    TexCoords = aTexCoords;
    gl_Position = projection * view * instanceMatrix * vec4(aPos, 1.0f); 
}