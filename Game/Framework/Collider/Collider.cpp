#include "Collider.h"

Collider::Collider(ColliderType type, float size)
	:m_colliderType(type)
{
	m_size = size;

	switch (m_colliderType)
	{
	case ColliderType::Sphere:
	{
		SetCollider<DirectX::BoundingSphere>();
		auto sphere = GetCollider<DirectX::BoundingSphere>();
		sphere->Radius = size;
		break;
	}
	case ColliderType::Box:
	{
		SetCollider<DirectX::BoundingBox>();
		auto box = GetCollider<DirectX::BoundingBox>();
		box->Extents = DirectX::SimpleMath::Vector3(size, size, size);
		break;
	}
	}
}

Collider::Collider(const Collider& col)
{
	this->m_colliderType = col.m_colliderType;
	this->m_size = col.m_size;

	switch (m_colliderType)
	{
	case ColliderType::Sphere:
	{
		SetCollider<DirectX::BoundingSphere>();
		auto sphere = GetCollider<DirectX::BoundingSphere>();
		sphere->Radius = m_size;
		break;
	}
	case ColliderType::Box:
	{
		SetCollider<DirectX::BoundingBox>();
		auto box = GetCollider<DirectX::BoundingBox>();
		box->Extents = DirectX::SimpleMath::Vector3(m_size, m_size, m_size);
		break;
	}
	}
}

void Collider::SetPosition(const DirectX::SimpleMath::Vector3& pos)
{
	DirectX::XMFLOAT3 position = pos;

	switch (m_colliderType)
	{
	case ColliderType::Sphere:
	{
		auto sphere = GetCollider<DirectX::BoundingSphere>();
		sphere->Center = position;
		break;
	}
	case ColliderType::Box:
	{
		auto box = GetCollider<DirectX::BoundingBox>();
		box->Center = position;
		break;
	}
	}
}
