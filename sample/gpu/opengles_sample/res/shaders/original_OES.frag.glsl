#extension GL_OES_EGL_image_external : require
precision highp float;
varying vec2 vTextureCoord;
uniform samplerExternalOES uTextureSampler;

void main()
{
        vec4 color = texture2D(uTextureSampler, vTextureCoord);
        gl_FragColor = vec4(color.r, color.g, color.b, 1.0);
}

