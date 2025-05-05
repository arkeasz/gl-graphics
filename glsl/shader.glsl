// what is wrong with this shader?

int sin(int x) {
    return x;
}

void main() {
    float a = sin(1.0);
    float b = sin(2.0);
    // render

    varying vec4 gl_TexCoord[];

    gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);


}
