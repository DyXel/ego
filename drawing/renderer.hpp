#ifndef DRAWING_RENDERER_HPP
#define DRAWING_RENDERER_HPP
#include "enums.hpp"
#include "scene_fwd.hpp"
#include "scene_createinfo.hpp"
#include "mesh_fwd.hpp"
#include "mesh_createinfo.hpp"
#include "texture_fwd.hpp"
#include "texture_createinfo.hpp"
#include "vertbuf_fwd.hpp"
#include "colbuf_fwd.hpp"
#include "indbuf_fwd.hpp"
#include "uvbuf_fwd.hpp"

namespace Drawing
{

namespace Detail
{

class IRenderer
{
public:
	virtual ~IRenderer() = default;
	
	virtual bool SetVSync(VSyncState vsync) = 0;
	
	virtual Scene NewScene2D(const SceneCreateInfo& info) = 0;
	virtual Scene NewScene3D(const SceneCreateInfo& info) = 0;
	virtual Mesh NewMesh(const MeshCreateInfo& info) = 0;
	virtual Texture NewTexture(const TextureCreateInfo& info) = 0;
	
	virtual VertBuf NewVertBuf(BufferHint hint) = 0;
	virtual IndBuf NewIndBuf(BufferHint hint) = 0;
	virtual ColBuf NewColBuf(BufferHint hint) = 0;
	virtual UVBuf NewUVBuf(BufferHint hint) = 0;
	
	virtual void SetInitialScene(Scene scene) = 0;
	virtual Scene GetInitialScene() = 0;
	
	virtual void DrawAllScenes() = 0;
};

} // namespace Detail

} // namespace Drawing

#endif // DRAWING_RENDERER_HPP
