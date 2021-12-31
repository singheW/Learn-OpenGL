#version 330 core
out vec4 FragColor;
in vec2 TexCoords;

in VS_OUT//ÊäÈë½Ó¿Ú¿é
{
	vec2 TexCoords;
}fs_in;

void main()
{
//FragColor = texture(texture,fs_in.TexCoords);
	FragColor = vec4(0.0,1.0,0.0,1.0);
}