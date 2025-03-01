#version 330

// Input
// TODO(student): Get vertex attributes from each location
layout(location=0) in vec3 position;
layout(location=1) in vec3 normal;
layout(location=3) in vec3 color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

// Output
out vec3 f_color;


float random (in vec2 st) {
    return fract(sin(dot(st.xy,
                         vec2(12.9898,78.233)))
                 * 43758.5453123);
}

float noise (in vec2 st) {
    vec2 i = floor(st);
    vec2 f = fract(st);

    
    float a = random(i);
    float b = random(i + vec2(1.0, 0.0));
    float c = random(i + vec2(0.0, 1.0));
    float d = random(i + vec2(1.0, 1.0));

    vec2 u = f*f*(3.0-2.0*f);
    

    
    return mix(a, b, u.x) +
            (c - a)* u.y * (1.0 - u.x) +
            (d - b) * u.x * u.y;
}

void main()
{
    float height = noise(vec2(position.x * 0.1, position.z * 0.1));
    
    f_color=mix(vec3(0.2, 0.8, 0.2),vec3(0.6, 0.4, 0.2),height);
  
    height=height/2;
    if(height>0.5)
	{
		height=0.5;
	}
    vec3 updated_position = vec3(position.x, height, position.z);
    updated_position = vec3(position.x, height, position.z);

    gl_Position=Projection*View*Model*vec4(updated_position,1);

}
