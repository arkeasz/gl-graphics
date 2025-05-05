// #ifdef GL_ES
// precision mediump float;
// #endif

// uniform vec2 iResolution;
// uniform float iTime;

// void main() {
//     vec2 uv = gl_FragCoord.xy / iResolution.xy;

//     // green color with opacity
//     vec4 color = vec4(0.1, 0.8, 0.5, 0.7);

//     // background color
//     vec4 background = vec4(0.0, 0.0, 0.0, 1.0);

//     // mix the background and color based on the alpha value of the color
//     gl_FragColor = mix(background, color, color.a);
// }
