#pragma once

// <class name		: System>
// <update date		: 2020 / 05 / 26>
// <author			: Nyarll>
// <GitHub			: https://github.com/Nyarll >

#ifndef SYSTEM_DEFINED
#define SYSTEM_DEFINED

class System
{
	static DirectX::SimpleMath::Vector2 windowSize;

public:
	static const DirectX::SimpleMath::Vector2& GetWindowSize()
	{
		return windowSize;
	}

	static void SetWindowSize(const DirectX::SimpleMath::Vector2& size)
	{
		windowSize = size;
	}
};

#endif