#type vertex
#version 330 core
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec3 aColor;

out vec4 fColor;

void main() {
	fColor = vec4(aColor, 1.0f);

	gl_Position = vec4(aPos, 1.0f, 1.0f);
}

#type fragment
#version 330 core

in vec4 fColor;

out vec4 color;

void main() {
	color = fColor;
}
