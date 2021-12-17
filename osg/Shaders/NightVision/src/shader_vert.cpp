char shader_vert[] = "void main()\n"
                     "{\n"
                     "   gl_Position = ftransform();\n"
                     "   gl_TexCoord[0] = gl_MultiTexCoord0;\n"
                     "}\n"
                     "\n";
