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

	Entity parent = entt::null;						// <�e�I�u�W�F�N�g>

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

	// <�X�V>
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
	// <�e�I�u�W�F�N�g��ݒ�>
	void SetParent(Entity _parent)
	{
		parent = _parent;
	}

	// <�`��p�s����擾>
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

	// <�I�u�W�F�N�g���A�N�e�B�u�ɂ���>
	void Activate()
	{
		m_isActive = true;
	}
	// <�`�悷��>
	void ActivateRendering()
	{
		m_isRendering = true;
	}

	// <�I�u�W�F�N�g���A�N�e�B�u�ɂ���>
	void Deactivate()
	{
		m_isActive = false;
	}
	// <�`�悵�Ȃ�>
	void DeactivateRendering()
	{
		m_isRendering = false;
	}

	// <�I�u�W�F�N�g���A�N�e�B�u���ǂ���>
	bool IsActive()
	{
		return m_isActive;
	}

	// <�`�悷�邩�ǂ���>
	bool IsRendering()
	{
		return m_isRendering;
	}

	// <�����Ɠ������Ă��邩�ǂ���>
	bool IsCollision()
	{
		return m_isCollisiion;
	}

	// <�������Ă��Ȃ�>
	void NotCollided()
	{
		m_isCollisiion = false;
	}

	// <�������Ă���>
	void Collided()
	{
		m_isCollisiion = true;
	}

	// <�^�O���擾>
	Tag GetTag()
	{
		return m_tag;
	}
	
	// <�^�O��ݒ�>
	void SetTag(Tag tag)
	{
		m_tag = tag;
	}

	// <�Փ˂����I�u�W�F�N�g�̃^�O���擾>
	Tag GetCollidedObjectTag()
	{
		return m_collidedObjectTag;
	}

	// <�Փ˂����I�u�W�F�N�g�̃^�O��ݒ�>
	void SetCollidedObjectTag(Tag tag)
	{
		m_collidedObjectTag = tag;
	}

	// <���W��ݒ�>
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

	// <���W���擾>
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

	// <���x��ݒ�>
	void SetVelocity(const DirectX::SimpleMath::Vector3& vel)
	{
		m_velocity = vel;
	}
	// <���x���擾>
	const DirectX::SimpleMath::Vector3& GetVelocity()
	{
		return m_velocity;
	}
	// <��]��ݒ�>
	void SetRotation(const DirectX::SimpleMath::Quaternion& rotation)
	{
		transform.localRotation = rotation;
	}
	// <��]���擾>
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
	// <�g�k��ݒ�>
	void SetScale(const DirectX::SimpleMath::Vector3& scale)
	{
		transform.localScale = scale;
	}

	// <�g�k���擾>
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