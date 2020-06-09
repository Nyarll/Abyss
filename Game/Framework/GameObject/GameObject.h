#pragma once

// <class name		: GameObject>
// <update date		: 2020 / 05 / 25>
// <author			: Nyarll>
// <GitHub			: https://github.com/Nyarll >

#ifndef GAMEOBJECT_DEFINED
#define GAMEOBJECT_DEFINED

#include "../Optional/Optional.h"
#include "Transform.h"

// <GameObject>
class GameObject
{
public:
	entt::DefaultRegistry* registry;
	uint32_t entity;

private:
	bool m_isActive = true;
	Transform transform;

	Entity parent = entt::null;						// <親オブジェクト>

	DirectX::SimpleMath::Matrix m_world;

	int m_count = 0;

public:
	GameObject()
		:registry(nullptr),
		entity(entt::null)
	{
	}
	GameObject(entt::DefaultRegistry* _pRegistry, uint32_t _entity)
		:registry(_pRegistry),
		 entity(_entity)
	{
	}

	void Update()
	{
		m_world = transform.GetMatrix();
		m_count++;
	}

	int GetCount()
	{
		return m_count;
	}

	Transform* GetTransform()
	{
		return &transform;
	}

	void SetParent(Entity _parent)
	{
		parent = _parent;
	}

	const DirectX::SimpleMath::Matrix GetMatrix()
	{
		if (parent == entt::null)
		{
			return m_world;
		}
		else
		{
			DirectX::SimpleMath::Matrix matrix = m_world;
			auto& pT = registry->get<GameObject>(parent);
			matrix *= pT.GetMatrix();
			return matrix;
		}
	}

	// <オブジェクトをアクティブにする>
	void Activate()
	{
		m_isActive = true;
	}
	// <オブジェクトを非アクティブにする>
	void Deactivate()
	{
		m_isActive = false;
	}

	// <オブジェクトがアクティブかどうか>
	bool IsActive()
	{
		return m_isActive;
	}
};

#endif