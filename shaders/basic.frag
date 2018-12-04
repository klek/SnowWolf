#version 130
//#extension GL_ARB_explicit_attrib_location : require

//layout (location = 0) out vec4 color;
out vec4 color;

uniform vec4 colour;
uniform vec2 light_pos;

//in DATA
//{
//	vec4 position;
//	vec4 color;
//} fs_in;
in vec4 vPosition;
in vec2 vUV;
in float vTID;
in vec4 vColor;

uniform sampler2D textures[32];

void main()
{
	//float intensity = 1.0f / length(fs_in.position.xy - light_pos);
	float intensity = 1.0f / length(vPosition.xy - light_pos);
//	color = colour * intensity;
	//color = fs_in.color * intensity;
//	color = fColor * intensity;
//	color = vColor * intensity;

	vec4 texColor = vColor;
	if ( vTID > 0.0 )
	{
		int tid = int(vTID - 0.5);
//		texColor = texture(textures[tid], vUV);
	}	
	color = texColor * intensity;
}