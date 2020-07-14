#pragma once

// <class name		: Player>
// <update date		: 2020 / 06 / 30>
// <author			: Nyarll>
// <GitHub			: https://github.com/Nyarll >

#ifndef PLAYER_DEFINED
#define PLAYER_DEFINED

class Player
{
private:
	static const float kJumpForce;

	Entity m_player;
	entt::DefaultRegistry* registry;

	DirectX::SimpleMath::Vector3 m_spawnPoint;

	bool m_isJump = false;

public:
	Player();
	Player(entt::DefaultRegistry* _registry, Entity entity);

	void Update();

	void DetermineSpawnPosition(Entity map_generator);

private:
	void Move();
	void Jump();
	void Physics();
	void Respawn();
};

#endif