#version 330 core
out vec4 FragColor;
layout (depth_greater)out float gl_FragDepth;//对片段的深度值进行了递增，也保留了一些提前深度测试：
void main()
{

	FragColor = vec4(0.0,0.0,1.0,1.0);
	//gl_FragDepth = gl_FragCoord.z + 0.1;
}