#version 330 core
out vec4 FragColor;
layout (depth_greater)out float gl_FragDepth;//��Ƭ�ε����ֵ�����˵�����Ҳ������һЩ��ǰ��Ȳ��ԣ�
void main()
{

	FragColor = vec4(0.0,0.0,1.0,1.0);
	//gl_FragDepth = gl_FragCoord.z + 0.1;
}