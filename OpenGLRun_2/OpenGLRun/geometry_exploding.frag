#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 FragPos;
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform sampler2D texture_normal1;
//方向光
struct DirLight {
    vec3 direction;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
  
    float constant;
    float linear;
    float quadratic;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;       
};
#define NR_POINT_LIGHTS 4

uniform vec3 viewPos;
uniform DirLight dirLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform SpotLight spotLight;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

//方向光
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // 漫反射着色
    float diff = max(dot(normal, lightDir), 0.0);
    // 镜面光着色
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0f);
    // 合并结果
    vec3 ambient  = light.ambient  * texture(texture_diffuse1, TexCoords).xyz;
    vec3 diffuse  = light.diffuse  * diff * texture(texture_diffuse1, TexCoords).xyz;
    vec3 specular = light.specular * spec * texture(texture_specular1, TexCoords).xyz;
    return (ambient + diffuse + specular);
}

//点光源
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // 漫反射着色
    float diff = max(dot(normal, lightDir), 0.0);
    // 镜面光着色
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0f);
    // 衰减
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + 
                 light.quadratic * (distance * distance));    
    // 合并结果
    vec3 ambient  = light.ambient  * texture(texture_diffuse1, TexCoords).xyz;
    vec3 diffuse  = light.diffuse * diff * texture(texture_diffuse1, TexCoords).xyz;
    vec3 specular = light.specular * spec* texture(texture_specular1, TexCoords).xyz;
    ambient  *= attenuation;
   diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}
// 聚光灯
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0f);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    vec3 ambient  = light.ambient  * texture(texture_diffuse1, TexCoords).xyz;
    vec3 diffuse  = light.diffuse * diff * texture(texture_diffuse1, TexCoords).xyz;
    vec3 specular = light.specular * spec* texture(texture_specular1, TexCoords).xyz;
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular)* 5;
}

void main()
{    
    vec3 norm = texture(texture_normal1,TexCoords).xyz;
     vec3 viewDir = normalize(viewPos - FragPos);
     vec3 result = CalcDirLight(dirLight, norm, viewDir);
      // 点光源
       //vec3 result;
     for(int i = 0; i < NR_POINT_LIGHTS; i++)
     result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);  
     
     // 聚光灯
     result += CalcSpotLight(spotLight, norm, FragPos, viewDir);  
    FragColor =vec4(result,1.0f);
     //   FragColor = vec4(1.0, 1.0, 0.0, 1.0);
}

