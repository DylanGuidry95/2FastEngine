#version 150

in vec4 vertColour;
in vec2 UV;

out vec4 outputColour;

uniform sampler2D Diffuse;
uniform int rows;
uniform int cols;
uniform int frame;

void main()
{
	
	//outputColour = texture(Diffuse, UV).rgba;

	int c = frame % cols;
	int r = frame / cols;
	
	float u = c / (cols*1.0f);
	float v = r / (rows*1.0f);
	
	vec2 cUV = vec2(u,v) + UV * vec2(1.0f/cols ,1.0f/rows);

	outputColour = texture(Diffuse, cUV).rgba;

		if(outputColour.rgb == vec3(0,0,0))
	{
		outputColour.a = 0;
	}
}