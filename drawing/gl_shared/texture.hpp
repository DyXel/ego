#ifndef DRAWING_GL_SHARED_TEXTURE_HPP
#define DRAWING_GL_SHARED_TEXTURE_HPP
#include "gl_include.hpp"
#include "../texture_createinfo.hpp"
#include "../texture.hpp"

namespace Drawing
{

namespace Detail
{

namespace GLShared
{

class Texture final : public ITexture
{
public:
	GLuint to; // Texture Object
	
	Texture(const TextureCreateInfo& info);
	virtual ~Texture();
	
	void SetImage(int width, int height, const void* pixels) override;
};

} // namespace GLShared

} // namespace Detail

} // namespace Drawing

#endif // DRAWING_GL_SHARED_TEXTURE_HPP
