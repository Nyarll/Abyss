#include "PlayState.h"

#include "../../../Framework/Framework.h"
#include "Component/Components.h"

void PlayState::Initialize(GameContext& context)
{
	{
		auto camera = m_registry.create();
		auto& obj = m_registry.assign<GameObject>(camera, &m_registry, camera);
		obj.GetTransform()->localPosition = DirectX::SimpleMath::Vector3(0.f, 15.f, 30.f);
		m_registry.assign<DebugCamera>(camera);
	}

	{
		//auto entity = m_registry.create();
		//auto& generator = m_registry.assign<MapGenerator>(entity, &m_registry);
		//generator.GenerateMap(context);
		//m_mapGenerator = entity;
	}

	{
		auto entity = m_registry.create();
		m_registry.assign<FontRenderer>(entity);
		m_registry.assign<DirectX::SimpleMath::Vector2>(entity);
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

	if (InputManager::GetKeyDown(DirectX::Keyboard::Keys::F1))
	{
		//m_registry.get<MapGenerator>(m_mapGenerator).GenerateMap(context);
	}

	Transform target;
	target.localPosition = target.localScale = DirectX::SimpleMath::Vector3(0, 0, 0);
	m_registry.view<GameObject, DebugCamera>().each([&](auto entity, auto& obj, auto& camera)
	{
		camera.Update(context, obj.GetTransform());
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
	DirectX::SimpleMath::Vector3 cameraPos;

	m_registry.view<DebugCamera, GameObject>().each([&](auto entity, auto& camera, auto& obj)
	{
		view = camera.GetViewMatrix();
		proj = camera.GetProjectionMatrix();
		cameraPos = obj.GetTransform()->localPosition;
	});

	m_registry.view<GameObject, PrimitiveRenderer>().each([&](auto entity, auto& obj, auto& renderer)
	{
		if (obj.IsActive())
		{
			renderer.Draw(obj.GetMatrix(), view, proj, DirectX::Colors::Red);
		}
	});

	m_registry.view<FontRenderer, DirectX::SimpleMath::Vector2>().each([&](auto entity, auto& renderer, auto& pos)
	{
		auto font = context.Get<FontManager>().GetSpriteFont("Meiryo UI");
		renderer.Draw(context, font, pos, DirectX::Colors::Red, "Camera : %.2f, %.2f", cameraPos.x, cameraPos.z);
	});
}
