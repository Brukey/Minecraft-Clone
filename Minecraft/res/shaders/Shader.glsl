#vertex
#version 400 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 uv;

uniform mat4 projectionmatrix;
uniform mat4 viewmatrix;

out vec2 texCoord;

void main() {

	gl_Position = viewmatrix * projectionmatrix * vec4(position, 0.0, 1.0);
	texCoord = uv;
}

#fragment
#version 400 core
in vec2 texCoord;
out vec4 color;

uniform sampler2D sampler;

void main() {
	color = texture(sampler, texCoord);
}