uniform sampler2D filter_tex;
uniform float dX;
uniform float dY;

float threshold(in float thr1, in float thr2, in float val) {
	if (val < thr1) { return 0.0; }
	if (val > thr2) { return 1.0; }
}

float pixel_average (in vec4 pix) {
	return (pix.r + pix.g + pix.b) / 3.0;
}

vec4 get_pixel(in vec2 coords, in float dx, in float dy) {
	return texture2D(filter_tex, coords + vec2(dx, dy));
}

float IsEdge (in vec2 coords) {
	
	float pix[9];
	float delta;
	int k = -1;
	
	for (int i = -1; i < 2; ++i) {
		for (int j = -1; j < 2; ++j) {
			k++;
			vec4 thisPix = get_pixel(coords, float(i) * dX, float(j) * dY);
			pix[k] = pixel_average(thisPix);
		}
	}
	
	delta = (abs(pix[1] - pix[7]) + abs(pix[5]-pix[3]) + abs(pix[0]-pix[8]) + abs(pix[2]-pix[6])) / 4.0;
	
	float min = 0.01;
	float max = 0.05;
	return threshold(min, max, clamp(1.8*delta, 0.0, 1.0));
}

void main() 
{
	vec4 color = vec4(0);
	color.b = IsEdge(gl_TexCoord[0].xy);
	gl_FragColor = color;
}
