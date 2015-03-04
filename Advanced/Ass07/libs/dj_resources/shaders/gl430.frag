uniform sampler2D uSampler;

varying vec3 color;
varying vec3 lighting;
varying vec2 texture_coord;

void main() {
	vec4 tex = texture2D(uSampler, vec2(texture_coord.s, texture_coord.t));
	gl_FragColor = vec4(gl_Color * tex);
}
