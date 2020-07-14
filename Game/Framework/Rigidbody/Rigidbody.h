#pragma once

// <class name		: Rigidbody>
// <update date		: 2020 / 07 / 2>
// <author			: Nyarll>
// <GitHub			: https://github.com/Nyarll >

#ifndef RIGIDBODY_DEFINED
#define RIGIDBODY_DEFINED

class Rigidbody
{
private:
	static const float kGravity;

	Entity m_owner;
	entt::DefaultRegistry* registry;

	DirectX::SimpleMath::Vector3 m_velocity;

public:
	Rigidbody(entt::DefaultRegistry* _registry, Entity _entity);

	void Update();

private:
	void Simulate();
};

#endif