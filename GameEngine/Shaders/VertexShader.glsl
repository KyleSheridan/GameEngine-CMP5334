#version 330 core

layout(location = 0) in vec4 vertexPosition;
layout(location = 1) in vec2 uvCoordinates;
layout(location = 2) in vec3 vertexNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 out_uv;
out vec3 out_normal;
out vec3 fragPosition;

void main()
{
    gl_Position = projection * view * model * vertexPosition;
    out_uv = uvCoordinates;
    out_normal = vec3(model * vec4(vertexNormal, 1.0f));
    fragPosition = vec3(model * vertexPosition);
}