#include "scene2d.hpp"

#include <glm/gtc/type_ptr.hpp>

#include "mesh.hpp"
#include "../gl_shared/gl_include.hpp"
#include "../gl_shared/program.hpp"

namespace Drawing
{

namespace Detail
{

namespace GLCore
{

Scene2D::Scene2D(std::shared_ptr<GLShared::ShadersContainer> sc, const SceneCreateInfo& info) :
	sc(sc),
	scissorTest(false)
{
	SetViewProjectionMat4(info.viewProj);
	SetViewport(info.viewport);
	SetNext(info.next);
}

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
		if(!mesh->render || !mesh->vertBuf || !mesh->indBuf) // ShouldDrawMesh
			continue;
		if(!mesh->diffuse) // ChangeProgramBasedOnMesh
		{
			glUseProgram(sc->sp1.spo);
		}
		else
		{
			glUseProgram(sc->sp2.spo);
			glBindTexture(GL_TEXTURE_2D, mesh->diffuse->to);
		}
		if(mesh->hasScissor) // ApplyScissor
		{
			if(!scissorTest)
			{
				scissorTest = true;
				glEnable(GL_SCISSOR_TEST);
			}
			glScissor(mesh->sci.x, mesh->sci.y, mesh->sci.w, mesh->sci.h);
		}
		else
		{
			if(scissorTest)
			{
				scissorTest = false;
				glDisable(GL_SCISSOR_TEST);
			}
		}
		
		glUniformMatrix4fv(sc->sp1.GetUniformLocation(GLShared::UNIFORM_MVP_MAT),
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
