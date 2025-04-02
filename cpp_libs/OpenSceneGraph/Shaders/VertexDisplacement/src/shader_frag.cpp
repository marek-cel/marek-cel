char shader_frag[] = "varying float height;\n"
                     "const vec4 lowerColor = vec4(0.1, 0.1, 0.1, 1.0);\n"
                     "const vec4 higherColor = vec4(0.2, 1.0, 0.2, 1.0);\n"
                     "\n"
                     "void main()\n"
                     "{\n"
                     "    gl_FragColor = mix(lowerColor, higherColor, height);\n"
                     "}\n"
                     "\n";
