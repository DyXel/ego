#ifndef EGO_TEXTURE_HPP
#define EGO_TEXTURE_HPP

namespace Ego
{

class ITexture
{
public:
	virtual void SetImage(int width, int height, const void* data) = 0;
protected:
	inline ~ITexture() = default;
};

} // Drawing

#endif // EGO_TEXTURE_HPP
