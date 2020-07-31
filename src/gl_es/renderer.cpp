#include "renderer.hpp"

#include "mesh.hpp"
#include "scene2d.hpp"
#include "scene3d.hpp"
#include "../gl_shared/shader.hpp"
#include "../gl_shared/gl_include.hpp"

namespace Ego::GLES
{

constexpr const GLchar* BLIT_VERTEX_SHADER_SRC =
R"(#version 100
attribute vec3 in_pos;
attribute vec2 in_uv;
varying vec2 out_uv;
void main()
{
	gl_Position = vec4(in_pos, 1.0);
	out_uv = in_uv;
})";

constexpr const GLchar* BLIT_FRAGMENT_SHADER_SRC =
R"(#version 100
precision mediump float;
varying vec2 out_uv; // input from vertex shader
uniform sampler2D in_tex;
void main()
{
	gl_FragColor = texture2D(in_tex, out_uv);
})";

Renderer::Renderer() :
	GLShared::Renderer()
{
	GLShared::Shader vs(GL_VERTEX_SHADER, BLIT_VERTEX_SHADER_SRC);
	GLShared::Shader fs(GL_FRAGMENT_SHADER, BLIT_FRAGMENT_SHADER_SRC);
	prog.Attach(vs);
	prog.Attach(fs);
	prog.Link();
	
	// Vertex attribute is guaranteed to be enabled when calling any draw
	// function.
	glEnableVertexAttribArray(GLShared::ATTRIBUTE_VERTICES);
}

SScene Renderer::NewScene2D(const SceneCreateInfo& info)
{
	return std::make_shared<Scene2D>(cache, *this, info);
}

SScene Renderer::NewScene3D(const SceneCreateInfo& info)
{
	return std::make_shared<Scene3D>(cache, *this, info);
}

SMesh Renderer::NewMesh(const MeshCreateInfo& info)
{
	return std::make_shared<Mesh>(info);
}

void Renderer::BlitToWindowFramebuffer(const GLShared::Scene& scene)
{
	cache.SetDepthTest(false);
	cache.SetCullFace(false);
	cache.SetScissorTest(false);
	cache.UseProgram(prog.spo);
	glDisableVertexAttribArray(GLShared::ATTRIBUTE_COLORS);
	const auto& vp = scene.Viewport();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(vp.x, vp.y, vp.z, vp.w);
	glBindTexture(GL_TEXTURE_2D, scene.TextureObject());
	glBindBuffer(GL_ARRAY_BUFFER, quad.vb->bo);
	glVertexAttribPointer(GLShared::ATTRIBUTE_VERTICES, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, quad.ub->bo);
	glVertexAttribPointer(GLShared::ATTRIBUTE_UVS, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(GLShared::ATTRIBUTE_UVS);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quad.ib->bo);
	glDrawElements(GL_TRIANGLE_STRIP, quad.ib->count, GL_UNSIGNED_SHORT, nullptr);
}

} // namespace Ego::GLES
