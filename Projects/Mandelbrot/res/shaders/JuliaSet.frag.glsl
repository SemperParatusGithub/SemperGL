uniform int u_MaxIterations;
uniform dvec2 u_ScreenSize;
uniform double u_Zoom;
uniform dvec2 u_Offset;
uniform float u_Re;
uniform float u_Im;

uniform vec3 u_Color;

int n = 0;

float mandelbrot(dvec2 c)
{
	dvec2 z = c;
	for (n = 0; n < u_MaxIterations; n++)
	{
		dvec2 znew;
		znew.x = (z.x * z.x) - (z.y * z.y) + u_Re;
		znew.y = (2.0 * z.x * z.y) + u_Im;
		z = znew;
		if ((z.x * z.x) + (z.y * z.y) > 16.0) break;
	}
	return n / float(u_MaxIterations);
}

vec4 map_to_color(float a)
{
	float r = u_Color.x * (1.0 - a) * a * a * a;
	float g = u_Color.y * (1.0 - a) * (1.0 - a) * a * a;
	float b = u_Color.z * (1.0 - a) * (1.0 - a) * (1.0 - a) * a;
	vec4 res = vec4(r, g, b, 1);
	return res;
}

void main()
{
	float n = mandelbrot(((gl_FragCoord.xy - u_ScreenSize / 2) / u_Zoom) - u_Offset);
	gl_FragColor = map_to_color(float(n));
}
