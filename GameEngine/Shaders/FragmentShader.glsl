#version 330

in vec2 out_uv;
in vec3 fragPosition;
in vec3 out_normal;
out vec4 fragmentColour;

uniform sampler2D textureSampler;
uniform vec3 lightColour;
uniform vec3 lightPosition;
uniform vec3 viewPosition;

void main() {
    //Ambient Light
    float ambientStrength = 1.0f;
    vec3 ambient = ambientStrength * lightColour;

    //Diffuse Lighting
    vec3 normal = normalize(out_normal);
    vec3 lightDirection = normalize(lightPosition - fragPosition);
    float diff = max(dot(normal, lightDirection), 0.0f);
    vec3 diffuse = diff * lightColour;

    //Specular Lighting
    float specularStrength = 0.1f;
    vec3 viewDir = normalize(viewPosition - fragPosition);
    vec3 reflectDirection = reflect(-lightDirection, normal);
    float spec = pow(max(dot(viewDir, reflectDirection), 0.0f), 32);
    vec3 specular = specularStrength * spec * lightColour;

    //Texture
    vec3 textureColour = texture(textureSampler, out_uv).xyz;

    //Combining together
    vec3 result = (ambient + diffuse) * textureColour + specular;

    fragmentColour = vec4(result, 1.0f);
}