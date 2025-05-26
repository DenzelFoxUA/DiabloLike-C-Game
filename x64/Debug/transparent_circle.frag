uniform sampler2D texture;
uniform vec2 spritePos;    // Позиція центру спрайта (в пікселях екрану)
uniform vec2 playerPos;    // Центр гравця (в пікселях екрану)
uniform float radius;      // Радіус ефекту

void main()
{
    // Витягуємо піксельний колір з текстури
    vec4 pixelColor = texture2D(texture, gl_TexCoord[0].xy);
    vec2 pixelPos = gl_FragCoord.xy;

    // Відстань від пікселя до гравця
    float dist = distance(pixelPos, playerPos);

    // Межі для плавного розмиття
    float fadeStart = radius * 0.7;
    float fadeEnd = radius;

    // Вираховуємо прозорість (0 — прозорий, 1 — повністю непрозорий)
    float alphaFactor = 1.0 - smoothstep(fadeStart, fadeEnd, dist);

    // Плавне змішування: максимум 30% прозорості
    pixelColor.a *= mix(1.0, 0.3, alphaFactor);

    gl_FragColor = pixelColor;
}
