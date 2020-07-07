#include "Player.h"

#include "../../../../../Framework/Framework.h"

#include "../MapGenerator/MapGenerator.h"

const float Player::kJumpForce = 0.5f;

Player::Player()
	:registry(nullptr)
	, m_player(entt::null)
{
}

Player::Player(entt::DefaultRegistry* _registry, Entity entity)
	: registry(_registry)
	, m_player(entity)
{
}

void Player::Update()
{
	if (!registry)return;
	if (m_player == entt::null)return;

	Physics();

	Move();
	Jump();
	
	Respawn();
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
			m_spawnPoint = DirectX::SimpleMath::Vector3(x, obj.GetTransform()->localPosition.y, z);
			obj.GetTransform()->localPosition = m_spawnPoint;
			spawnData[z][x] = MapGenerator::MapState::EntityPlaced;

			break;
		}
	}
}

void Player::Move()
{
	auto& obj = registry->get<GameObject>(m_player);
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
	vel *= .3f;
	vel.y = obj.GetVelocity().y;

	obj.SetVelocity(vel);
}

void Player::Jump()
{
	auto& obj = registry->get<GameObject>(m_player);
	DirectX::SimpleMath::Vector3 pos = obj.GetPosition();
	DirectX::SimpleMath::Vector3 vel = obj.GetVelocity();

	if (InputManager::GetKeyDown(DirectX::Keyboard::Keys::Space) && !m_isJump)
	{
		m_isJump = true;
		vel.y = kJumpForce;
		obj.SetVelocity(vel);
		//pos.y += vel.y;
		//obj.SetPosition(pos);
	}
}

void Player::Physics()
{
	auto& obj = registry->get<GameObject>(m_player);
	if (!obj.IsCollision())
		return;

	if (obj.GetCollidedObjectTag() == GameObject::Tag::Floor)
	{
		auto pos = obj.GetPosition();
		auto vel = obj.GetVelocity();

		obj.SetVelocity(DirectX::SimpleMath::Vector3(vel.x, 0, vel.z));
		obj.SetPosition(DirectX::SimpleMath::Vector3(pos.x, 0, pos.z));
		m_isJump = false;
	}
}

void Player::Respawn()
{
	auto& obj = registry->get<GameObject>(m_player);

	if (obj.GetPosition().y < -10)
	{
		DirectX::SimpleMath::Vector3 respawn = m_spawnPoint;
		respawn.y = 5.f;
		obj.SetPosition(respawn);
	}
}
