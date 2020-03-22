#ifndef DRAWING_GL_CORE_SCENE_HPP
#define DRAWING_GL_CORE_SCENE_HPP
#include <memory>

#include "../scene.hpp"
#include "../gl_shared/common.hpp"

namespace Drawing
{

namespace Detail
{

namespace GLCore
{

class Mesh;

class Scene : public IScene
{
public:
	virtual ~Scene() = default;
	
	Scene* GetNext() const;
	
	void SetViewport(const glm::vec4& rect) override;
	void SetNext(SScene scene) override;
	
	virtual void Draw() = 0;
	virtual void OnMeshTransparencyChange(Mesh& mesh) = 0;
	virtual void OnMeshModelMatChange(Mesh& mesh) = 0;
protected:
	std::shared_ptr<Scene> next;
	GLShared::Rect viewport;
};

} // namespace GLCore

} // namespace Detail

} // namespace Drawing

#endif // DRAWING_GL_CORE_SCENE_HPP
