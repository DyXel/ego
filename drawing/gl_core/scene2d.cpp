#include "scene2d.hpp"

#include <glm/gtc/type_ptr.hpp>

#include "mesh.hpp"
#include "../gl_shared/gl_include.hpp"

namespace Drawing
{

namespace Detail
{

namespace GLCore
{

Scene2D::Scene2D(GLShared::IProgramProvider& pp, const SceneCreateInfo& info) :
	GLShared::Scene(pp, info),
	pp(pp)
{}

void Scene2D::Insert(SMesh obj)
{
	auto mesh = std::dynamic_pointer_cast<Mesh>(obj);
	meshes.remove(mesh);
	meshes.push_back(mesh);
	mesh->scene = this;
	if(!WasViewProjectionSet())
		CalculateMVP(*mesh);
}

void Scene2D::Erase(SMesh obj)
{
	auto mesh = std::dynamic_pointer_cast<Mesh>(obj);
	meshes.remove(mesh);
	mesh->scene = nullptr;
}

void Scene2D::Draw()
{
	if(WasViewProjectionSet(true))
	{
		for(auto& mesh : meshes)
			CalculateMVP(*mesh);
	}
	ApplyViewport();
	for(auto& mesh : meshes)
	{
		if(!mesh->render || !mesh->vertBuf || !mesh->indBuf)
			continue;
		UseMeshProgram(*mesh);
		UseMeshScissor(*mesh);
		// NOTE: since all shaders have the same uniforms, it doesnt matter
		// which shader we retrieve the location from.
		auto& p = pp.GetProgram(GLShared::PROGRAM_ONLY_COLOR);
		glUniformMatrix4fv(p.GetUniformLocation(GLShared::UNIFORM_MVP_MAT),
		                   1, GL_FALSE, glm::value_ptr(mesh->mvp));
		glBindVertexArray(mesh->vao);
		glDrawElements(mesh->topology, mesh->indBuf->count, GL_UNSIGNED_SHORT, nullptr);
	}
}

void Scene2D::OnMeshTransparencyChange([[maybe_unused]] GLShared::Mesh& mesh)
{}

void Scene2D::OnMeshModelMatChange(GLShared::Mesh& mesh)
{
	if(WasViewProjectionSet())
		return;
	CalculateMVP(dynamic_cast<Mesh&>(mesh));
}

} // namespace GLCore

} // namespace Detail

} // namespace Drawing
