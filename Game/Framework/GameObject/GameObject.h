#pragma once

// <class name		: GameObject>
// <update date		: 2020 / 05 / 25>
// <author			: Nyarll>
// <GitHub			: https://github.com/Nyarll >

#ifndef GAMEOBJECT_DEFINED
#define GAMEOBJECT_DEFINED

#include "Transform.h"

// <GameObject>
class GameObject
{
private:
	bool m_isActive = true;
	Transform transform;

public:
	
	Transform* GetTransform()
	{
		return &transform;
	}

	const DirectX::SimpleMath::Matrix& GetMatrix()
	{
		return transform.GetMatrix();
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