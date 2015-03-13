uniform int cursor_x;
uniform int cursor_y;

uniform int window_x;
uniform int window_y;

uniform int draw;

uniform sampler2D canvas;

void main() {
	vec2 ccoord = vec2(cursor_x, cursor_y);
	
	float tx = gl_TexCoord[0].s * float(window_x);
	float ty = gl_TexCoord[0].t * float(window_y);
	
	vec2 pcoord = vec2(tx, ty);
	vec4 canvas_color = texture2D(canvas,gl_TexCoord[0].st);
	
	float epsx = abs(ccoord.x - pcoord.x);
	float epsy = abs(ccoord.y - pcoord.y);
	
	if (epsx < 2.0 && epsy < 2.0) {
		if(draw > 0) {
				if (draw == 1) {
					canvas_color = vec4(1, 0, 0, 1);
				} else if (draw == 2) {
					canvas_color = vec4(0, 1, 0, 1);
				} else if (draw == 3) {
					canvas_color = vec4(0, 0, 1, 1);
				}
		}
	} 
	gl_FragColor = canvas_color;
}
