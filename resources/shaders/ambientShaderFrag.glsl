#version 330 core
out vec4 FragColor;

uniform vec3 lightColor;
uniform vec3 lightPos;

in vec3 Normal;
in vec3 FragPos;

void main() {
    vec3 norm = normalize(Normal);
    vec3 c = norm * 0.5 + 0.5;
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    //FragColor = vec4(diff, diff, diff, 1.0);
    //FragColor = vec4(c, 1.0);
    vec3 diffuse = diff * lightColor;
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
    vec3 result = (ambient + diffuse) * vec3(1.0, 0.5, 0.1);
    FragColor = vec4(result, 1.0);
};
