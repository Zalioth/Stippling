#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec3 vertexColor;
layout(location = 3) in vec2 vertexUV;

// Output data ; will be interpolated for each fragment.
out vec2 UV;

// Values that stay constant for the whole mesh.
uniform mat4 mvp;

uniform vec3 pickingColor;

uniform float xLeft;
uniform float xRight;

uniform float yBottom;
uniform float yTop;

uniform float zNear;
uniform float zFar;

void main(){

        // Output position of the vertex, in clip space : MVP * position
        gl_Position =  mvp * vec4(vertexPosition,1);

        // UV of the vertex. No special space for this one.
        UV = vertexUV;
}

