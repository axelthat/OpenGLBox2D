#version 330 core

in vec4 v_Color;

out vec4 o_FragColor;

void main() {
	o_FragColor = vec4(v_Color.xyz, 1.0f);
}