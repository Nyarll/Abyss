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
	Entity m_player;
	entt::DefaultRegistry* registry;

public:
	Player();
	Player(entt::DefaultRegistry* _registry, Entity entity);

	void Update();

	void DetermineSpawnPosition(Entity map_generator);

private:
	void Move();
};

#endif