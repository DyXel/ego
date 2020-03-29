#ifndef DRAWING_GL_CORE_SCENE_3D_HPP
#define DRAWING_GL_CORE_SCENE_3D_HPP
#include <set>
#include <map>

#include "../scene_createinfo.hpp"
#include "../gl_shared/scene.hpp"
#include "../gl_shared/program_provider.hpp"

namespace Drawing
{

namespace Detail
{

namespace GLCore
{

class Mesh;

class Scene3D final : public GLShared::Scene
{
public:
	Scene3D(GLShared::IProgramProvider& pp, const SceneCreateInfo& info);
	virtual ~Scene3D() = default;
	
	// Drawing::Detail::IScene overrides
	void Insert(SMesh obj) override;
	void Erase(SMesh obj) override;
	
	// GLShared::Scene overrides
	void Draw() override;
	void OnMeshTransparencyChange(GLShared::Mesh& mesh) override;
	void OnMeshModelMatChange(GLShared::Mesh& mesh) override;
private:
	GLShared::IProgramProvider& pp;
	std::set<std::shared_ptr<Mesh>> meshes;
	std::set<Mesh*> solidMeshes;
	std::multimap<float, Mesh*> alphaMeshes;
	
	float DistanceToVP(const Mesh& mesh) const;
};

} // namespace GLCore

} // namespace Detail

} // namespace Drawing

#endif // DRAWING_GL_CORE_SCENE_3D_HPP
