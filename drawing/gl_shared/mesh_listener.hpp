#ifndef EGO_GLSHARED_MESH_LISTENER_HPP
#define EGO_GLSHARED_MESH_LISTENER_HPP

namespace Ego
{

namespace GLShared
{

class Mesh;

class IMeshListener
{
public:
	virtual void OnMeshTransparencyChange(Mesh& mesh) = 0;
	virtual void OnMeshModelMatChange(Mesh& mesh) = 0;
};

} // GLShared

} // Drawing

#endif // EGO_GLSHARED_MESH_LISTENER_HPP
