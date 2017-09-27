#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "TextureApplication.h"



TextureApplication::TextureApplication()
{
	_shader = new Shader();
	_plane = new Mesh();
}


TextureApplication::~TextureApplication()
{
}

void TextureApplication::startup()
{
	int texWidth, texHeight, texFormat;
	stbi_load("../texture/crate.png", &texWidth, &texHeight, &texFormat, )
}

void TextureApplication::update(float)
{
}

void TextureApplication::shutdown()
{
}

void TextureApplication::draw()
{
}
