#include "Player.h"

#include "../../../../../Framework/Framework.h"

Player::Player()
	:registry(nullptr)
	,m_player(entt::null)
{
}

Player::Player(entt::DefaultRegistry* _registry, Entity entity)
	:registry(_registry)
	,m_player(entity)
{
}

void Player::Update()
{
	if (!registry)return;
	if (m_player == entt::null)return;

	Move();
}

void Player::Move()
{
	DirectX::SimpleMath::Vector3 pos = registry->get<GameObject>(m_player).GetTransform()->localPosition;

	if (InputManager::GetKey(DirectX::Keyboard::Keys::W))
	{
		pos.z += 0.1f;
	}
	if (InputManager::GetKey(DirectX::Keyboard::Keys::S))
	{
		pos.z -= 0.1f;
	}
	if (InputManager::GetKey(DirectX::Keyboard::Keys::A))
	{
		pos.x += 0.1f;
	}
	if (InputManager::GetKey(DirectX::Keyboard::Keys::D))
	{
		pos.x -= 0.1f;
	}

	registry->get<GameObject>(m_player).GetTransform()->localPosition = pos;
}
