#include "texture.hpp"

#include "common.hpp"
#include "gl_include.hpp"

namespace Drawing
{

namespace GLShared
{

Texture::Texture(const TextureCreateInfo& info)
{
	glGenTextures(1, &to);
	const auto glFiltering = GLTextureFilteringFromEnum(info.filtering);
	const auto glhWrap = GLTextureWrapFromEnum(info.hWrap);
	const auto glvWrap = GLTextureWrapFromEnum(info.vWrap);
	
	glBindTexture(GL_TEXTURE_2D, to);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, glFiltering);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, glFiltering);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, glhWrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, glvWrap);
	
	if(info.width != 0 && info.height != 0 && info.pixels != nullptr)
		SetImage(info.width, info.height, info.pixels);
}

Texture::~Texture()
{
	glDeleteTextures(1, &to);
}

void Texture::SetImage(int width, int height, const void* pixels)
{
	static const GLint MIPS_COUNT = 0;
	glBindTexture(GL_TEXTURE_2D, to);
	glTexImage2D(GL_TEXTURE_2D, MIPS_COUNT, GL_RGBA, width, height, 0, GL_RGBA,
	             GL_UNSIGNED_BYTE, pixels);
}

} // namespace GLShared

} // namespace Drawing
