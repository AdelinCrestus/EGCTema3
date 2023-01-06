#version 330

// Input
in vec2 texcoord;
in vec3 world_position;
in vec3 world_normal;

// Uniform properties
uniform sampler2D texture_1;
uniform sampler2D texture_2;
// TODO(student): Declare various other uniforms

uniform vec3 eye_position;
uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;
uniform vec3 positions[150];
uniform vec3 colors[150];
uniform int N;

// Output
layout(location = 0) out vec4 out_color;

float f(vec3 L,vec3 Light_Pos)
{
    vec3 N = normalize(world_normal);
    vec3 V = normalize(eye_position - world_position);
    //vec3 L = normalize(Light_Pos- world_position);
    vec3 H = normalize(L+V);
    float diffuse_light = material_kd * max(dot(N,L), 0);
    float specular_light;
    if(diffuse_light > 0)
    {
        specular_light = material_ks * pow(max(dot(N,H), 0), 2);
    }

    float distance = distance(Light_Pos, world_position);
    float factorAtenuare = 1/pow(distance,2);
    
    return factorAtenuare * (diffuse_light + specular_light);
}




void main()
{
    // TODO(student): Calculate the out_color using the texture2D() function.
    float ambient_light = 0.25;
    int i = 0;
    out_color = texture2D(texture_1, texcoord);
    float culoareObiect = ambient_light + f(vec3(0, -1, 0), world_position + vec3(0,1.5,0));
    float culoareObiectpct = 0.0;
    vec3 objcolor = vec3(0);
    for(i = 1 ; i < N; i++)
    {
        culoareObiectpct = f(vec3(0, -1, 0), positions[i] + vec3(0,1,0));
        objcolor += colors[i]*culoareObiectpct;
    }
    out_color = out_color * culoareObiect + vec4(objcolor, 0);
    

}
