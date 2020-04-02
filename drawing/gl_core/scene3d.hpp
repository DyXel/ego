#ifndef DRAWING_GL_CORE_SCENE_3D_HPP
#define DRAWING_GL_CORE_SCENE_3D_HPP
#include <set>
#include <map>

#include "../scene_createinfo.hpp"
#include "../gl_shared/scene.hpp"
#include "../gl_shared/mesh_listener.hpp"
#include "../gl_shared/program_provider.hpp"

namespace Ego
{

namespace GLCore
{

class Mesh;

class Scene3D final : public GLShared::Scene, public GLShared::IMeshListener
{
public:
	Scene3D(GLShared::Cache& cache, GLShared::IProgramProvider& pp, const SceneCreateInfo& info);
	virtual ~Scene3D() = default;
	
	// IScene overrides
	void Insert(SMesh obj) override;
	void Erase(SMesh obj) override;
	
	// GLShared::Scene overrides
	void Draw() override;
	
	// GLShared::IMeshListener overrides
	void OnMeshTransparencyChange(GLShared::Mesh& mesh) override;
	void OnMeshModelMatChange(GLShared::Mesh& mesh) override;
private:
	std::set<std::shared_ptr<Mesh>> meshes;
	std::set<Mesh*> solidMeshes;
	std::multimap<float, Mesh*, std::greater<>> alphaMeshes;
	
	float DistanceToVP(const Mesh& mesh) const;
};

} // namespace GLCore

} // namespace Ego

#endif // DRAWING_GL_CORE_SCENE_3D_HPP
