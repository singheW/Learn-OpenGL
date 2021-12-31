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
	vec3 projCoords = FragPosLightSpace.xyz / FragPosLightSpace.w; // 执行透视除法
	projCoords = projCoords * 0.5 + 0.5;//因为深度贴图的深度范围为0-1，使用projCoords从深度贴图中采样，所以将NDC坐标变换到0-1的范围

	float closetDepth = texture(shadowMap,projCoords.xy).r; // 取得最近点的深度(使用[0,1]范围下的fragPosLight当坐标)
	float currentDepth = projCoords.z;// 取得当前片段在光源视角下的深度

	//计算阴影偏移（基于深度图分辨率和斜率）
	vec3 normal = normalize(fs_in.Normal);
	vec3 lightDir = normalize(lightPos - fs_in.FragPos);
	float bias = max(0.5*(1.0- dot(normal,lightDir)),0.005);//使用点乘根据表面朝向光线的角度更改偏移量,这样整个表面就正确地被照亮
	//检查当前片段位置是否在阴影里
	//float shadow = currentDepth - bias > closetDepth ? 1.0:0.0;
	//一个简单PCF的实现是从纹理像素四周对深度贴图采样，然后把结果平均起来：
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

		//灯光截头体far_Plane外的区域，阴影保持在0.0
		if(projCoords.z > 1.0)//当一个点比光的原平面还要远时，他的投影坐标的z坐标大于1.0，解决深度贴图采样超出的问题
		shadow = 0.0;//只要投影向量的z坐标大于1.0，就把shadow的值强制设为0.0

//	float shadow = currentDepth > closetDepth ? 1.0:0.0; // 检查当前片段是否在阴影中
	return shadow;
}

void main()//检测一个片段是否在阴影中
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

	//计算阴影
	//float shadow = ShadowCalculation(fs_in.FragPosLightSpace);
	float shadow = shadows ? ShadowCalculation(fs_in.FragPosLightSpace) : 0.0;
	shadow = min(shadow,0.75);

//片段着色器使用Blinn-Phong光照模型渲染场景。计算一个shadow值，当fragment在阴影中时是1.0，在阴影外是0.0.
//然后diffuse和specular乘以这个阴影值，由于散射阴影不会全黑。我们把ambient分量从乘法中剔除。
	vec3 lighting = (ambient + (1.0-shadow) * (diffuse + specular)) * color;

	FragColor = vec4(lighting,1.0);
}
