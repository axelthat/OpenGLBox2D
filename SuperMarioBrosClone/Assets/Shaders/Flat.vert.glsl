#version 330 core

layout(location = 0) in vec2 a_Pos;
layout(location = 1) in vec4 a_Color;

uniform mat4 u_Projection;
uniform mat4 u_View;
uniform mat4 u_Model;
uniform vec4 u_Color;
uniform bool u_Batch;

out vec4 v_Color;

void main() {
	if(u_Batch) {
		v_Color = a_Color;
	} else {
		v_Color = u_Color;
	}

	gl_Position = u_Projection * u_View * u_Model * vec4(a_Pos.xy, 0.0f, 1.0f);
}