varying vec4 position;  // position of the vertex (and fragment) in world space
varying vec3 varyingNormalDirection;  // surface normal vector in world space
varying vec2 texCoords; // the texture coordinates
uniform mat4 m, v, p;
uniform mat4 mvpIn;
uniform mat4 v_inv;
uniform sampler2D imgTexture;
  
void main()
{
	// vec3 normalDirection = normalize(varyingNormalDirection);
	// vec3 viewDirection = normalize(vec3(v_inv * vec4(0.0, 0.0, 0.0, 1.0) - position));
	// vec3 lightDirection;
	// float attenuation;

	vec4 textureColor = texture2D(imgTexture, texCoords);

	// if (0.0 == light0.position.w) // directional light?
	// {
	  // attenuation = 1.0; // no attenuation
	  // lightDirection = normalize(vec3(light0.position));
	// } 
	// else // point light or spotlight (or other kind of light) 
	// {
		// vec3 positionToLightSource = vec3(light0.position - position);
		// float distance = length(positionToLightSource);
		// lightDirection = normalize(positionToLightSource);
		// attenuation = 1.0 / (light0.constantAttenuation
						   // + light0.linearAttenuation * distance
						   // + light0.quadraticAttenuation * distance * distance);

		// if (light0.spotCutoff <= 90.0) // spotlight?
		// {
			// float clampedCosine = max(0.0, dot(-lightDirection, light0.spotDirection));
			// if (clampedCosine < cos(radians(light0.spotCutoff))) // outside of spotlight cone?
			// {
				// attenuation = 0.0;
			// }
			// else
			// {
				// attenuation = attenuation * pow(clampedCosine, light0.spotExponent);   
			// }
		// }
	// }

	// vec3 ambientLighting = vec3(scene_ambient) * vec3(textureColor);

	// vec3 diffuseReflection = attenuation 
	// * vec3(light0.diffuse) * vec3(textureColor)
	// * max(0.0, dot(normalDirection, lightDirection));

	// vec3 specularReflection;
	// if (dot(normalDirection, lightDirection) < 0.0) // light source on the wrong side?
	// {
	  // specularReflection = vec3(0.0, 0.0, 0.0); // no specular reflection
	// }
	// else // light source on the right side
	// {
		// specularReflection = attenuation * vec3(light0.specular) * vec3(frontMaterial.specular) * (1.0 - textureColor.a)
		//  for usual gloss maps: "* textureColor.a"
		// * pow(max(0.0, dot(reflect(-lightDirection, normalDirection), viewDirection)), frontMaterial.shininess);
	// }

	//gl_FragColor = vec4(ambientLighting + diffuseReflection + specularReflection, 1.0);

	gl_FragColor = textureColor;
}