#version 330 core
out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    sampler2D specular; 
    sampler2D emission;
    float shininess;
}; 

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 FragPos;  
in vec3 Normal;  
in vec2 TexCoords;
  
uniform vec3 viewPos;
uniform Material material;
uniform Light light;

uniform float matrixlight;
uniform float matrixmove;
void main()
{
    // ambient
    vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;  
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;  
   // vec3 specular = light.specular * spec * (vec3(1.0)-vec3(texture(material.specular,TexCoords)));//第一题：中反转镜面光贴图的颜色值，让木头显示镜面高光而钢制边缘不反光

   vec3 emission = matrixlight * texture(material.emission,vec2(TexCoords.x,TexCoords.y + matrixmove)).rgb;

    vec3 result = ambient + diffuse + specular + emission*0.5;
    FragColor = vec4(result, 1.0);
} 