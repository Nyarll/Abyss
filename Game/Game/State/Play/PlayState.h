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
public:
	virtual void Initialize(GameContext& context)override;	// <初期化>

	virtual void Update(GameContext& context)override;		// <更新>
	virtual void Render(GameContext& context)override;		// <描画>

	static IState* Create()
	{
		return{ new PlayState };
	}
};

#endif