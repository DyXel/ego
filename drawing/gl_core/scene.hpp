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
	
	// Drawing::Detail::IScene overrides
	void SetViewport(const glm::vec4& rect) override;
	void SetNext(SScene scene) override;
	void SetViewProjectionMat4(const glm::mat4& mat) override;
	
	virtual void Draw() = 0;
	virtual void OnMeshTransparencyChange(Mesh& mesh) = 0;
	virtual void OnMeshModelMatChange(Mesh& mesh) = 0;
protected:
	void ApplyViewport() const;
	const glm::mat4& ViewProjection() const;
	void CalculateMVP(Mesh& mesh) const;
	bool WasViewProjectionSet() const;
	bool WasViewProjectionSet(bool ignored); // Resets the flag
private:
	GLShared::Rect viewport;
	std::shared_ptr<Scene> next;
	glm::mat4 viewProj;
	bool viewProjChanged;
};

} // namespace GLCore

} // namespace Detail

} // namespace Drawing

#endif // DRAWING_GL_CORE_SCENE_HPP
