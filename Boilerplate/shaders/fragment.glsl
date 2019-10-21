// ==========================================================================
// Vertex program for barebones GLFW boilerplate
//
// Author:  Sonny Chan, University of Calgary
// Date:    December 2015
// ==========================================================================
#version 410

// interpolated colour received from vertex stage
in vec2 ftextureUV;
in vec3 fnormal;
in vec3 position;



// first output is mapped to the framebuffer's colour index by default
out vec4 FragmentColour;

uniform sampler2D imageTexture;
uniform bool diffuse;

vec4 sunLight = vec4(1);
vec3 lightRay = normalize(vec3(0) - position);
float cosTheta = clamp( dot(fnormal,lightRay), 0,1 ); // from http://www.opengl-tutorial.org/beginners-tutorials/tutorial-8-basic-shading/

void main(void)
{
    vec4 planetShading = texture(imageTexture, ftextureUV);
    vec4 ambientColour = vec4(0.3) * planetShading;
    if(diffuse)
        FragmentColour = ambientColour + planetShading * sunLight * cosTheta;
    else
        FragmentColour = planetShading;
}
