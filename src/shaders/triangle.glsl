//shader vertex
#version 330 core
layout (location = 0) in vec3 position; 
layout (location = 1) in vec3 aColor;

out vec3 ourColor;

uniform mat4 transform;

void main() {
    gl_Position = transform * vec4(position, 1.0);
    ourColor = aColor;
}

//shader fragment
#version 330 core
layout(location = 0) out vec4 color;

void main()
{
	color = vec4(1.0, 0.0, 0.0, 1.0);
}
