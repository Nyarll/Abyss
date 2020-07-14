#include "Rigidbody.h"

#include "../GameObject/GameObject.h"

const float Rigidbody::kGravity = 0.03f;

Rigidbody::Rigidbody(entt::DefaultRegistry * _registry, Entity _entity)
	:registry(_registry)
	,m_owner(_entity)
{
}

void Rigidbody::Update()
{
	if (m_owner == entt::null)return;
	if (!registry)return;
	Simulate();
}

void Rigidbody::Simulate()
{
	auto& gameObject = registry->get<GameObject>(m_owner);
	DirectX::SimpleMath::Vector3 vel = gameObject.GetVelocity();
	vel.y -= kGravity;

	gameObject.SetVelocity(vel);
}
