#version 150

in  vec4 vPosition;
in  vec4 vColor;
out vec4 color;

uniform mat4 model_view;
uniform mat4 face_rotations;

void main(){
    color = vColor;
    gl_Position = model_view * face_rotations * vPosition;
}
