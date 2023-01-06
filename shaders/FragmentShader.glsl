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
uniform vec3 pos_lighting[150];
uniform vec3 spotPos;
uniform int N;
uniform int M;

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

float spotlight(vec3 dir, vec3 pos)
{
    float cutt_off = radians(30.0f);
    vec3 L = normalize(pos - world_position);
    float spot_light = dot(-L, dir);
    float spot_light_limit = cos(cutt_off);
    float linear_att;
    float light_att_factor;
    float factorAtenuare;
    float diffuse_light;
    float specular_light;
    if(spot_light > cos(cutt_off))
    {
        vec3 N = normalize(world_normal);
        vec3 V = normalize(eye_position- world_position);
        vec3 H = normalize(L+V);
        diffuse_light = 0.8 * max(dot(N,L), 0); //material_kd
        
        if(diffuse_light > 0)
        {
            specular_light = 0.75 * pow(max(dot(N,H), 0), 2);//material_ks
        }
        float distance = distance(pos, world_position);
        factorAtenuare = 1.0f/pow(distance,2);
        linear_att = (spot_light - spot_light_limit) / (1.0f - spot_light_limit);
        light_att_factor = pow(linear_att, 2);

    }
    else
    {
        light_att_factor = 0;
    }

    return (diffuse_light + specular_light) * light_att_factor;

}

float spotlight2(vec3 Light_Dir,vec3 Light_Pos)
{
    float cut_off = 0.5f;
    vec3 N = normalize(vec3(0,1,0));
    vec3 V = normalize(eye_position - world_position);
    vec3 L = normalize(Light_Pos- world_position);
    vec3 H = normalize(L+V);
    float diffuse_light = material_kd * max(dot(N,L), 0);
    float specular_light;
    if(diffuse_light > 0)
    {
        specular_light = material_ks * pow(max(dot(N,H), 0), 5);
    }
    float light_att_factor = 1;
    float spot_light = dot(-L, Light_Dir);
    
    float spot_light_limit = cos(cut_off);
    if(spot_light > cos(cut_off))
    {
        float linear_att = (spot_light - spot_light_limit) / (1.0f - spot_light_limit);
        light_att_factor = pow(linear_att, 2);
    }
    else
    {
        light_att_factor = 0;
    }
    
    float distance = distance(Light_Pos, world_position);
    float factorAtenuare = 1/pow(distance,2);


    return factorAtenuare * (diffuse_light + specular_light) * light_att_factor;
}



void main()
{
    // TODO(student): Calculate the out_color using the texture2D() function.
    float ambient_light = 0.5;
    int i = 0;
    out_color = texture2D(texture_1, texcoord);
    float culoareObiect = ambient_light;// + f(vec3(0, -1, 0), world_position + vec3(0,1.5,0));
    float culoareObiectpct = 0.0;
    vec3 objcolor = vec3(0);
    for(i = 1 ; i < N; i++)
    {
        culoareObiectpct = f(vec3(0, -1, 0), positions[i] + vec3(0,1,0));
        objcolor += colors[i]*culoareObiectpct;
    }
    float culoareObiectSpot = 0.0f;
    for(int i = 0; i < M; i++)
    {
        culoareObiectSpot += spotlight2(vec3(0, -1, 0),pos_lighting[i] + spotPos );
        culoareObiectSpot += spotlight2(vec3(0, -1, 0), pos_lighting[i] + spotPos + vec3(-2*spotPos.x, 0, 0));
    }
    out_color = out_color * culoareObiect + vec4(objcolor, 0) + vec4(1) * culoareObiectSpot;
    

}
