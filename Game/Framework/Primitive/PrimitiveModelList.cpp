#include "PrimitiveModelList.h"

#include "../Context/GameContext.h"

extern void ExitGame();

using PrimitiveModel = DirectX::GeometricPrimitive;

void PrimitiveModelList::Initialize(GameContext& context)
{
	auto deviceContext = context.GetDR().GetD3DDeviceContext();

	// <scale“™‚ðŒã‚©‚ç‚¢‚¶‚é‚©‚à‚µ‚ê‚È‚¢‚Ì‚ÅA“™”{i‚P”{j‚Åì¬‚·‚é>
	m_pools[ID::Cone]			= DirectX::GeometricPrimitive::CreateCone(deviceContext);
	m_pools[ID::Cube]			= DirectX::GeometricPrimitive::CreateCube(deviceContext);
	m_pools[ID::Cylinder]		= DirectX::GeometricPrimitive::CreateCylinder(deviceContext);
	m_pools[ID::Dodecahedron]	= DirectX::GeometricPrimitive::CreateDodecahedron(deviceContext);
	m_pools[ID::GeoSphere]		= DirectX::GeometricPrimitive::CreateGeoSphere(deviceContext);
	m_pools[ID::Icosahedron]	= DirectX::GeometricPrimitive::CreateIcosahedron(deviceContext);
	m_pools[ID::Octahedron]		= DirectX::GeometricPrimitive::CreateOctahedron(deviceContext);
	m_pools[ID::Sphere]			= DirectX::GeometricPrimitive::CreateSphere(deviceContext);
	m_pools[ID::Teapot]			= DirectX::GeometricPrimitive::CreateTeapot(deviceContext);
	m_pools[ID::Tetrahedron]	= DirectX::GeometricPrimitive::CreateTetrahedron(deviceContext);
	m_pools[ID::Torus]			= DirectX::GeometricPrimitive::CreateTorus(deviceContext);
}

PrimitiveModel* PrimitiveModelList::GetModel(ID id)
{
	assert(id > -1 && id < ID::ModelNum && "ID is invalid.");
	if (id >= ID::ModelNum || id < 0)
	{
		ExitGame();
	}

	return m_pools[id].get();
}
