#type vertex
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec4 aColor;

out vec4 fColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	fColor = aColor;

	gl_Position = projection * view * model * vec4(aPos, 1.0f);
}

#type fragment
#version 330 core

in vec4 fColor;

out vec4 color;

void main() {
	color = fColor;
}
