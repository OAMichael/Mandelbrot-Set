#version 330 core
layout (location = 0) in vec2 vPosition;
uniform mat4 transform;
out vec4 MainColor;

void main() {
    gl_Position = vec4(vPosition, 0.0, 1.0);
    vec2 p = gl_Position.xy;
    vec2 c = p;
    gl_Position = transform * vec4(vPosition, 0.0, 1.0);


    //Set default color to HSV value for black
    vec3 color = vec3(0.0, 0.0, 0.0);


    for(int i = 0; i < 300; i++) {
        //Perform complex number arithmetic
        p = vec2(p.x * p.x - p.y * p.y, 2.0 * p.x * p.y) + c;
        
        if (dot(p, p) > 4.0) {
            float colorRegulator = float(i - 1) - log( (log(dot(p, p)) / log(2.0)) ) / log(2.0);
            
            color = vec3(0.95 + 0.012 * colorRegulator , 1.0, 0.2 + 0.4 * (1.0 + sin(0.3 * colorRegulator)));
           
            break;
        }
    }
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 m = abs(fract(color.xxx + K.xyz) * 6.0 - K.www);
    MainColor.rgb = color.z * mix(K.xxx, clamp(m - K.xxx, 0.0, 1.0), color.y);
    MainColor.a = 1;
}
