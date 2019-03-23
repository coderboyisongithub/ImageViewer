    #shader vertex
    #version 330 core 

layout(location = 0) in vec4 positions;
layout(location=0) in vec2 texCoords;

    uniform mat4 translation_matrix; //active
    uniform mat4 rotation_matrix;
    mat4 model_matrix; //
    mat4 projection_matrix;
    out vec4 pos;
    out vec2 frag_TexCoord;

    void main()
    {
    
    rotation_matrix;
vec4 v=positions;
 
    gl_Position=rotation_matrix*translation_matrix*v; //translation matrix operated with POS vector..
    pos=gl_Position;
frag_TexCoord=texCoords;
    translation_matrix;

    }

//fragment shader

#shader fragment  
    #version 330 core

    layout(location=0) out vec4 color;
    in vec4 pos;
    in vec2 frag_TexCoord;
    uniform float col;
uniform sampler2D a_texture;


    void main()
    {
    col;
    a_texture;
    //color=texture(a_texture,frag_TexCoord);
    color=texture(a_texture,frag_TexCoord);


    }