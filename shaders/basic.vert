#version 130
//#extension GL_ARB_explicit_attrib_location : require

//layout (location = 0) in vec4 position;
//layout (location = 1) in vec4 color;
in vec4 position;
in vec2 uv;
in float tid;
in vec4 color;

uniform mat4 pr_matrix;
uniform mat4 vw_matrix = mat4(1.0);
uniform mat4 ml_matrix = mat4(1.0);

//out DATA
//{
//	vec4 position;
//	vec4 color;
//} vs_out;
out vec4 vPosition;
out vec2 vUV;
out float vTID;
out vec4 vColor;

void main()
{
	gl_Position = pr_matrix * vw_matrix * ml_matrix * position;
	//vs_out.position = ml_matrix * position;
	//vs_out.color = color;
	vPosition = ml_matrix * position;
	vUV = uv;
	vTID = tid;
	vColor = color;
}