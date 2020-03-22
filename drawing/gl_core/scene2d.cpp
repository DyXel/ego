#include "scene2d.hpp"

#include <glm/gtc/type_ptr.hpp>
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
	next = std::dynamic_pointer_cast<Scene>(info.next);
}

void Scene2D::Insert(SMesh obj)
{
	auto mesh = std::dynamic_pointer_cast<Mesh>(obj);
	meshes.remove(mesh);
	meshes.push_back(mesh);
	mesh->scene = this;
	if(!vpMatChanged)
		CalculateMVP(*mesh);
}

void Scene2D::Erase(SMesh obj)
{
	auto mesh = std::dynamic_pointer_cast<Mesh>(obj);
	meshes.remove(mesh);
	mesh->scene = nullptr;
}

void Scene2D::SetViewProjectionMat4(const glm::mat4& mat)
{
	viewProj = mat;
	vpMatChanged = true;
}

void Scene2D::Draw()
{
	glViewport(viewport.x, viewport.y, viewport.w, viewport.h);
	if(vpMatChanged)
	{
		for(auto& mesh : meshes)
			CalculateMVP(*mesh);
		vpMatChanged = false;
	}
	for(auto& mesh : meshes)
	{
		if(!mesh->render || !mesh->vertBuf || !mesh->indBuf)
			continue;
		if(!mesh->diffuse)
		{
			glUseProgram(sc->sp1.spo);
		}
		else
		{
			glUseProgram(sc->sp2.spo);
			glBindTexture(GL_TEXTURE_2D, mesh->diffuse->to);
		}
		if(mesh->hasScissor)
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

void Scene2D::OnMeshTransparencyChange([[maybe_unused]] Mesh& mesh)
{}

void Scene2D::OnMeshModelMatChange(Mesh& mesh)
{
	if(vpMatChanged)
		return;
	CalculateMVP(mesh);
}

void Scene2D::CalculateMVP(Mesh& mesh)
{
	mesh.mvp = viewProj * mesh.model;
}

} // namespace GLCore

} // namespace Detail

} // namespace Drawing
