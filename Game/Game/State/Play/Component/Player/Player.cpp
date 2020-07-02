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

	
}
