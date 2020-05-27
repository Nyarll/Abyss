#pragma once

// <class name		: TitleState>
// <update date		: 2020 / 05 / 26>
// <author			: Nyarll>
// <GitHub			: https://github.com/Nyarll >

#ifndef TITLESTATE_DEFINED
#define TITLESTATE_DEFINED

#include "../IState.h"

// <TitleState>
class TitleState : public IState
{
public:
	virtual void Initialize(GameContext& context)override;	// <‰Šú‰»>

	virtual void Update(GameContext& context)override;		// <XV>
	virtual void Render(GameContext& context)override;		// <•`‰æ>

	static IState* Create()
	{
		return{ new TitleState };
	}
};

#endif