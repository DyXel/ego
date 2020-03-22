#ifndef DRAWING_SCENE_HPP
#define DRAWING_SCENE_HPP
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include "scene_fwd.hpp"
#include "mesh_fwd.hpp"

namespace Drawing
{

namespace Detail
{

class IScene
{
public:
	virtual ~IScene() = default;
	
	virtual void Insert(Mesh obj) = 0;
	virtual void Erase(Mesh obj) = 0;
	virtual void SetViewProjectionMat4(const glm::mat4& mat) = 0;
	virtual void SetViewport(const glm::vec4& rect) = 0;
	virtual void SetNext(Scene next) = 0;
};

} // namespace Detail

} // namespace Drawing

#endif // DRAWING_SCENE_HPP
