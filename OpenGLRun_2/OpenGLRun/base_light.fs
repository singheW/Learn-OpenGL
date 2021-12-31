#version 330 core
out vec4 FragColor;

in vec3 Normal;  //��������������ķ�����
in vec3 FragPos;  //����ռ�����Ķ�������
  
uniform vec3 lightPos; 
uniform vec3 viewPos; //�����λ������
uniform vec3 lightColor;
uniform vec3 objectColor;

void main()
{
    // ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;//�ù����ɫ����һ����С�ĳ����������ӣ��ٳ����������ɫ��Ȼ�����ս����ΪƬ�ε���ɫ��
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);//�������ǹ�Դλ����Ƭ��λ���������������
    float diff = max(dot(norm, lightDir), 0.0);//�����Դ�Ե�ǰƬ��ʵ�ʵ�������Ӱ��
    vec3 diffuse = diff * lightColor;//���Թ����ɫ���õ��������������������֮��ĽǶ�Խ������������ͻ�ԽС��
    
    // specular
    float specularStrength = 0.5;//����һ������ǿ��(Specular Intensity)����
    vec3 viewDir = normalize( viewPos- FragPos);//�������߷�������
    vec3 reflectDir = reflect(-lightDir, norm);  //���߷���������Ӧ�����ŷ�����ķ���������reflect(�ӹ�Դָ��Ƭ��λ�õ�����, ������);
    float spec = pow(max(dot( viewDir,reflectDir), 0.0), 32);//�ȼ������߷����뷴�䷽��ĵ�ˣ���ȷ�������Ǹ�ֵ����ȡ32���ݡ�32�Ǹ߹�ķ���ȣ���ϣ���������ۣ�����ָ������Ϊ32��
    vec3 specular = specularStrength * spec * lightColor;  
        
    vec3 result = (ambient + diffuse + specular ) * objectColor;//Phong ambient +diffuse + specular
    FragColor = vec4(result, 1.0);//Ƭ�����������ɫ��
} 