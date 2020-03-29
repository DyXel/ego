#ifndef DRAWING_GL_CORE_SCENE_3D_HPP
#define DRAWING_GL_CORE_SCENE_3D_HPP
#include <set>
#include <map>

#include "scene.hpp"
#include "../scene_createinfo.hpp"
#include "../gl_shared/shaders_container.hpp"

namespace Drawing
{

namespace Detail
{

namespace GLCore
{

class Scene3D final : public Scene
{
public:
	Scene3D(std::shared_ptr<GLShared::ShadersContainer> sc, const SceneCreateInfo& info);
	virtual ~Scene3D() = default;
	
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
	std::set<std::shared_ptr<Mesh>> meshes;
	std::set<Mesh*> solidMeshes;
	std::multimap<float, Mesh*> alphaMeshes;
	bool scissorTest;
	
	float DistanceToVP(const Mesh& mesh) const;
};

} // namespace GLCore

} // namespace Detail

} // namespace Drawing

#endif // DRAWING_GL_CORE_SCENE_3D_HPP
