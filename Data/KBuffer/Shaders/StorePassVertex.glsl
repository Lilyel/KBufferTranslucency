#version 450 core

layout (location = 0) in vec3 Position;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

out vec3 VS_Position;

void main()
{
	gl_Position = vec4(Position, 1.0) * (Model * View * Projection);

	VS_Position = vec3( vec4( Position.xyz, 1.0 ) * Model );
}