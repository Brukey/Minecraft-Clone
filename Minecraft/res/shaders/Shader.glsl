#vertex
#version 400 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 uv;
layout(location = 2) in vec3 normal;
layout(location = 3) in float textureSlot;

uniform mat4 viewprojectionmatrix;

out vec2 texCoord;
out float f_textureSlot;
out vec3 f_normal;

void main() {

	gl_Position = viewprojectionmatrix * vec4(position, 1.0);
	texCoord = uv;
	f_textureSlot = textureSlot;
	f_normal = normal;
}

#fragment
#version 400 core
in vec2 texCoord;
in float f_textureSlot;
in vec3 f_normal;
out vec4 color;


uniform sampler2D samplers[30];

void main() {
	int texId = int(round(f_textureSlot));
	
	color = texture(samplers[texId], texCoord);
	//color = vec4(f_normal, 1.0);
}