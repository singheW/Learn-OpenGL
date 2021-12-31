#version 330 core
layout (triangles) in;
layout (line_strip, max_vertices = 6) out;

in VS_OUT {
    vec2 texCoords;
    vec3 normal;
} gs_in[];
const float MAGNITUDE = 0.04;

//������ɫ�������ÿһ�����㣨����һ��λ��������һ����������������ÿ��λ������������һ����������
void GenerateLine(int index)
{
    gl_Position = gl_in[index].gl_Position;
    EmitVertex();
    gl_Position = gl_in[index].gl_Position + vec4(gs_in[index].normal,0.0) * MAGNITUDE;//������һ��MAGNITUDE��������������ʾ���ķ�������С���������Ǿ��е���ˣ���
    EmitVertex();
    EndPrimitive();
}

out vec2 TexCoords; 

uniform float time;

vec4 explode(vec4 position, vec3 normal)//����һ��explode��������ʹ�÷������Ͷ���λ��������Ϊ�����������������һ��������������λ���������ŷ�����������λ��֮��Ľ��
{
    float magnitude = 2.0;//sin��������һ��time������������ʱ�䷵��һ��-1.0��1.0֮���ֵ����Ϊ���ǲ������������ڱ�ը(Implode)��
    vec3 direction = normal * ((sin(time) + 1.0) / 2.0) * magnitude; //���ǽ�sinֵ�任����[0, 1]�ķ�Χ�ڡ����յĽ�������normal������
    return position + vec4(direction, 0.0);//�������յ�direction�����ᱻ�ӵ�λ�������ϡ�
}

vec3 GetNormal()//�������������в������ȡ������
{
    vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
    vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
    return normalize(cross(a, b));
}

void main() {    
    vec3 normal = GetNormal();

    gl_Position = explode(gl_in[0].gl_Position, normal);
    TexCoords = gs_in[0].texCoords;//�ڷ��䶥��֮ǰ����˶�Ӧ���������ꡣ
    EmitVertex();
    gl_Position = explode(gl_in[1].gl_Position, normal);
    TexCoords = gs_in[1].texCoords;
    EmitVertex();
    gl_Position = explode(gl_in[2].gl_Position, normal);
    TexCoords = gs_in[2].texCoords;
    EmitVertex();
    EndPrimitive();

    GenerateLine(0);
    GenerateLine(1);
    GenerateLine(2);
}