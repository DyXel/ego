#ifndef EGO_GL_SHARED_RENDERER_HPP
#define EGO_GL_SHARED_RENDERER_HPP
#include <array>
#include <ego/renderer.hpp>

#include "cache.hpp"
#include "program_provider.hpp"

namespace Ego::GLShared
{

class Scene;
class VertBuf;
class IndBuf;
class UVBuf;

class Renderer : public IRenderer, public IProgramProvider
{
public:
	Renderer();
	
	virtual void BlitToWindowFramebuffer(const Scene& scene) = 0;
	
	// IRenderer overrides
	MeshTopology QuadTopology() const override;
	SCVertBuf QuadVertBuf() const override;
	SCIndBuf QuadIndBuf() const override;
	SCUVBuf QuadUVBuf() const override;
	
	SVertBuf NewVertBuf(BufferHint hint) override;
	SIndBuf NewIndBuf(BufferHint hint) override;
	SColBuf NewColBuf(BufferHint hint) override;
	SUVBuf NewUVBuf(BufferHint hint) override;
	STexture NewTexture(const TextureCreateInfo& info) override;
	
	void SetInitialScene(SScene scene) override;
	void DrawAllScenes() override;
	
	// GLShared::IProgramProvider overrides
	const Program& GetProgram(ProgramTypes value) const override;
protected:
	Cache cache;
	std::array<Program, PROGRAM_TYPES_COUNT> programs;
	struct
	{
		std::shared_ptr<VertBuf> vb;
		std::shared_ptr<IndBuf> ib;
		std::shared_ptr<UVBuf> ub;
	}quad;
	
	std::shared_ptr<Scene> initialScene;
};

} // namespace Ego::GLShared

#endif // EGO_GL_SHARED_RENDERER_HPP
