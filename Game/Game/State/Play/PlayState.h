#pragma once

// <class name		: PlayState>
// <update date		: 2020 / 06 / 02>
// <author			: Nyarll>
// <GitHub			: https://github.com/Nyarll >

#ifndef PLAYSTATE_DEFINED
#define PLAYSTATE_DEFINED

#include "../IState.h"

// <PlayState>
class PlayState : public IState
{
private:
	Entity m_mapGenerator = entt::null;

public:
	virtual void Initialize(GameContext& context)override;	// <‰Šú‰»>

	virtual void Update(GameContext& context)override;		// <XV>
	virtual void Render(GameContext& context)override;		// <•`‰æ>

	static IState* Create()
	{
		return{ new PlayState };
	}
};

#endif