#include "Enemy.h"

#include "../MapGenerator/MapGenerator.h"
#include "../../../../../Framework/Framework.h"

Enemy::Enemy(entt::DefaultRegistry * _registry, Entity entity)
	:registry(_registry)
	,m_enemy(entity)
{
}

void Enemy::Update()
{
}

void Enemy::DetermineSpawnPosition(Entity map_generator)
{
	auto& spawnData = registry->get<MapGenerator>(map_generator).GetEntitySpawnMapData();

	Random random;
	while (true)
	{
		float x = random.Range(0, spawnData.size() - 1);
		float z = random.Range(0, spawnData.size() - 1);

		if (spawnData[z][x] == MapGenerator::MapState::Floor)
		{
			auto& obj = registry->get<GameObject>(m_enemy);
			auto spawnPoint = DirectX::SimpleMath::Vector3(x, obj.GetPosition().y, z);

			obj.SetPosition(spawnPoint);
			spawnData[z][x] = MapGenerator::MapState::EntityPlaced;

			break;
		}
	}
}

void Enemy::SetPlayerEntity(Entity player)
{
	m_player = player;
}
