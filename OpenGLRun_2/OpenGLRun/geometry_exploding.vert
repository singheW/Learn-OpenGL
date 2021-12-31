#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
out vec3 FragPos;
layout (location = 2) in vec2 aTexCoords;

//out vec2 TexCoords;

out VS_OUT {
    vec2 texCoords;
    vec3 normal;
} vs_out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));
    vs_out.texCoords = aTexCoords;   
    gl_Position = projection * view * vec4(FragPos, 1.0);
    mat3 normalMatrix = mat3(transpose(inverse(view * model)));//使用模型提供的法线
    //为了适配（观察和模型矩阵的）缩放和旋转，在将法线变换到裁剪空间坐标之前，先用法线矩阵变换一次。
    vs_out.normal = normalize(vec3(projection * vec4(normalMatrix * aNormal,0.0)));


}