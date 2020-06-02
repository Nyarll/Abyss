#pragma once

// <class name		: PrimitiveModelList>
// <update date		: 2020 / 06 / 02>
// <author			: Nyarll>
// <GitHub			: https://github.com/Nyarll >

#ifndef PRIMITIVEMODELLIST_DEFINED
#define PRIMITIVEMODELLIST_DEFINED

class GameContext;

class PrimitiveModelList final
{
public:
	enum ID
	{
		Cone,
		Cube,
		Cylinder,
		Dodecahedron,
		GeoSphere,
		Icosahedron,
		Octahedron,
		Sphere,
		Teapot,
		Tetrahedron,
		Torus,

		ModelNum
	};

private:
	using PrimitiveModel = DirectX::GeometricPrimitive;

	std::array<std::unique_ptr<PrimitiveModel>, ModelNum> m_pools;	// <ModelList>

public:
	void Initialize(GameContext& context);

	PrimitiveModel* GetModel(ID id);
};

#endif