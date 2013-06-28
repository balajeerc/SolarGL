//Default_VS.glsl
//Simple shader emulating fixed functionality

uniform mat4 ProjectionModelViewMatrix;
attribute vec4 InVertex;	//w will be set to 1.0 automatically
//attribute vec3 InColor;		//Color specified for this vertex

//varying vec4 OutColor;

void main()
{
	gl_Position = ProjectionModelViewMatrix * InVertex;
	//OutColor = vec4(InColor, 1.f);
}