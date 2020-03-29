#ifndef DRAWING_GL_CORE_SCENE_2D_HPP
#define DRAWING_GL_CORE_SCENE_2D_HPP
#include <list>
#include "scene.hpp"
#include "../scene_createinfo.hpp"
#include "../gl_shared/shaders_container.hpp"

namespace Drawing
{

namespace Detail
{

namespace GLCore
{

class Scene2D final : public Scene
{
public:
	Scene2D(std::shared_ptr<GLShared::ShadersContainer> sc, const SceneCreateInfo& info);
	virtual ~Scene2D() = default;
	
	// Drawing::Detail::IScene overrides
	void Insert(SMesh obj) override;
	void Erase(SMesh obj) override;
	
	// GLShared::Scene overrides
	void Draw() override;
	
	// Scene overrides
	void OnMeshTransparencyChange(Mesh& mesh) override;
	void OnMeshModelMatChange(Mesh& mesh) override;
private:
	std::shared_ptr<GLShared::ShadersContainer> sc;
	std::list<std::shared_ptr<Mesh>> meshes;
	bool scissorTest;
};

} // namespace GLCore

} // namespace Detail

} // namespace Drawing

#endif // DRAWING_GL_CORE_SCENE_2D_HPP
