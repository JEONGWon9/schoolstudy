#version 150

#if GL_ES
precision mediump float;
#endif

uniform vec2 sp,ep;
uniform float radius;
uniform vec4 color;
uniform float linewidth;


out vec4 fragColor;

void main()
{	

	float d = length(gl_FragCoord.xy);
	float lw = linewidth/2.0;
	
	fragColor = vec4(color.rgb, color.a * d);

	
}
