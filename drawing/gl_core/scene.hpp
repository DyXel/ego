#ifndef DRAWING_GL_CORE_SCENE_HPP
#define DRAWING_GL_CORE_SCENE_HPP
#include <memory>

#include "../scene.hpp"
#include "../gl_shared/common.hpp"
#include "../gl_shared/scene.hpp"

namespace Drawing
{

namespace Detail
{

namespace GLCore
{

class Mesh;

class Scene : public GLShared::Scene
{
public:
	virtual ~Scene() = default;
protected:
	void CalculateMVP(Mesh& mesh) const;
};

} // namespace GLCore

} // namespace Detail

} // namespace Drawing

#endif // DRAWING_GL_CORE_SCENE_HPP
