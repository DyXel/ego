#ifndef DRAWING_GL_CORE_SCENE_2D_HPP
#define DRAWING_GL_CORE_SCENE_2D_HPP
#include <list>
#include "../scene_createinfo.hpp"
#include "../gl_shared/scene.hpp"

namespace Drawing
{

namespace Detail
{

namespace GLShared
{

class ShadersContainer;

} // namespace GLShared

namespace GLCore
{

class Mesh;

class Scene2D final : public GLShared::Scene
{
public:
	Scene2D(std::shared_ptr<GLShared::ShadersContainer> sc, const SceneCreateInfo& info);
	virtual ~Scene2D() = default;
	
	// Drawing::Detail::IScene overrides
	void Insert(SMesh obj) override;
	void Erase(SMesh obj) override;
	
	// GLShared::Scene overrides
	void Draw() override;
	void OnMeshTransparencyChange(GLShared::Mesh& mesh) override;
	void OnMeshModelMatChange(GLShared::Mesh& mesh) override;
private:
	GLShared::ShadersContainer& sc;
	std::list<std::shared_ptr<Mesh>> meshes;
};

} // namespace GLCore

} // namespace Detail

} // namespace Drawing

#endif // DRAWING_GL_CORE_SCENE_2D_HPP
