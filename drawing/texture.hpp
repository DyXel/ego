#ifndef DRAWING_TEXTURE_HPP
#define DRAWING_TEXTURE_HPP
#include "texture_createinfo.hpp"

namespace Drawing
{

namespace Detail
{

class ITexture
{
public:
	virtual void SetImage(int width, int height, const void* data) = 0;
};

} // Detail

} // Drawing

#endif // DRAWING_TEXTURE_HPP
