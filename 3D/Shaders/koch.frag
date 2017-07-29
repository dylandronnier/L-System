varying vec2 f_texcoord;
uniform sampler2D MyTexture;


void main(){

	// Output color = color specified in the vertex shader, 
	// interpolated between all 3 surrounding vertices
  vec2 flipped_texcoord = vec2(f_texcoord.x, 1.0 - f_texcoord.y);
  gl_FragColor = texture2D(MyTexture, flipped_texcoord);

}
