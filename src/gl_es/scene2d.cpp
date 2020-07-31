#include "scene2d.hpp"

#include <glm/gtc/type_ptr.hpp>

#include "mesh.hpp"
#include "../gl_shared/gl_include.hpp"

namespace Ego::GLES
{

Scene2D::Scene2D(GLShared::Cache& cache, GLShared::IProgramProvider& pp, const SceneCreateInfo& info) :
	GLShared::Scene(cache, pp, info)
{}

void Scene2D::Insert(SMesh obj)
{
	auto mesh = std::dynamic_pointer_cast<Mesh>(obj);
	meshes.remove(mesh);
	meshes.push_back(mesh);
	mesh->listener = this;
	if(!WasViewProjectionSet())
		CalculateMVP(*mesh);
}

void Scene2D::Erase(SMesh obj)
{
	auto mesh = std::dynamic_pointer_cast<Mesh>(obj);
	meshes.remove(mesh);
	mesh->listener = nullptr;
}

void Scene2D::Draw()
{
	GLShared::Scene::Draw();
	if(WasViewProjectionSet(true))
	{
		for(auto& mesh : meshes)
			CalculateMVP(*mesh);
	}
	for(auto& meshPtr : meshes)
	{
		auto& mesh = *meshPtr;
		if(!mesh.render || !mesh.vertBuf || !mesh.indBuf)
			continue;
		UseMeshProgram(mesh);
		UseMeshScissor(mesh);
		auto& p = pp.GetProgram(GLShared::PROGRAM_ONLY_COLOR);
		glUniformMatrix4fv(p.GetUniformLocation(GLShared::UNIFORM_MVP_MAT),
		                   1, GL_FALSE, glm::value_ptr(mesh.mvp));
		glBindBuffer(GL_ARRAY_BUFFER, mesh.vertBuf->bo);
		glVertexAttribPointer(GLShared::ATTRIBUTE_VERTICES, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
		if(mesh.colBuf)
		{
			glBindBuffer(GL_ARRAY_BUFFER, mesh.colBuf->bo);
			glVertexAttribPointer(GLShared::ATTRIBUTE_COLORS, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
			glEnableVertexAttribArray(GLShared::ATTRIBUTE_COLORS);
		}
		else
		{
			glDisableVertexAttribArray(GLShared::ATTRIBUTE_COLORS);
		}
		if(mesh.uvBuf)
		{
			glBindBuffer(GL_ARRAY_BUFFER, mesh.uvBuf->bo);
			glVertexAttribPointer(GLShared::ATTRIBUTE_UVS, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
			glEnableVertexAttribArray(GLShared::ATTRIBUTE_UVS);
		}
		else
		{
			glDisableVertexAttribArray(GLShared::ATTRIBUTE_UVS);
		}
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.indBuf->bo);
		glDrawElements(mesh.topology, mesh.indBuf->count, GL_UNSIGNED_SHORT, nullptr);
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

} // namespace Ego::GLES
