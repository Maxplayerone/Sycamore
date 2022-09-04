#type vertex
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec4 aColor;
layout(location = 2) in float aTexIndex;
layout(location = 3) in vec2 aTexCoords;

out vec4 fColor;
out vec2 fTexCoords;
out float fTexIndex;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	fColor = aColor;
	fTexCoords = aTexCoords;
	fTexIndex = aTexIndex;

	gl_Position = projection * view * model * vec4(aPos, 1.0f);
}

#type fragment
#version 330 core

in vec4 fColor;
in vec2 fTexCoords;
in float fTexIndex;

uniform sampler2D u_Textures[8];

out vec4 color;

void main() {
	int index = int(fTexIndex);
	if(index > 0) {
		color = texture(u_Textures[index], fTexCoords);
	}
	else {
		color = fColor;
	}
}
