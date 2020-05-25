#pragma once

// <class name		: IState>
// <update date		: 2020 / 05 / 25>
// <author			: Nyarll>
// <GitHub			: https://github.com/Nyarll >

#include "../../Framework/ECS/ECS.h"

#ifndef ISTATE_DEFINED
#define ISTATE_DEFINED

// <State Interface>
class IState : public ECS::Registry
{
public:
	IState() {};
	virtual ~IState() = default;
};

#endif