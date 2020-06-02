#include "InputManager.h"

DirectX::Keyboard::KeyboardStateTracker InputManager::m_keyboardTracker;

void InputManager::Update()
{
	m_keyboardTracker.Update(DirectX::Keyboard::Get().GetState());
}

bool InputManager::GetKey(DirectX::Keyboard::Keys key)
{
	return m_keyboardTracker.lastState.IsKeyDown(key);
}

bool InputManager::GetKeyUp(DirectX::Keyboard::Keys key)
{
	return m_keyboardTracker.IsKeyReleased(key);
}

bool InputManager::GetKeyDown(DirectX::Keyboard::Keys key)
{
	return m_keyboardTracker.IsKeyPressed(key);
}

bool InputManager::GetAnyKey()
{
	auto currPtr = reinterpret_cast<const uint32_t*>(&m_keyboardTracker.lastState);
	for (size_t j = 0; j < (256 / 32); ++j)
	{
		if (*currPtr != 0)
			return true;
		++currPtr;
	}
	return false;
}

bool InputManager::GetAnyKeyDown()
{
	auto currPtr = reinterpret_cast<const uint32_t*>(&m_keyboardTracker.pressed);
	for (size_t j = 0; j < (256 / 32); ++j)
	{
		if (*currPtr != 0)
			return true;
		++currPtr;
	}
	return false;
}
