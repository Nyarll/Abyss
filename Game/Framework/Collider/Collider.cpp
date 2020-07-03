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

Collider::Collider(Collider&& col) noexcept
{
	m_colliderType = col.m_colliderType;
	m_size = col.m_size;

	m_colliderHolder = std::move(col.m_colliderHolder);
}

Collider& Collider::operator=(Collider&& col) noexcept
{
	if (this != &col)
	{
		m_colliderType = col.m_colliderType;
		m_size = col.m_size;
		m_colliderHolder = std::move(col.m_colliderHolder);
	}
	return *this;
}

void Collider::SetPosition(const DirectX::SimpleMath::Vector3& pos)
{
	DirectX::XMFLOAT3 position;
	position.x = pos.x;
	position.y = pos.y;
	position.z = pos.z;

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

DirectX::SimpleMath::Vector3 Collider::GetPosition()
{
	DirectX::XMFLOAT3 position;

	switch (m_colliderType)
	{
	case ColliderType::Sphere:
	{
		auto sphere = GetCollider<DirectX::BoundingSphere>();
		position = sphere->Center;
		break;
	}
	case ColliderType::Box:
	{
		auto box = GetCollider<DirectX::BoundingBox>();
		position = box->Center;
		break;
	}
	}

	DirectX::SimpleMath::Vector3 result;
	result.x = position.x;
	result.y = position.y;
	result.z = position.z;

	return result;
}

bool Collider::OnCollision(Collider& collider)
{
	switch (m_colliderType)
	{
	case ColliderType::Sphere:
	{
		auto sphere = GetCollider<DirectX::BoundingSphere>();
		return OnCollisionSphere(collider, *sphere);
	}
	case ColliderType::Box:
	{
		auto box = GetCollider<DirectX::BoundingBox>();
		return OnCollisionBox(collider, *box);
	}
	}
}

bool Collider::OnCollisionSphere(Collider& other, DirectX::BoundingSphere& bounding)
{
	switch (other.GetColliderType())
	{
	case ColliderType::Sphere:
	{
		auto sphere = other.GetCollider<DirectX::BoundingSphere>();
		return sphere->Intersects(bounding);
	}
	case ColliderType::Box:
	{
		auto box = other.GetCollider<DirectX::BoundingBox>();
		return box->Intersects(bounding);
	}
	}
}

bool Collider::OnCollisionBox(Collider& other, DirectX::BoundingBox& bounding)
{
	switch (other.GetColliderType())
	{
	case ColliderType::Sphere:
	{
		auto sphere = other.GetCollider<DirectX::BoundingSphere>();
		return sphere->Intersects(bounding);
	}
	case ColliderType::Box:
	{
		auto box = other.GetCollider<DirectX::BoundingBox>();
		return box->Intersects(bounding);
	}
	}
}
