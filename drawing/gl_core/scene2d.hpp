#ifndef DRAWING_GL_CORE_SCENE_2D_HPP
#define DRAWING_GL_CORE_SCENE_2D_HPP
#include <list>

#include "../scene_createinfo.hpp"
#include "../gl_shared/scene.hpp"
#include "../gl_shared/mesh_listener.hpp"
#include "../gl_shared/program_provider.hpp"

namespace Drawing
{

namespace GLCore
{

class Mesh;

class Scene2D final : public GLShared::Scene, public GLShared::IMeshListener
{
public:
	Scene2D(GLShared::Cache& cache, GLShared::IProgramProvider& pp, const SceneCreateInfo& info);
	virtual ~Scene2D() = default;
	
	// IScene overrides
	void Insert(SMesh obj) override;
	void Erase(SMesh obj) override;
	
	// GLShared::Scene overrides
	void Draw() override;
	
	// GLShared::IMeshListener overrides
	void OnMeshTransparencyChange(GLShared::Mesh& mesh) override;
	void OnMeshModelMatChange(GLShared::Mesh& mesh) override;
private:
	std::list<std::shared_ptr<Mesh>> meshes;
};

} // namespace GLCore

} // namespace Drawing

#endif // DRAWING_GL_CORE_SCENE_2D_HPP
