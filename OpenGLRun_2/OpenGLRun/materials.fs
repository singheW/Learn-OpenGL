#version 330 core
out vec4 FragColor;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;    
    float shininess;
}; 

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};


uniform Material material;
uniform Light light;

in vec3 Normal;  //��������������ķ�����
in vec3 FragPos;  //����ռ�����Ķ�������
  
uniform vec3 viewPos; //�����λ������


void main()
{
    // ambient
    vec3 ambient = light.ambient * material.ambient;//�ù����ɫ����һ����С�ĳ����������ӣ��ٳ����������ɫ��Ȼ�����ս����ΪƬ�ε���ɫ��
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);//�������ǹ�Դλ����Ƭ��λ���������������
    float diff = max(dot(norm, lightDir), 0.0);//�����Դ�Ե�ǰƬ��ʵ�ʵ�������Ӱ��
    vec3 diffuse =   light.diffuse * (diff*material.diffuse);//���Թ����ɫ���õ��������������������֮��ĽǶ�Խ������������ͻ�ԽС��
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);//�������߷�������
    vec3 reflectDir = reflect(-lightDir, norm);  //���߷���������Ӧ�����ŷ�����ķ���������reflect(�ӹ�Դָ��Ƭ��λ�õ�����, ������);
    float spec = pow(max(dot(viewDir,reflectDir), 0.0), material.shininess);//�ȼ������߷����뷴�䷽��ĵ�ˣ���ȷ�������Ǹ�ֵ����ȡ32���ݡ�32�Ǹ߹�ķ���ȣ���ϣ���������ۣ�����ָ������Ϊ32��
    vec3 specular =  light.specular * (spec * material.specular);  
        
    vec3 result = (ambient +diffuse + specular );//
    FragColor = vec4(result, 1.0);//Ƭ�����������ɫ��
} 