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

public:
	Transform transform;

	// <�I�u�W�F�N�g���A�N�e�B�u�ɂ���>
	void Activate()
	{
		m_isActive = true;
	}
	// <�I�u�W�F�N�g���A�N�e�B�u�ɂ���>
	void Deactivate()
	{
		m_isActive = false;
	}

	// <�I�u�W�F�N�g���A�N�e�B�u���ǂ���>
	bool IsActive()
	{
		return m_isActive;
	}
};

#endif