#include "Player.h"

#include "../../../../../Framework/Framework.h"

#include "../MapGenerator/MapGenerator.h"

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

void Player::DetermineSpawnPosition(Entity map_generator)
{
	auto& spawnData = registry->get<MapGenerator>(map_generator).GetEntitySpawnMapData();

	Random random;
	while (true)
	{
		float x = random.Range(0, spawnData.size() - 1);
		float z = random.Range(0, spawnData.size() - 1);

		if (spawnData[z][x] == MapGenerator::MapState::Floor)
		{
			auto& obj = registry->get<GameObject>(m_player);
			obj.GetTransform()->localPosition = DirectX::SimpleMath::Vector3(x, obj.GetTransform()->localPosition.y, z);
			spawnData[z][x] = MapGenerator::MapState::EntityPlaced;
			break;
		}
	}
}

void Player::Move()
{
	DirectX::SimpleMath::Vector3 pos = registry->get<GameObject>(m_player).GetTransform()->localPosition;
	DirectX::SimpleMath::Vector3 vel = DirectX::SimpleMath::Vector3::Zero;

	if (InputManager::GetKey(DirectX::Keyboard::Keys::W))
	{
		vel.z += 1.0f;
	}
	if (InputManager::GetKey(DirectX::Keyboard::Keys::S))
	{
		vel.z -= 1.0f;
	}
	if (InputManager::GetKey(DirectX::Keyboard::Keys::A))
	{
		vel.x += 1.0f;
	}
	if (InputManager::GetKey(DirectX::Keyboard::Keys::D))
	{
		vel.x -= 1.0f;
	}
	vel.Normalize();
	vel *= .5f;

	registry->get<GameObject>(m_player).GetTransform()->localPosition = pos + vel;
}
