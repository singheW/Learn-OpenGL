#version 330 core

layout (location = 0) in vec3 aPos;
//layout (std140����˵����ǰ�����Uniform�����������ʹ��һ���ض����ڴ沼�֡���Uniform�鲼��(Uniform Block Layout)��
layout (std140) uniform Matrices//Uniform���еı�������ֱ�ӷ��ʣ�����Ҫ�ӿ�����Ϊǰ׺��
{
mat4 projection;
mat4 view;
};
//��ͶӰ��ģ�;���洢��һ������Matrices��Uniform���С����ǲ��Ὣģ�;�����������Ϊģ�;����ڲ�ͬ����ɫ���л᲻�ϸı䣬����ʹ��Uniform������󲢲������ʲô�ô���


out VS_OUT//�ӿڿ�
{
	vec2 TexCoords;
}vs_out;


uniform mat4 model;
void main()
{
	gl_Position = projection * view * model * vec4(aPos,1.0);
	gl_PointSize = gl_Position.z*1000;//ʹ���������õ�Ŀ�ߣ����أ�������Ĵ�С����Ϊ�����۲��ߵľ��롣��Ĵ�С�����Ź۲��߾ඥ������Զ������
}