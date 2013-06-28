varying vec4 position;  // position of the vertex (and fragment) in world space
varying vec3 varyingNormalDirection;  // surface normal vector in world space
varying vec2 texCoords; // the texture coordinates
uniform mat4 m, v, p;
uniform mat4 v_inv;
uniform sampler2D imgTexture;
  
void main()
{
	vec4 textureColor = texture2D(imgTexture, texCoords);

	gl_FragColor = textureColor;
}