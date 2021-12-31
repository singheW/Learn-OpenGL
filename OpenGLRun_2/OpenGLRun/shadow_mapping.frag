#version 330 core
out vec4 FragColor;

in VS_OUT
{
	vec3 FragPos;
	vec3 Normal;
	vec2 TexCoords;
	vec4 FragPosLightSpace;
}fs_in;

uniform sampler2D diffuseTexture;
uniform sampler2D shadowMap;

uniform vec3 lightPos;
uniform vec3 viewPos;

uniform bool shadows;

float ShadowCalculation(vec4 FragPosLightSpace)
{
	vec3 projCoords = FragPosLightSpace.xyz / FragPosLightSpace.w; // ִ��͸�ӳ���
	projCoords = projCoords * 0.5 + 0.5;//��Ϊ�����ͼ����ȷ�ΧΪ0-1��ʹ��projCoords�������ͼ�в��������Խ�NDC����任��0-1�ķ�Χ

	float closetDepth = texture(shadowMap,projCoords.xy).r; // ȡ�����������(ʹ��[0,1]��Χ�µ�fragPosLight������)
	float currentDepth = projCoords.z;// ȡ�õ�ǰƬ���ڹ�Դ�ӽ��µ����

	//������Ӱƫ�ƣ��������ͼ�ֱ��ʺ�б�ʣ�
	vec3 normal = normalize(fs_in.Normal);
	vec3 lightDir = normalize(lightPos - fs_in.FragPos);
	float bias = max(0.5*(1.0- dot(normal,lightDir)),0.005);//ʹ�õ�˸��ݱ��泯����ߵĽǶȸ���ƫ����,���������������ȷ�ر�����
	//��鵱ǰƬ��λ���Ƿ�����Ӱ��
	//float shadow = currentDepth - bias > closetDepth ? 1.0:0.0;
	//һ����PCF��ʵ���Ǵ������������ܶ������ͼ������Ȼ��ѽ��ƽ��������
	float shadow = 0.0;
	vec2 texelSize = 1.0 / textureSize(shadowMap,0);
	for(int x = -1;x<= 1;++x)
	{
		for(int y = -1;y<=1;++y)
		{
			float pcfDepth = texture(shadowMap,projCoords.xy + vec2(x,y) * texelSize).r;
			shadow += currentDepth - bias > pcfDepth ? 1.0:0.0;
		}
	}
		shadow /= 9.0;

		//�ƹ��ͷ��far_Plane���������Ӱ������0.0
		if(projCoords.z > 1.0)//��һ����ȹ��ԭƽ�滹ҪԶʱ������ͶӰ�����z�������1.0����������ͼ��������������
		shadow = 0.0;//ֻҪͶӰ������z�������1.0���Ͱ�shadow��ֵǿ����Ϊ0.0

//	float shadow = currentDepth > closetDepth ? 1.0:0.0; // ��鵱ǰƬ���Ƿ�����Ӱ��
	return shadow;
}

void main()//���һ��Ƭ���Ƿ�����Ӱ��
{
	vec3 color = texture(diffuseTexture,fs_in.TexCoords).rgb;
	vec3 normal = normalize(fs_in.Normal);
	vec3 lightColor = vec3(2);
	//ambient
	vec3 ambient = 0.3 * lightColor;
	//diffuse
	vec3 lightDir = normalize(lightPos - fs_in.FragPos);
	float diff = max(dot(lightDir,normal),0.0);
	vec3 diffuse = diff * lightColor;
	//specular
	vec3 viewDir = normalize(viewPos - fs_in.FragPos);
	vec3 reflectDir = reflect(-lightDir,normal);
	float spec = 0.0;
	vec3 halfwayDir = normalize(lightDir + viewDir);
	spec = pow(max(dot(normal,halfwayDir),0.0),64.0);
	vec3 specular = spec * lightColor;

	//������Ӱ
	//float shadow = ShadowCalculation(fs_in.FragPosLightSpace);
	float shadow = shadows ? ShadowCalculation(fs_in.FragPosLightSpace) : 0.0;
	shadow = min(shadow,0.75);

//Ƭ����ɫ��ʹ��Blinn-Phong����ģ����Ⱦ����������һ��shadowֵ����fragment����Ӱ��ʱ��1.0������Ӱ����0.0.
//Ȼ��diffuse��specular���������Ӱֵ������ɢ����Ӱ����ȫ�ڡ����ǰ�ambient�����ӳ˷����޳���
	vec3 lighting = (ambient + (1.0-shadow) * (diffuse + specular)) * color;

	FragColor = vec4(lighting,1.0);
}
