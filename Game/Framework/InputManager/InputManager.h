#pragma once

// <class name		: InputManager>
// <update date		: 2020 / 05 / 27>
// <author			: Nyarll>
// <GitHub			: https://github.com/Nyarll >

#ifndef INPUTMANAGER_DEFINED
#define INPUTMANAGER_DEFINED

class InputManager final
{
private:
	static DirectX::Keyboard::KeyboardStateTracker m_keyboardTracker;

public:
	static void Update();
	
	static bool GetKey(DirectX::Keyboard::Keys key);
	static bool GetKeyUp(DirectX::Keyboard::Keys key);
	static bool GetKeyDown(DirectX::Keyboard::Keys key);

	static bool GetAnyKey();
	static bool GetAnyKeyDown();
};

#endif