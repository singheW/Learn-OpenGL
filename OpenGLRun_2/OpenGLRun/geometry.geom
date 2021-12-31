#version 330 core
layout (points) in;//声明从顶点着色器输入的图元类型。这需要在in关键字前声明一个布局修饰符: (points：绘制GL_POINTS图元时（1）。)
layout (triangle_strip,max_vertices = 5) out;//(Line Strip)：线条连接了一组点，形成一条连续的线，它最少要由两个点来组成。
//指定几何着色器输出的图元类型，这需要在out关键字前面加一个布局修饰符。几何着色器同时希望我们设置一个它最大能够输出的顶点数量（如果超过,OpenGL将不会绘制多出的顶点）

in VS_OUT//获取前一着色器阶段的输出。几何着色器的输入是一个图元的所有顶点。
{
	vec3 color;

} gs_in[];

out vec3 fColor;

//使用几何着色器函数，EmitVertex和EndPrimitive，来生成新的数据 //几何着色器希望你能够生成并输出至少一个定义为输出的图元。
void build_house(vec4 position)
{
	fColor = gs_in[0].color;// gs_in[0] 因为只有一个输入顶点
	gl_Position = position +vec4(-0.2,-0.2,0.0,0.0); // 1:左下  
	EmitVertex();//每次我们调用EmitVertex时，gl_Position中的向量会被添加到图元中来
		gl_Position = position +vec4(0.2,-0.2,0.0,0.0);// 2:右下
	EmitVertex();//在一个或多个EmitVertex调用之后重复调用EndPrimitive能够生成多个图元。
		gl_Position = position +vec4(-0.2,0.2,0.0,0.0);//3:左上
	EmitVertex();
		gl_Position = position +vec4(0.2,0.2,0.0,0.0);// 4:右上
	EmitVertex();
		gl_Position = position +vec4(0.0,0.4,0.0,0.0); // 5:顶部
	fColor = vec3(1.0,1.0,1.0);

	EmitVertex();

	EndPrimitive();//当EndPrimitive被调用时，所有发射出的(Emitted)顶点都会合成为指定的输出渲染图元。
	
	//以上发射了顶点，它们从原始顶点位置平移了一段距离，之后调用了EndPrimitive，将这两个顶点合成为一个包含两个顶点的线条。
}
void main()
{
	build_house(gl_in[0].gl_Position);
}