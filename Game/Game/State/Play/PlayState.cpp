#include "PlayState.h"

#include "../../../Framework/Framework.h"
#include "Component/Components.h"

void PlayState::Initialize(GameContext& context)
{
	RegisterTexture(context);

	CreateCamera();
	CreateGameEntitys(context);
	CreateUI(context);

	CreateDebugItems(context);
}

void PlayState::Update(GameContext& context)
{
	//Transform* target = nullptr;
	// <プレイヤーを探してターゲットにする>
	/*m_registry.view<GameObject, PrimitiveRenderer>().each([&](auto entity, auto& obj, auto& renderer)
	{
		target = obj.GetTransform();
	});*/

	DebugFunction();

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
			renderer.Draw(obj.GetMatrix(), view, proj);
		}
	});

	DebugRender(context, cameraPos, view, proj);
}

void PlayState::CreateCamera()
{
	auto camera = m_registry.create();
	auto& obj = m_registry.assign<GameObject>(camera, &m_registry, camera);
	obj.GetTransform()->localPosition = DirectX::SimpleMath::Vector3(25.f, 15.f, -12.f);
	m_registry.assign<DebugCamera>(camera);
}

void PlayState::CreateGameEntitys(GameContext& context)
{
	{
		auto entity = m_registry.create();
		auto& generator = m_registry.assign<MapGenerator>(entity);
		generator.Initialize(context, &m_registry);
		generator.Generate();
		m_mapGenerator = entity;
	}
}

void PlayState::CreateUI(GameContext& context)
{
	auto entity = m_registry.create();
	m_registry.assign<FontRenderer>(entity);
	m_registry.assign<DirectX::SimpleMath::Vector2>(entity);
}

void PlayState::RegisterTexture(GameContext& context)
{
	auto& textureManager = context.Get<TextureManager>();
	textureManager.Register(context, L"Resources/Sprite/stationFloor.png", TextureID::Floor);
}

void PlayState::CreateDebugItems(GameContext& context)
{
	auto device = context.GetDR().GetD3DDevice();
	auto deviceContext = context.GetDR().GetD3DDeviceContext();
	{
		auto entity = m_registry.create();
		auto& obj = m_registry.assign<GameObject>(entity);
		obj.GetTransform()->localScale = DirectX::SimpleMath::Vector3(.5f, 2.f, .5f);
		obj.GetTransform()->localPosition = DirectX::SimpleMath::Vector3(0.f, 1.f, 0.f);
		auto& renderer = m_registry.assign<PrimitiveRenderer>(entity);
		renderer.SetModel(context.Get<PrimitiveModelList>().GetModel(PrimitiveModelList::ID::Cylinder));
		renderer.SetModelOption(DirectX::Colors::Red, true);
	}

	m_gridFloor = std::make_unique<GridFloor>(device, deviceContext, &context.Get<DirectX::CommonStates>(), 500, 500);
}

void PlayState::SwitchingDebug()
{
	if (isWireframe)isWireframe = false;
	else isWireframe = true;

	m_registry.view<PrimitiveRenderer>().each([&](auto entity, auto& renderer)
	{
		renderer.SetIsWireframe(isWireframe);
	});
}

void PlayState::DebugFunction()
{
	if (InputManager::GetKeyDown(DirectX::Keyboard::Keys::F1))
	{
		m_registry.get<MapGenerator>(m_mapGenerator).Plain();
	}
	if (InputManager::GetKeyDown(DirectX::Keyboard::Keys::F2))
	{
		m_registry.get<MapGenerator>(m_mapGenerator).Generate();
	}
	if (InputManager::GetKeyDown(DirectX::Keyboard::Keys::F3))
	{
		SwitchingDebug();
	}
}

void PlayState::DebugRender(GameContext& context, DirectX::SimpleMath::Vector3& cameraPos,
	const DirectX::SimpleMath::Matrix& view,
	const DirectX::SimpleMath::Matrix& proj)
{
	if (isWireframe)
	{
		m_gridFloor->draw(DirectX::SimpleMath::Matrix::Identity, view, proj);
	}
	m_registry.view<FontRenderer, DirectX::SimpleMath::Vector2>().each([&](auto entity, auto& renderer, auto& pos)
	{
		auto font = context.Get<FontManager>().GetSpriteFont("Meiryo UI");
		renderer.Draw(context, font, pos, DirectX::Colors::Red, "Camera : %.2f, %.2f", cameraPos.x, cameraPos.z);
	});
}
