#ifndef EGO_SCENE_HPP
#define EGO_SCENE_HPP
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>

#include "ego_fwd.hpp"

namespace Ego
{

class IScene
{
public:
	virtual ~IScene() = default;
	
	virtual void Insert(SMesh obj) = 0;
	virtual void Erase(SMesh obj) = 0;
	virtual void SetViewProjectionMat4(const glm::mat4& mat) = 0;
	virtual void SetViewport(const glm::ivec4& rect) = 0;
	virtual void SetNext(SScene next) = 0;
};

} // namespace Ego

#endif // EGO_SCENE_HPP
