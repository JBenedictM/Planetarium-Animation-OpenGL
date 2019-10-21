// ==========================================================================
// Vertex program for barebones GLFW boilerplate
//
// Author:  Sonny Chan, University of Calgary
// Date:    December 2015
// ==========================================================================
#version 410

// location indices for these attributes correspond to those specified in the
// InitializeGeometry() function of the main program
layout(location = 0) in vec3 VertexPosition;
layout(location = 1) in vec3 VertexColour;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec2 textureUV;

uniform mat4 MVP;
uniform mat4 sunMVP;

// output to be interpolated between vertices and passed to the fragment stage
//out vec3 normal;
out vec2 ftextureUV;
out vec3 position;
out vec3 fnormal;

void main()
{

    ftextureUV = textureUV;
    fnormal = normalize((MVP * vec4(normal, 0.0f))).xyz;
    

    // assign vertex position without modification
    gl_Position =  MVP * vec4(VertexPosition, 1.0);
    position = gl_Position.xyz;


}

