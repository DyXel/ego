#ifndef DRAWING_GL_SHARED_SCENE_HPP
#define DRAWING_GL_SHARED_SCENE_HPP
#include <memory>

#include "common.hpp"
#include "program_provider.hpp"
#include "../scene_createinfo.hpp"
#include "../scene.hpp"

namespace Drawing
{

namespace GLShared
{

class Mesh;

class Scene : public IScene
{
public:
	Scene(IProgramProvider& pp, const SceneCreateInfo& info);
	virtual ~Scene();
	
	Scene* Next() const;
	GLuint FramebufferObject() const;
	GLuint TextureObject() const;
	const GLShared::Rect& Viewport() const;
	
	virtual void Draw();
	
	// IScene overrides
	void SetViewport(const glm::vec4& rect) override;
	void SetNext(SScene scene) override;
	void SetViewProjectionMat4(const glm::mat4& mat) override;
protected:
	const glm::mat4& ViewProjection() const;
	void CalculateMVP(Mesh& mesh) const;
	bool WasViewProjectionSet() const;
	bool WasViewProjectionSet(bool ignored); // Resets the flag
	void UseMeshProgram(const Mesh& mesh);
	void UseMeshScissor(const Mesh& mesh);
private:
	IProgramProvider& pp;
	GLbitfield clearBits;
	bool backfaceCull;
	bool depthTest;
	glm::vec4 clearColor;
	GLuint fbo; // Framebuffer object
	GLuint to; // Texture object
	GLuint rbo; // Renderbuffer object
	GLShared::Rect vp;
	std::shared_ptr<Scene> next;
	glm::mat4 viewProj;
	bool viewProjChanged;
};

} // namespace GLShared

} // namespace Drawing

#endif // DRAWING_GL_SHARED_SCENE_HPP
