#ifndef EGO_RENDERER_HPP
#define EGO_RENDERER_HPP
#include "ego_fwd.hpp"
#include "enums.hpp"
#include "scene_createinfo.hpp"
#include "mesh_createinfo.hpp"
#include "texture_createinfo.hpp"

namespace Ego
{

class IRenderer
{
public:
	virtual ~IRenderer() = default;
	
	virtual bool SetVSync(VSyncState vsync) = 0;
	
	virtual MeshTopology QuadTopology() const = 0;
	virtual SCVertBuf QuadVertBuf() const = 0;
	virtual SCIndBuf QuadIndBuf() const = 0;
	virtual SCUVBuf QuadUVBuf() const = 0;
	
	virtual SScene NewScene2D(const SceneCreateInfo& info) = 0;
	virtual SScene NewScene3D(const SceneCreateInfo& info) = 0;
	virtual SMesh NewMesh(const MeshCreateInfo& info) = 0;
	virtual STexture NewTexture(const TextureCreateInfo& info) = 0;
	virtual SVertBuf NewVertBuf(BufferHint hint) = 0;
	virtual SIndBuf NewIndBuf(BufferHint hint) = 0;
	virtual SColBuf NewColBuf(BufferHint hint) = 0;
	virtual SUVBuf NewUVBuf(BufferHint hint) = 0;
	
	virtual void SetInitialScene(SScene scene) = 0;
	virtual void DrawAllScenes() = 0;
};

} // namespace Ego

#endif // EGO_RENDERER_HPP
