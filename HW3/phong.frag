
#version 330 core
out vec4 color;

in vec3 FragPos;  
in vec3 Normal;  
  
uniform vec3 lightPos; 
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform vec3 objectColor;

void main()
{
    // TODO: Replace with your code...
    // If gl_Position was set correctly, this gives a totally red cube
    //color = vec4(vec3(1.f,0.f,0.f), 1.0f);

    //Reference material: https://learnopengl.com/Lighting/Basic-Lighting
    
    // Ambient: the light surrounding room always exists
    float ambientStrength = 0.1f;     
    vec3 ambient = ambientStrength * lightColor;
  	
    // Diffuse: simulates directional impact a light obj. has on an obj. 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);	
    vec3 diffuse = diff * lightColor;		
    
    // Specular: simulates the bright spot of a light that appears on shiny obj.
    float specularStrength = 0.5f;
    vec3 viewDir = normalize(viewPos - FragPos); 
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;  

    color = vec4((ambient + diffuse + specular)*objectColor, 1.0f); 
} 
