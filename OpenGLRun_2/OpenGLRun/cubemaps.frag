#version 330 core
out vec4 FragColor;
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform sampler2D texture_normal1;

in vec2 TexCoords;
in vec3 Normal;
in vec3 Position;

uniform vec3 cameraPos;
uniform samplerCube skybox;

void main()
{    
float ratio = 1.00/1.52;
    vec3 I = normalize(Position - cameraPos);
 //   vec3 R = reflect(I, normalize(Normal));//∑¥…‰
    vec3 R = refract(I,normalize(Normal),ratio);
    FragColor = vec4(texture(skybox, R).rgb, 1.0);

}