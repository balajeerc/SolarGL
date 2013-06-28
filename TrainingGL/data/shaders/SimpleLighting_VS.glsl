attribute vec3 v_coord;
attribute vec3 v_normal;
attribute vec2 v_texcoord;
varying vec4 position;  // position of the vertex (and fragment) in world space
varying vec3 varyingNormalDirection;  // surface normal vector in world space
varying vec2 texCoords; // the texture coordinates
uniform mat4 m, v, p;
uniform mat4 mvpIn;
uniform mat3 m_3x3_inv_transp;
 
void main()
{
	vec4 v_coord4 = vec4(v_coord, 1.0);
	mat4 mvp = p*v*m;
	position = m * v_coord4;
	varyingNormalDirection = normalize(m_3x3_inv_transp * v_normal);

	texCoords = v_texcoord;
	//gl_Position = mvp * v_coord4;
	gl_Position = mvpIn * v_coord4;
}