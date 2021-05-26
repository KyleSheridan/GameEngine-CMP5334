#version 140

in vec3 vertexPos3D;
in vec2 vUV;
out vec2 uv;

uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;

out float fog_amount;

uniform float fog_start;
uniform float fog_range;

void main() {
	vec4 v = vec4(vertexPos3D.xyz, 1);
	vec4 posInWorld = transform * v;
	v = projection * view * posInWorld;

	gl_Position = v;
	uv = vUV;

	vec4 pos_rel_eye = view * posInWorld;
	float distance = length(pos_rel_eye.xyz);
	fog_amount = (distance - fog_start) / fog_range;
	fog_amount = clamp(fog_amount, 0.0f, 1.0f);
}