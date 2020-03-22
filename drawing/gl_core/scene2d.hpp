#ifndef DRAWING_GL_CORE_SCENE_2D_HPP
#define DRAWING_GL_CORE_SCENE_2D_HPP
#include <list>
#include "scene.hpp"
#include "mesh.hpp"
#include "../scene_createinfo.hpp"

#include "../gl_shared/shaders_container.hpp"

namespace Drawing
{

namespace Detail
{

namespace GLShared
{

class Program;

}

namespace GLCore
{

class Scene2D final : public Scene
{
public:
	Scene2D(std::shared_ptr<GLShared::ShadersContainer> sc, const SceneCreateInfo& info);
	virtual ~Scene2D() = default;
	
	// Drawing::Detail::IScene overrides
	void Insert(Drawing::Mesh obj) override;
	void Erase(Drawing::Mesh obj) override;
	void SetViewProjectionMat4(const glm::mat4& mat) override;
	
	// Scene overrides
	void Draw() override;
	void OnMeshTransparencyChange(Mesh& mesh) override;
	void OnMeshModelMatChange(Mesh& mesh) override;
private:
	std::shared_ptr<GLShared::ShadersContainer> sc;
	std::list<std::shared_ptr<Mesh>> meshes;
	glm::mat4 viewProj;
	bool vpMatChanged;
	bool scissorTest;
	
	void CalculateMVP(Mesh& mesh);
};

} // namespace GLCore

} // namespace Detail

} // namespace Drawing

#endif // DRAWING_GL_CORE_SCENE_2D_HPP
