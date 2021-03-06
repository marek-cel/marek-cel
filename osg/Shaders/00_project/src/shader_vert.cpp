char shader_vert[] = "attribute vec3 tangent;\n"
                     "attribute vec3 binormal;\n"
                     "varying vec3 lightDir;\n"
                     "\n"
                     "void main()\n"
                     "{\n"
                     "    vec3 normal = normalize( gl_NormalMatrix * gl_Normal );\n"
                     "    mat3 rotation = mat3( tangent, binormal, normal );\n"
                     "    vec4 vertexInEye = gl_ModelViewMatrix * gl_Vertex;\n"
                     "\n"
                     "    lightDir = vec3( gl_LightSource[0].position.xyz - vertexInEye.xyz );\n"
                     "    lightDir = normalize( rotation * normalize( lightDir ) );\n"
                     "    gl_Position = ftransform();\n"
                     "    gl_TexCoord[0] = gl_MultiTexCoord0;\n"
                     "}\n"
                     "\n";
