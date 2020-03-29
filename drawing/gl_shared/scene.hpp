#ifndef DRAWING_GL_SHARED_SCENE_HPP
#define DRAWING_GL_SHARED_SCENE_HPP
#include <memory>

#include "common.hpp"
#include "../scene_createinfo.hpp"
#include "../scene.hpp"

namespace Drawing
{

namespace Detail
{

namespace GLShared
{

class Mesh;
class ShadersContainer;

class Scene : public IScene
{
public:
	Scene(std::shared_ptr<ShadersContainer> sc, const SceneCreateInfo& info);
	virtual ~Scene() = default;
	
	virtual void Draw() = 0;
	virtual void OnMeshTransparencyChange(Mesh& mesh) = 0;
	virtual void OnMeshModelMatChange(Mesh& mesh) = 0;
	
	// Drawing::Detail::IScene overrides
	void SetViewport(const glm::vec4& rect) override;
	void SetNext(SScene scene) override;
	void SetViewProjectionMat4(const glm::mat4& mat) override;
	
	Scene* GetNext() const;
protected:
	void ApplyViewport() const;
	const glm::mat4& ViewProjection() const;
	void CalculateMVP(Mesh& mesh) const;
	bool WasViewProjectionSet() const;
	bool WasViewProjectionSet(bool ignored); // Resets the flag
	void UseMeshProgram(const Mesh& mesh);
	void UseMeshScissor(const Mesh& mesh);
private:
	std::shared_ptr<ShadersContainer> sc;
	GLShared::Rect viewport;
	std::shared_ptr<Scene> next;
	glm::mat4 viewProj;
	bool viewProjChanged;
	
	struct
	{
		GLuint lastProgram{0};
		bool usingScissor{false};
	}cache;
};

} // namespace GLShared

} // namespace Detail

} // namespace Drawing

#endif // DRAWING_GL_SHARED_SCENE_HPP
