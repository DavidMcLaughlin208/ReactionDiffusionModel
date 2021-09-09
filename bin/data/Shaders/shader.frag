 #version 440

layout(std430, binding = 1) buffer newMap {
	vec2 newCells[];
};

uniform int screenWidth;
uniform int cellsSize;
uniform float xRatio;
uniform float yRatio;
uniform vec4 aColor;
uniform vec4 bColor;
 
void main(void) {
	float x = gl_FragCoord.x / xRatio; 
    float y = gl_FragCoord.y / yRatio; 
    int index = int(x) + int(int(y) * screenWidth);
	if (index > cellsSize - 1 || index < 0) {
		gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
	} else {
		vec2 cell = newCells[index];
		//gl_FragColor = vec4(cell.x * aColor, cell.y * bColor, 0.0, 1.0);
		gl_FragColor = mix(aColor, bColor, cell.x);
	}
}