#ifndef EGO_GLSHARED_MESH_LISTENER_HPP
#define EGO_GLSHARED_MESH_LISTENER_HPP

namespace Ego::GLShared
{

class Mesh;

class IMeshListener
{
public:
	virtual void OnMeshTransparencyChange(Mesh& mesh) = 0;
	virtual void OnMeshModelMatChange(Mesh& mesh) = 0;
};

} // namespace Ego::GLShared

#endif // EGO_GLSHARED_MESH_LISTENER_HPP
