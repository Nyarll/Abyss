#include "PlayState.h"

#include "../../../Framework/Framework.h"
#include "Component/Components.h"

void PlayState::Initialize(GameContext& context)
{
	{
		auto camera = m_registry.create();
		auto& obj = m_registry.assign<GameObject>(camera);
		obj.GetTransform()->localPosition = DirectX::SimpleMath::Vector3(0.f, 10.f, 10.f);
		m_registry.assign<Camera>(camera);
	}

	for (int z = 0; z < 10; z++)
	{
		for (int x = 0; x < 10; x++)
		{
			auto object = m_registry.create();
			auto& obj = m_registry.assign<GameObject>(object);

			obj.GetTransform()->localPosition = DirectX::SimpleMath::Vector3((float)x * 1.5f, 0.f, (float)z * 1.5f);

			auto& renderer = m_registry.assign<PrimitiveRenderer>(object);
			renderer.SetModel(context.Get<PrimitiveModelList>().GetModel(PrimitiveModelList::ID::Cube));
			auto& move = m_registry.assign<Move>(object);
			if (x % 2)
			{
				move.SetFunction([](GameObject* obj)
				{
					obj->GetTransform()->localRotation *=
						DirectX::SimpleMath::Quaternion::CreateFromRotationMatrix(
							DirectX::SimpleMath::Matrix::CreateRotationY(
								DirectX::XMConvertToRadians(5.f)));
				});
			}
			else
			{
				move.SetFunction([](GameObject* obj)
				{
					obj->GetTransform()->localRotation *=
						DirectX::SimpleMath::Quaternion::CreateFromRotationMatrix(
							DirectX::SimpleMath::Matrix::CreateRotationY(
								DirectX::XMConvertToRadians(-5.f)));
				});
			}
		}
	}

	m_registry.view<GameObject>().each([&](auto entity, auto& obj)
	{
		auto transform = obj.GetTransform();
		transform->localScale = DirectX::SimpleMath::Vector3(1.f, 1.f, 1.f);
	});
}

void PlayState::Update(GameContext& context)
{
	Transform* target = nullptr;
	// <プレイヤーを探してターゲットにする>
	m_registry.view<GameObject, PrimitiveRenderer>().each([&](auto entity, auto& obj, auto& renderer)
	{
		target = obj.GetTransform();
	});

	m_registry.view<GameObject, Camera>().each([&](auto entity, auto& obj, auto& camera)
	{
		camera.Update(context, obj.GetTransform(), target);
	});

	m_registry.view<GameObject, Move>().each([](auto entity, auto& obj, auto& move)
	{
		move.Update(&obj);
	});

	// <TransformをWorld行列へ更新>
	m_registry.view<GameObject>().each([&](auto entity, auto& obj)
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
