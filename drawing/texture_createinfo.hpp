#ifndef DRAWING_TEXTURE_CREATEINFO_HPP
#define DRAWING_TEXTURE_CREATEINFO_HPP
#include "enums.hpp"

namespace Ego
{

struct TextureCreateInfo
{
	TextureFiltering filtering;
	TextureWrap hWrap;
	TextureWrap vWrap;
	int width;
	int height;
	const void* pixels;
// 	uint8_t mipCount;
};

} // namespace Ego

#endif // DRAWING_TEXTURE_CREATEINFO_HPP
