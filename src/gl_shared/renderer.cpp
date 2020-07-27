#include "renderer.hpp"

#include "colbuf.hpp"
#include "gl_include.hpp"
#include "indbuf.hpp"
#include "scene.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "uvbuf.hpp"
#include "vertbuf.hpp"

namespace Ego::GLShared
{

constexpr std::array<const GLchar*, PROGRAM_TYPES_COUNT> VERTEX_SHADER_SRC =
{
// PROGRAM_ONLY_COLOR
R"(#version 100
attribute vec3 in_pos;
attribute vec4 in_color;
varying vec4 out_color;
uniform mat4 in_mvp;
void main()
{
	gl_Position = in_mvp * vec4(in_pos, 1.0);
	out_color = in_color;
})",
// PROGRAM_TEXTURE_PLUS_COLOR
R"(#version 100
attribute vec3 in_pos;
attribute vec4 in_color;
attribute vec2 in_uv;
varying vec4 out_color;
varying vec2 out_uv;
uniform mat4 in_mvp;
void main()
{
	gl_Position = in_mvp * vec4(in_pos, 1.0);
	// color buffer shouldn't contribute to alpha
	out_color = vec4(in_color.xyz, 0.0);
	out_uv = in_uv;
})",
};

constexpr std::array<const GLchar*, PROGRAM_TYPES_COUNT> FRAGMENT_SHADER_SRC =
{
// PROGRAM_ONLY_COLOR
R"(#version 100
precision mediump float;
varying vec4 out_color; // input from vertex shader
void main()
{
	gl_FragColor = out_color;
})",
// PROGRAM_TEXTURE_PLUS_COLOR
R"(#version 100
precision mediump float;
varying vec4 out_color; // input from vertex shader
varying vec2 out_uv; // input from vertex shader
uniform sampler2D in_tex;
void main()
{
	gl_FragColor = texture2D(in_tex, out_uv) + out_color;
})",
};

// Quad data
constexpr std::size_t QUAD_VERTEX_COUNT = 4;
constexpr std::array<glm::vec3, QUAD_VERTEX_COUNT> QUAD_VERTICES =
{ {
	{-1.0F, -1.0F, 0.0F}, // top-left corner
	{-1.0F,  1.0F, 0.0F}, // bottom-left corner
	{ 1.0F, -1.0F, 0.0F}, // top-right corner
	{ 1.0F,  1.0F, 0.0F}, // bottom-right corner
} };
constexpr std::array<short, QUAD_VERTEX_COUNT> QUAD_INDICES =
{
	0, 1, 2, 3
};
constexpr std::array<glm::vec2, QUAD_VERTEX_COUNT> QUAD_UVS =
{ {
	{0.0F, 0.0F},
	{0.0F, 1.0F},
	{1.0F, 0.0F},
	{1.0F, 1.0F},
} };

Renderer::Renderer() : initialScene(nullptr)
{
	// Enable additive blending
	cache.SetBlending(true);
	cache.SetBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Initialize internal shaders
	for(std::size_t i = 0; i < PROGRAM_TYPES_COUNT; i++)
	{
		GLShared::Shader vs(GL_VERTEX_SHADER, VERTEX_SHADER_SRC[i]);
		GLShared::Shader fs(GL_FRAGMENT_SHADER, FRAGMENT_SHADER_SRC[i]);
		programs[i].Attach(vs);
		programs[i].Attach(fs);
		programs[i].Link();
	}
	
	// Initialize quad vertex, indice and uv buffer
	quad.vb = std::make_shared<VertBuf>(BUFFER_HINT_STATIC);
	quad.vb->Submit(QUAD_VERTICES.data(), QUAD_VERTEX_COUNT);
	quad.ib = std::make_shared<IndBuf>(BUFFER_HINT_STATIC);
	quad.ib->Submit(QUAD_INDICES.data(), QUAD_VERTEX_COUNT);
	quad.ub = std::make_shared<UVBuf>(BUFFER_HINT_STATIC);
	quad.ub->Submit(QUAD_UVS.data(), QUAD_VERTEX_COUNT);
}

MeshTopology Renderer::QuadTopology() const
{
	return MESH_TOPOLOGY_TRIANGLE_STRIP;
}

SCVertBuf Renderer::QuadVertBuf() const
{
	return quad.vb;
}

SCIndBuf Renderer::QuadIndBuf() const
{
	return quad.ib;
}

SCUVBuf Renderer::QuadUVBuf() const
{
	return quad.ub;
}

SVertBuf Renderer::NewVertBuf(BufferHint hint)
{
	return std::make_shared<VertBuf>(hint);
}

SIndBuf Renderer::NewIndBuf(BufferHint hint)
{
	return std::make_shared<IndBuf>(hint);
}

SColBuf Renderer::NewColBuf(BufferHint hint)
{
	return std::make_shared<ColBuf>(hint);
}

SUVBuf Renderer::NewUVBuf(BufferHint hint)
{
	return std::make_shared<UVBuf>(hint);
}

STexture Renderer::NewTexture(const TextureCreateInfo& info)
{
	return std::make_shared<Texture>(info);
}

void Renderer::SetInitialScene(SScene scene)
{
	initialScene = std::dynamic_pointer_cast<Scene>(scene);
}

void Renderer::DrawAllScenes()
{
	for(Scene* s = initialScene.get(); s != nullptr; s = s->Next())
	{
		s->Draw();
		BlitToWindowFramebuffer(*s);
	}
}

const Program& Renderer::GetProgram(ProgramTypes value) const
{
	return programs[value];
}

} // namespace Ego::GLShared
