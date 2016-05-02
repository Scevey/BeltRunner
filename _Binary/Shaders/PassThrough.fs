#version 330

in vec3 Position_W;
in vec2 UV;

uniform sampler2D TextureID;

out vec4 Fragment;

void main()
{
	Fragment = texture( TextureID, UV );

	return;
}