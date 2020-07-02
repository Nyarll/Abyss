#pragma once

// <class name		: Collider>
// <update date		: 2020 / 07 / 02>
// <author			: Nyarll>
// <GitHub			: https://github.com/Nyarll >

#ifndef COLLIDER_DEFINED
#define COLLIDER_DEFINED

enum ColliderType
{
	Sphere,
	Box
};

struct _ColliderHolderBase
{
	virtual ~_ColliderHolderBase() {}
};

template <typename Collider>
struct _ColliderHolder : public _ColliderHolderBase
{
	std::unique_ptr<Collider>	collider;
	_ColliderHolder(std::unique_ptr<Collider>&& colliderUniquePtr):collider(std::move(colliderUniquePtr)){}
};

class Collider
{
private:
	ColliderType m_colliderType;
	std::unique_ptr<_ColliderHolderBase> m_colliderHolder;
	float m_size;

public:
	Collider(ColliderType type, float size);
	Collider(const Collider& col);

	Collider& operator=(const Collider& col)
	{
		return std::move(*this);
	}

	void SetPosition(const DirectX::SimpleMath::Vector3& pos);

private:
	template <typename Type>
	void SetCollider()
	{
		m_colliderHolder = std::make_unique<_ColliderHolder<Type>>(std::make_unique<Type>());
	}

	template <typename Type>
	Type* GetCollider()
	{
		auto holder = dynamic_cast<_ColliderHolder<Type>*> (m_colliderHolder.get());
		return holder->collider.get();
	}
};

#endif
