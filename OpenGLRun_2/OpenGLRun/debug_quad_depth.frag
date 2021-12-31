#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
//将深度贴图渲染到四边形上的片段着色器
uniform sampler2D depthMap;
uniform float near_plane;
uniform float far_plane;

//当使用透视投影矩阵时需要
float LinearizeDepth(float depth)
{
	float z = depth * 2.0 -1.0;//退回NDC
	return (2.0  * near_plane * far_plane) / (far_plane + near_plane - z * (far_plane - near_plane));

}
void main()
{
	float depthValue = texture(depthMap,TexCoords).r;
	//FragColor = vec4(vec3(LinearizeDepth(depthValue) / far_plane),1.0);//perspective
	FragColor = vec4(vec3(depthValue),1.0);//orthographic
}