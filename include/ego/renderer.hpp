#ifndef EGO_RENDERER_HPP
#define EGO_RENDERER_HPP
#include <functional>

#include "ego_fwd.hpp"
#include "enums.hpp"
#include "scene_createinfo.hpp"
#include "mesh_createinfo.hpp"
#include "texture_createinfo.hpp"

namespace Ego
{

namespace Detail
{

using GLProcAddrGetter = std::function<void*(const char*)>;

} // namespace Detail

class IRenderer
{
public:
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
protected:
	inline ~IRenderer() = default;
};

SRenderer MakeGLCoreRenderer(Detail::GLProcAddrGetter glProcAddrGetter);
SRenderer MakeGLESRenderer(Detail::GLProcAddrGetter glProcAddrGetter);

} // namespace Ego

#endif // EGO_RENDERER_HPP
