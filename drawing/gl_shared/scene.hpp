#ifndef DRAWING_GL_SHARED_SCENE_HPP
#define DRAWING_GL_SHARED_SCENE_HPP
#include <memory>

#include "common.hpp"
#include "../scene.hpp"

namespace Drawing
{

namespace Detail
{

namespace GLShared
{

class Mesh;

class Scene : public IScene
{
public:
	virtual ~Scene() = default;
	
	virtual void Draw() = 0;
	
	// Drawing::Detail::IScene overrides
	void SetViewport(const glm::vec4& rect) override;
	void SetNext(SScene scene) override;
	void SetViewProjectionMat4(const glm::mat4& mat) override;
	
	Scene* GetNext() const;
protected:
	void ApplyViewport() const;
	const glm::mat4& ViewProjection() const;
	bool WasViewProjectionSet() const;
	bool WasViewProjectionSet(bool ignored); // Resets the flag
private:
	GLShared::Rect viewport;
	std::shared_ptr<Scene> next;
	glm::mat4 viewProj;
	bool viewProjChanged;
};

} // namespace GLShared

} // namespace Detail

} // namespace Drawing

#endif // DRAWING_GL_SHARED_SCENE_HPP
