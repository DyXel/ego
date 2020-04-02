#ifndef EGO_TEXTURE_HPP
#define EGO_TEXTURE_HPP
#include "texture_createinfo.hpp"

namespace Ego
{

class ITexture
{
public:
	virtual void SetImage(int width, int height, const void* data) = 0;
};

} // Drawing

#endif // EGO_TEXTURE_HPP
