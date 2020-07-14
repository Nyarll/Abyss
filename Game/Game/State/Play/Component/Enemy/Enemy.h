#pragma once

// <class name		: Enemy>
// <update date		: 2020 / 07 / 14>
// <author			: Nyarll>
// <GitHub			: https://github.com/Nyarll >

#ifndef ENEMY_DEFINED
#define ENEMY_DEFINED

class Enemy
{
private:
	Entity m_player;
	Entity m_enemy;
	entt::DefaultRegistry* registry;

public:
	Enemy(entt::DefaultRegistry* _registry, Entity entity);

	void Update();

	void DetermineSpawnPosition(Entity map_generator);

	void SetPlayerEntity(Entity player);
};

#endif