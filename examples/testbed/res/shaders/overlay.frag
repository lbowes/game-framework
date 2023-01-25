#version 330 core

out vec4 colour;

in vec2 texCoord;

uniform sampler2D overlayTexture;

void main(){
	vec4 texColour = texture(overlayTexture, texCoord);
    if(texColour.a < 0.5)
        discard;
    
	colour = vec4(texColour.rgb, 0.5f);
}