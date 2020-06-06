#pragma once

// <class name		: Move>
// <update date		: 2020 / 06 / 05>
// <author			: Nyarll>
// <GitHub			: https://github.com/Nyarll >

#ifndef MOVE_DEFINED
#define MOVE_DEFINED

#include "../../../../../Framework/Framework.h"

class Move
{
private:
	std::function<void(GameObject*)> m_func;

public:
	void SetFunction(std::function<void(GameObject*)> func)
	{
		m_func = func;
	}

	void Update(GameObject* owner)
	{
		m_func(owner);
	}
};

#endif