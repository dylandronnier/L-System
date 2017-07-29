
// Interpolated values from the vertex shaders
varying vec3 fragmentColor;


void main(){

	// Output color = color specified in the vertex shader, 
	// interpolated between all 3 surrounding vertices
  gl_FragColor = vec4(fragmentColor.x,fragmentColor.y,fragmentColor.z,1.0);

}
