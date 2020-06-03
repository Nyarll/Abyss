#include "PlayState.h"

#include "../../../Framework/Framework.h"

void PlayState::Initialize(GameContext& context)
{
	{
		auto camera = m_registry.create();
		auto& obj = m_registry.assign<GameObject>(camera);
		obj.GetTransform()->localPosition = DirectX::SimpleMath::Vector3(0.f, 10.f, 10.f);
		m_registry.assign<Camera>(camera);
	}
	{
		auto object = m_registry.create();
		m_registry.assign<GameObject>(object);
		auto& renderer = m_registry.assign<PrimitiveRenderer>(object);
		renderer.SetModel(context.Get<PrimitiveModelList>().GetModel(PrimitiveModelList::ID::Sphere));
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
		renderer.Draw(obj.GetMatrix(), view, proj);
	});
}
