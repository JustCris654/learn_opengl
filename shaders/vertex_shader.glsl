#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 vertexColor;

uniform float offSet;

void main() {
    gl_Position = vec4(aPos.x + offSet, -aPos.y, aPos.z, 1.0);
    vertexColor = aColor;   // set vertexColor to the input color we 
                            // got from vertex data
}


