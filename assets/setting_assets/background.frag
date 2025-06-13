#ifdef GL_ES
precision lowp float;
#endif

uniform float time;
uniform vec2 resolution;
uniform vec2 mouse;
uniform sampler2D backgroundTexture;

#define iTime time
#define iResolution resolution

float hash(float n) {
    return fract(sin(n) * 78757.5757 + cos(n) * 71767.8727);
}

float noise(vec2 p) {
    vec2 i = floor(p);
    vec2 f = fract(p);
    vec2 u = f * f * (3.0 - 2.0 * f);

    return mix(mix(hash(i.x + hash(i.y)), hash(i.x + 1.0 + hash(i.y)), u.x),
               mix(hash(i.x + hash(i.y + 1.0)), hash(i.x + 1.0 + hash(i.y + 1.0)), u.x), u.y);
}

vec3 auroraLayer(vec2 uv, float speed, float intensity, vec3 color) {
    float t = iTime * speed;
    vec2 scaleXY = vec2(2.0, 2.0);
    vec2 movement = vec2(2.0, -2.0);
    vec2 p = uv * scaleXY + t * movement;
    float n = noise(p + noise(color.xy + p + t));
    float aurora = smoothstep(0.0, 0.1, n - uv.y) * (1.0 - smoothstep(0.0, 0.5, n - uv.y));
    return aurora * intensity * color;
}

void mainImage(out vec4 fragColor, in vec2 fragCoord) {
    vec2 uv = fragCoord.xy / iResolution.xy;

    vec2 mouseNorm = mouse / iResolution;
    vec2 mouseOffset = (mouseNorm - 0.5) * 0.03;

    vec3 bg = texture2D(backgroundTexture, vec2(uv.x, 1.0 - uv.y) + mouseOffset).rgb;

    vec3 flames = vec3(0.0);
    flames += auroraLayer(uv, 0.05, 0.3, vec3(0.45, 0.15, 0.03));  // Rouge sombre
    flames += auroraLayer(uv, 0.1, 0.4, vec3(0.6, 0.2, 0.05));    // Orange brûlé
    flames += auroraLayer(uv, 0.15, 0.3, vec3(0.4, 0.2, 0.02));   // Brun rougeâtre
    flames += auroraLayer(uv, 0.07, 0.2, vec3(0.2, 0.05, 0.01));  // Ombres chaudes

    vec3 skyColor1 = vec3(0.2, 0.1, 0.3);
    vec3 skyColor2 = vec3(0.2, 0.1, 0.1);

    flames += skyColor2 * (1.0 - smoothstep(0.0, 2.0, uv.y));
    flames += skyColor1 * (1.0 - smoothstep(0.0, 1.0, uv.y));

    float brightness = dot(flames, vec3(0.299, 0.587, 0.114));
    float alpha = smoothstep(0.1, 0.4, brightness) * 0.6;

    float fadeDuration = 3.0;
    float fadeFactor = clamp(iTime / fadeDuration, 0.0, 1.0);
    alpha *= fadeFactor;

    vec3 finalColor = mix(bg, flames, alpha);

    fragColor = vec4(finalColor, 1.0);
}

void main(void) {
    mainImage(gl_FragColor, gl_FragCoord.xy);
}
