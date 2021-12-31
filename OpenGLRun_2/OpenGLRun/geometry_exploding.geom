#version 330 core
layout (triangles) in;
layout (line_strip, max_vertices = 6) out;

in VS_OUT {
    vec2 texCoords;
    vec3 normal;
} gs_in[];
const float MAGNITUDE = 0.04;

//几何着色器会接收每一个顶点（包括一个位置向量和一个法向量），并在每个位置向量处绘制一个法线向量
void GenerateLine(int index)
{
    gl_Position = gl_in[index].gl_Position;
    EmitVertex();
    gl_Position = gl_in[index].gl_Position + vec4(gs_in[index].normal,0.0) * MAGNITUDE;//乘以了一个MAGNITUDE向量，来限制显示出的法向量大小（否则它们就有点大了）。
    EmitVertex();
    EndPrimitive();
}

out vec2 TexCoords; 

uniform float time;

vec4 explode(vec4 position, vec3 normal)//创建一个explode函数，它使用法向量和顶点位置向量作为参数。这个函数返回一个新向量，它是位置向量沿着法线向量进行位移之后的结果
{
    float magnitude = 2.0;//sin函数接收一个time参数，它根据时间返回一个-1.0到1.0之间的值。因为我们不想让物体向内爆炸(Implode)，
    vec3 direction = normal * ((sin(time) + 1.0) / 2.0) * magnitude; //我们将sin值变换到了[0, 1]的范围内。最终的结果会乘以normal向量，
    return position + vec4(direction, 0.0);//并且最终的direction向量会被加到位置向量上。
}

vec3 GetNormal()//对两个向量进行叉乘来获取法向量
{
    vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
    vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
    return normalize(cross(a, b));
}

void main() {    
    vec3 normal = GetNormal();

    gl_Position = explode(gl_in[0].gl_Position, normal);
    TexCoords = gs_in[0].texCoords;//在发射顶点之前输出了对应的纹理坐标。
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