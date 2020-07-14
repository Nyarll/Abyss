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
	enum Tag
	{
		None = (-1),

		Universal,
		Player,
		Floor,
	};

private:
	entt::DefaultRegistry* registry;
	uint32_t entity;

private:
	bool m_isActive = true;
	bool m_isRendering = true;
	Transform transform;
	Tag m_tag = Tag::Universal;

	DirectX::SimpleMath::Vector3 m_velocity;

	Entity parent = entt::null;						// <親オブジェクト>

	DirectX::SimpleMath::Matrix m_world;

	int m_count = 0;

	bool m_isCollisiion = false;
	Tag m_collidedObjectTag = Tag::None;

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

	// <更新>
	void Update()
	{
		transform.localPosition += m_velocity;
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
	// <親オブジェクトを設定>
	void SetParent(Entity _parent)
	{
		parent = _parent;
	}

	// <描画用行列を取得>
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
	// <描画する>
	void ActivateRendering()
	{
		m_isRendering = true;
	}

	// <オブジェクトを非アクティブにする>
	void Deactivate()
	{
		m_isActive = false;
	}
	// <描画しない>
	void DeactivateRendering()
	{
		m_isRendering = false;
	}

	// <オブジェクトがアクティブかどうか>
	bool IsActive()
	{
		return m_isActive;
	}

	// <描画するかどうか>
	bool IsRendering()
	{
		return m_isRendering;
	}

	// <何かと当たっているかどうか>
	bool IsCollision()
	{
		return m_isCollisiion;
	}

	// <当たっていない>
	void NotCollided()
	{
		m_isCollisiion = false;
	}

	// <当たっている>
	void Collided()
	{
		m_isCollisiion = true;
	}

	// <タグを取得>
	Tag GetTag()
	{
		return m_tag;
	}
	
	// <タグを設定>
	void SetTag(Tag tag)
	{
		m_tag = tag;
	}

	// <衝突したオブジェクトのタグを取得>
	Tag GetCollidedObjectTag()
	{
		return m_collidedObjectTag;
	}

	// <衝突したオブジェクトのタグを設定>
	void SetCollidedObjectTag(Tag tag)
	{
		m_collidedObjectTag = tag;
	}

	// <座標を設定>
	void SetPosition(DirectX::SimpleMath::Vector3 pos)
	{
		if (parent == entt::null)
		{
			transform.localPosition = pos;
		}
		else
		{
			auto pT = registry->get<GameObject>(parent).GetTransform();
			transform.localPosition = pos - pT->localPosition;
		}
	}

	// <座標を取得>
	DirectX::SimpleMath::Vector3 GetPosition()
	{
		if (parent == entt::null)
		{
			return transform.localPosition;
		}
		else
		{
			DirectX::SimpleMath::Vector3 position = transform.localPosition;
			auto pT = registry->get<GameObject>(parent).GetTransform();
			position += pT->localPosition;
			return position;
		}
	}

	// <速度を設定>
	void SetVelocity(const DirectX::SimpleMath::Vector3& vel)
	{
		m_velocity = vel;
	}
	// <速度を取得>
	const DirectX::SimpleMath::Vector3& GetVelocity()
	{
		return m_velocity;
	}
	// <回転を設定>
	void SetRotation(const DirectX::SimpleMath::Quaternion& rotation)
	{
		transform.localRotation = rotation;
	}
	// <回転を取得>
	const DirectX::SimpleMath::Quaternion& GetRotation()
	{
		if (parent == entt::null)
		{
			return transform.localRotation;
		}
		else
		{
			DirectX::SimpleMath::Quaternion rotation = transform.localRotation;
			auto pT = registry->get<GameObject>(parent).GetTransform();
			rotation *= pT->localRotation;
			return rotation;
		}
	}
	// <拡縮を設定>
	void SetScale(const DirectX::SimpleMath::Vector3& scale)
	{
		transform.localScale = scale;
	}

	// <拡縮を取得>
	const DirectX::SimpleMath::Vector3& GetScale()
	{
		if (parent == entt::null)
		{
			return transform.localScale;
		}
		else
		{
			DirectX::SimpleMath::Vector3 scale = transform.localScale;
			auto pT = registry->get<GameObject>(parent).GetTransform();
			scale *= pT->localScale;
			return scale;
		}
	}
};

#endif