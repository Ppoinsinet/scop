void main(void) {
    // Use the current time as a seed for generating pseudo-random colors
    float seed = mod(gl_FragCoord.x * 37821.0 + gl_FragCoord.y * 721.0 + mod(gl_FragCoord.x * gl_FragCoord.y, 1000.0) + mod(gl_FragCoord.y * gl_FragCoord.x, 1000.0), 1.0);
    
    // Create a random color using the seed
    vec3 randomColor = vec3(mod(seed + 0.5, 1.0), mod(seed + 0.75, 1.0), mod(seed + 0.25, 1.0));

    // Set the fragment's color
    gl_FragColor = vec4(randomColor, 1.0);
}
