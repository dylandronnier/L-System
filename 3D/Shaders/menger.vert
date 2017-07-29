attribute vec3 coord3d;
attribute vec2 texcoord;

// Output data ; will be interpolated for each fragment.
varying vec2 f_texcoord;
// Values that stay constant for the whole mesh.
uniform mat4 MVP;

void main(){	

	// Output position of the vertex, in clip space : MVP * position
	gl_Position =  MVP * vec4(coord3d,1.0);

	// The color of each vertex will be interpolated
	// to produce the color of each fragment
        f_texcoord = texcoord ;
}
