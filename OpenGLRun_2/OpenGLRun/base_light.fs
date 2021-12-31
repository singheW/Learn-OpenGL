#version 330 core
out vec4 FragColor;

in vec3 Normal;  //用来计算漫反射的法向量
in vec3 FragPos;  //世界空间坐标的顶点数据
  
uniform vec3 lightPos; 
uniform vec3 viewPos; //摄像机位置坐标
uniform vec3 lightColor;
uniform vec3 objectColor;

void main()
{
    // ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;//用光的颜色乘以一个很小的常量环境因子，再乘以物体的颜色，然后将最终结果作为片段的颜色：
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);//光向量是光源位置与片段位置向量间的向量差
    float diff = max(dot(norm, lightDir), 0.0);//计算光源对当前片段实际的漫发射影响
    vec3 diffuse = diff * lightColor;//乘以光的颜色，得到漫反射分量。两个向量之间的角度越大，漫反射分量就会越小：
    
    // specular
    float specularStrength = 0.5;//定义一个镜面强度(Specular Intensity)变量
    vec3 viewDir = normalize( viewPos- FragPos);//计算视线方向向量
    vec3 reflectDir = reflect(-lightDir, norm);  //视线方向向量对应的沿着法线轴的反射向量。reflect(从光源指向片段位置的向量, 法向量);
    float spec = pow(max(dot( viewDir,reflectDir), 0.0), 32);//先计算视线方向与反射方向的点乘（并确保它不是负值），取32次幂。32是高光的反光度，不希望过于显眼，所以指数保持为32。
    vec3 specular = specularStrength * spec * lightColor;  
        
    vec3 result = (ambient + diffuse + specular ) * objectColor;//Phong ambient +diffuse + specular
    FragColor = vec4(result, 1.0);//片段最后的输出颜色。
} 