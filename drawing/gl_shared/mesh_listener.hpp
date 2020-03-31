#ifndef DRAWING_GLSHARED_MESH_LISTENER_HPP
#define DRAWING_GLSHARED_MESH_LISTENER_HPP

namespace Drawing
{

namespace Detail
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

} // Detail

} // Drawing

#endif // DRAWING_GLSHARED_MESH_LISTENER_HPP
