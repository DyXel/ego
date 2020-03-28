#include "scene3d.hpp"

#include <algorithm>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/norm.hpp> // glm::distance2

#include "mesh.hpp"
#include "../gl_shared/gl_include.hpp"
#include "../gl_shared/program.hpp"

namespace Drawing
{

namespace Detail
{

namespace GLCore
{

// basically C++20's std::multimap::erase_if
template<typename Container, typename Pred>
void EraseIf(Container& c, Pred pred)
{
	for (auto it = c.begin(), last = c.end(); it != last; )
	{
		if (pred(*it))
			it = c.erase(it);
		else
			++it;
	}
}

Scene3D::Scene3D(std::shared_ptr<GLShared::ShadersContainer> sc, const SceneCreateInfo& info) :
	sc(sc),
	scissorTest(false)
{
	SetViewProjectionMat4(info.viewProj);
	SetViewport(info.viewport);
	SetNext(info.next);
}

void Scene3D::Insert(SMesh obj)
{
	auto mesh = std::dynamic_pointer_cast<Mesh>(obj);
	meshes.insert(mesh);
	if(mesh->transparent)
	{
		if(WasViewProjectionSet())
		{
			alphaMeshes.emplace(0.0f, mesh.get());
		}
		else
		{
			auto dist = DistanceToVP(*mesh);
			alphaMeshes.emplace(dist, mesh.get());
		}
	}
	else
	{
		solidMeshes.insert(mesh.get());
	}
}

void Scene3D::Erase(SMesh obj)
{
	auto mesh = std::dynamic_pointer_cast<Mesh>(obj);
	meshes.erase(mesh);
	if(mesh->transparent)
	{
		EraseIf(alphaMeshes,
		[val = mesh.get()](const decltype(alphaMeshes)::value_type& kv)
		{
			return kv.second == val;
		});
	}
	else
	{
		solidMeshes.erase(mesh.get());
	}
}

void Scene3D::Draw()
{
	if(WasViewProjectionSet(true))
	{
		for(auto& mesh : solidMeshes)
			CalculateMVP(*mesh);
		// Recalculate all distances to camera
		{
			decltype(alphaMeshes) tmpMap;
			for(const auto& kv : alphaMeshes)
			{
				const float newKey = DistanceToVP(*kv.second);
				CalculateMVP(*kv.second);
				tmpMap.emplace(newKey, kv.second);
			}
			alphaMeshes = std::move(tmpMap);
		}
	}
	ApplyViewport();
	// Draw solid elements
	
}

void Scene3D::OnMeshTransparencyChange(Mesh& mesh)
{
	solidMeshes.erase(&mesh);
	EraseIf(alphaMeshes,
	[val = &mesh](const decltype(alphaMeshes)::value_type& kv)
	{
		return kv.second == val;
	});
	if(mesh.transparent)
	{
		if(WasViewProjectionSet())
		{
			alphaMeshes.emplace(0.0f, &mesh);
		}
		else
		{
			auto dist = DistanceToVP(mesh);
			alphaMeshes.emplace(dist, &mesh);
		}
	}
	else
	{
		solidMeshes.insert(&mesh);
	}
}

void Scene3D::OnMeshModelMatChange(Mesh& mesh)
{
	if(WasViewProjectionSet())
		return;
	CalculateMVP(mesh);
	if(!mesh.transparent)
		return;
	auto it = std::find_if(alphaMeshes.begin(), alphaMeshes.end(),
	[val = &mesh](const decltype(alphaMeshes)::value_type& kv)
	{
		return kv.second == val;
	});
	auto node = alphaMeshes.extract(it);
	node.key() = DistanceToVP(mesh);
	alphaMeshes.insert(std::move(node));
}

float Scene3D::DistanceToVP(const Mesh& mesh) const
{
	// DT == Decompose Translation.
	auto DT = [](const glm::mat4& mat) -> glm::vec3
	{
		return glm::vec3(mat[3]); // taken from glm::decompose
	};
	return glm::distance2(DT(ViewProjection()), DT(mesh.model));
}

} // namespace GLCore

} // namespace Detail

} // namespace Drawing
