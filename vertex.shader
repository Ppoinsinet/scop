// in vec3 in_Position;
// in vec3 in_Color;
// out vec3 pass_Color;

void main(void) {
	gl_Position = vec4(gl_Vertex);
	// pass_Color = in_Color;
}