#pragma once

// <class name		: IState>
// <update date		: 2020 / 05 / 25>
// <author			: Nyarll>
// <GitHub			: https://github.com/Nyarll >

#ifndef ISTATE_DEFINED
#define ISTATE_DEFINED

#include <entt.hpp>

class GameContext;

// <State Interface>
class IState
{
protected:
	entt::DefaultRegistry m_registry;

public:
	IState() {};
	virtual ~IState() = default;

	virtual void Initialize() = 0;	// <初期化>

	virtual void Update() = 0;		// <更新>
	virtual void Render() = 0;		// <描画>
};

#endif