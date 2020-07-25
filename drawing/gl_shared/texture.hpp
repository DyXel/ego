#ifndef EGO_GL_SHARED_TEXTURE_HPP
#define EGO_GL_SHARED_TEXTURE_HPP
#include "gl_include.hpp"
#include "../texture_createinfo.hpp"
#include "../texture.hpp"

namespace Ego::GLShared
{

class Texture final : public ITexture
{
public:
	GLuint to{}; // Texture Object
	
	Texture(const TextureCreateInfo& info);
	~Texture();
	
	void SetImage(int width, int height, const void* pixels) override;
};

} // namespace Ego::GLShared

#endif // EGO_GL_SHARED_TEXTURE_HPP
