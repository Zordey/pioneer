#ifdef TEXTURE0
varying vec2 texCoord0;
#endif
#ifdef VERTEXCOLOR
varying vec4 vertexColor;
#endif
#if (NUM_LIGHTS > 0)
varying vec3 eyePos;
varying vec3 normal;
<<<<<<< HEAD
=======
	#ifdef HEAT_COLOURING
		uniform mat3 heatingMatrix;
		uniform vec3 heatingNormal; // normalised
		varying vec3 heatingDir;
	#endif // HEAT_COLOURING
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
#endif

void main(void)
{
	gl_Position = logarithmicTransform();
#ifdef VERTEXCOLOR
	vertexColor = gl_Color;
#endif
#ifdef TEXTURE0
	texCoord0 = gl_MultiTexCoord0.xy;
#endif
#if (NUM_LIGHTS > 0)
	eyePos = vec3(gl_ModelViewMatrix * gl_Vertex);
	normal = normalize(gl_NormalMatrix * gl_Normal);
<<<<<<< HEAD
=======
	#ifdef HEAT_COLOURING
		heatingDir = normalize(heatingMatrix * heatingNormal);
	#endif
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
#endif
}
