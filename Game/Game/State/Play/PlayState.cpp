#include "PlayState.h"

#include "../../../Framework/Framework.h"
#include "Component/Components.h"

void PlayState::Initialize(GameContext& context)
{
	{
		auto camera = m_registry.create();
		auto& obj = m_registry.assign<GameObject>(camera, &m_registry, camera);
		obj.GetTransform()->localPosition = DirectX::SimpleMath::Vector3(0.f, 15.f, 30.f);
		m_registry.assign<Camera>(camera);
		auto& move = m_registry.assign<Move>(camera);
		move.SetFunction([](GameObject* obj)
		{
			auto pos = obj->GetTransform()->localPosition;
			if (InputManager::GetKey(DirectX::Keyboard::Keys::W))
			{
				pos.z -= 0.1f;
			}
			if (InputManager::GetKey(DirectX::Keyboard::Keys::A))
			{
				pos.x -= 0.1f;
			}
			if (InputManager::GetKey(DirectX::Keyboard::Keys::LeftShift))
			{
				pos.y -= 0.1f;
			}
			if (InputManager::GetKey(DirectX::Keyboard::Keys::S))
			{
				pos.z += 0.1f;
			}
			if (InputManager::GetKey(DirectX::Keyboard::Keys::D))
			{
				pos.x += 0.1f;
			}
			if (InputManager::GetKey(DirectX::Keyboard::Keys::Space))
			{
				pos.y += 0.1f;
			}
			obj->GetTransform()->localPosition = pos;
		});
	}
	float shift = 1.5f;

	auto parentEntity = m_registry.create();
	auto& parentObj = m_registry.assign<GameObject>(parentEntity, &m_registry, parentEntity);
	parentObj.GetTransform()->localPosition = DirectX::SimpleMath::Vector3(0.f * shift, 0.f * shift, 0.f * shift);
	auto& pMove = m_registry.assign<Move>(parentEntity);
	pMove.SetFunction([](GameObject* object)
	{
		if (InputManager::GetKey(DirectX::Keyboard::Keys::X))
		{
			object->GetTransform()->localRotation *=
				DirectX::SimpleMath::Quaternion::CreateFromRotationMatrix(
					DirectX::SimpleMath::Matrix::CreateRotationY(
						DirectX::XMConvertToRadians(5.f)));
		}
		else
		{
			object->GetTransform()->localRotation = DirectX::SimpleMath::Quaternion::Identity;
		}
	});

	for (int y = 0; y < 11; y++)
	{
		for (int z = 0; z < 11; z++)
		{
			for (int x = 0; x < 11; x++)
			{
				auto object = m_registry.create();
				auto& obj = m_registry.assign<GameObject>(object, &m_registry, object);
				obj.SetParent(parentEntity);

				obj.GetTransform()->localPosition = DirectX::SimpleMath::Vector3((float)(x - 5) * shift, (float)(y - 5) * shift, (float)(z - 5) * shift);

				auto& renderer = m_registry.assign<PrimitiveRenderer>(object);
				renderer.SetModel(context.Get<PrimitiveModelList>().GetModel(PrimitiveModelList::ID::Teapot));
				auto& move = m_registry.assign<Move>(object);
				/**/
				move.SetFunction([](GameObject* obj)
				{
					if (InputManager::GetKey(DirectX::Keyboard::Keys::Z))
					{
						obj->GetTransform()->localRotation *=
							DirectX::SimpleMath::Quaternion::CreateFromRotationMatrix(
								DirectX::SimpleMath::Matrix::CreateRotationY(
									DirectX::XMConvertToRadians(10.f)) *
								DirectX::SimpleMath::Matrix::CreateRotationX(
									DirectX::XMConvertToRadians(10.f)) *
								DirectX::SimpleMath::Matrix::CreateRotationZ(
									DirectX::XMConvertToRadians(-5.f))
							);
					}
					else
					{
						obj->GetTransform()->localRotation = DirectX::SimpleMath::Quaternion::Identity;
					}
				});
				/**/
			}
		}
	}

	m_registry.view<GameObject>().each([](auto entity, auto& obj)
	{
		auto transform = obj.GetTransform();
		transform->localScale = DirectX::SimpleMath::Vector3(1.f, 1.f, 1.f);
	});
}

void PlayState::Update(GameContext& context)
{
	//Transform* target = nullptr;
	// <プレイヤーを探してターゲットにする>
	/*m_registry.view<GameObject, PrimitiveRenderer>().each([&](auto entity, auto& obj, auto& renderer)
	{
		target = obj.GetTransform();
	});*/

	Transform target;
	target.localPosition = target.localScale = DirectX::SimpleMath::Vector3(0, 0, 0);
	m_registry.view<GameObject, Camera>().each([&](auto entity, auto& obj, auto& camera)
	{
		camera.Update(context, obj.GetTransform(), &target);
	});

	m_registry.view<GameObject, Move>().each([](auto entity, auto& obj, auto& move)
	{
		move.Update(&obj);
	});

	// <TransformをWorld行列へ更新>
	m_registry.view<GameObject>().each([](auto entity, auto& obj)
	{
		obj.Update();
	});
}

void PlayState::Render(GameContext& context)
{
	DirectX::SimpleMath::Matrix view, proj;

	m_registry.view<Camera>().each([&](auto entity, auto& camera)
	{
		view = camera.GetViewMatrix();
		proj = camera.GetProjectionMatrix();
	});

	m_registry.view<GameObject, PrimitiveRenderer>().each([&](auto entity, auto& obj, auto& renderer)
	{
		renderer.Draw(obj.GetMatrix(), view, proj, DirectX::Colors::Red);
	});
}
