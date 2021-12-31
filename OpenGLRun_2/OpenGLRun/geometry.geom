#version 330 core
layout (points) in;//�����Ӷ�����ɫ�������ͼԪ���͡�����Ҫ��in�ؼ���ǰ����һ���������η�: (points������GL_POINTSͼԪʱ��1����)
layout (triangle_strip,max_vertices = 5) out;//(Line Strip)������������һ��㣬�γ�һ���������ߣ�������Ҫ������������ɡ�
//ָ��������ɫ�������ͼԪ���ͣ�����Ҫ��out�ؼ���ǰ���һ���������η���������ɫ��ͬʱϣ����������һ��������ܹ�����Ķ����������������,OpenGL��������ƶ���Ķ��㣩

in VS_OUT//��ȡǰһ��ɫ���׶ε������������ɫ����������һ��ͼԪ�����ж��㡣
{
	vec3 color;

} gs_in[];

out vec3 fColor;

//ʹ�ü�����ɫ��������EmitVertex��EndPrimitive���������µ����� //������ɫ��ϣ�����ܹ����ɲ��������һ������Ϊ�����ͼԪ��
void build_house(vec4 position)
{
	fColor = gs_in[0].color;// gs_in[0] ��Ϊֻ��һ�����붥��
	gl_Position = position +vec4(-0.2,-0.2,0.0,0.0); // 1:����  
	EmitVertex();//ÿ�����ǵ���EmitVertexʱ��gl_Position�е������ᱻ��ӵ�ͼԪ����
		gl_Position = position +vec4(0.2,-0.2,0.0,0.0);// 2:����
	EmitVertex();//��һ������EmitVertex����֮���ظ�����EndPrimitive�ܹ����ɶ��ͼԪ��
		gl_Position = position +vec4(-0.2,0.2,0.0,0.0);//3:����
	EmitVertex();
		gl_Position = position +vec4(0.2,0.2,0.0,0.0);// 4:����
	EmitVertex();
		gl_Position = position +vec4(0.0,0.4,0.0,0.0); // 5:����
	fColor = vec3(1.0,1.0,1.0);

	EmitVertex();

	EndPrimitive();//��EndPrimitive������ʱ�����з������(Emitted)���㶼��ϳ�Ϊָ���������ȾͼԪ��
	
	//���Ϸ����˶��㣬���Ǵ�ԭʼ����λ��ƽ����һ�ξ��룬֮�������EndPrimitive��������������ϳ�Ϊһ���������������������
}
void main()
{
	build_house(gl_in[0].gl_Position);
}