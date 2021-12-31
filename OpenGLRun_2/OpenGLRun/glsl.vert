#version 330 core

layout (location = 0) in vec3 aPos;
//layout (std140）是说，当前定义的Uniform块对它的内容使用一个特定的内存布局。即Uniform块布局(Uniform Block Layout)。
layout (std140) uniform Matrices//Uniform块中的变量可以直接访问，不需要加块名作为前缀。
{
mat4 projection;
mat4 view;
};
//将投影和模型矩阵存储到一个叫做Matrices的Uniform块中。我们不会将模型矩阵存在这里，因为模型矩阵在不同的着色器中会不断改变，所以使用Uniform缓冲对象并不会带来什么好处。


out VS_OUT//接口块
{
	vec2 TexCoords;
}vs_out;


uniform mat4 model;
void main()
{
	gl_Position = projection * view * model * vec4(aPos,1.0);
	gl_PointSize = gl_Position.z*1000;//使用它来设置点的宽高（像素）。将点的大小设置为顶点距观察者的距离。点的大小会随着观察者距顶点距离变远而增大。
}