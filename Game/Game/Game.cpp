//
// Game.cpp
//

#include "Game.h"

#include "State\StateManager.h"
#include "State\States.h"

#include "../Framework/Texture/TextureManager.h"
#include "../Framework/GameFont/FontManager.h"

#include "../Framework/System/System.h"

extern void ExitGame();

using namespace DirectX;

using Microsoft::WRL::ComPtr;

Game::Game() noexcept(false)
{
	Register(std::make_unique<DX::StepTimer>());

	Register(std::make_unique<DX::DeviceResources>());
	m_deviceResources = &Get<DX::DeviceResources>();
	m_deviceResources->RegisterDeviceNotify(this);
}

// Initialize the Direct3D resources required to run.
void Game::Initialize(HWND window, int width, int height)
{
	System::SetWindowSize(DirectX::SimpleMath::Vector2((float)width, (float)height));

	Register(std::make_unique<DirectX::Mouse>());
	Get<DirectX::Mouse>().SetWindow(window);
	Register(std::make_unique<DirectX::Mouse::ButtonStateTracker>());
	Register(std::make_unique<DirectX::Keyboard>());

	m_deviceResources->SetWindow(window, width, height);

	m_deviceResources->CreateDeviceResources();
	CreateDeviceDependentResources();

	m_deviceResources->CreateWindowSizeDependentResources();
	CreateWindowSizeDependentResources();

	// TODO: Change the timer settings if you want something other than the default variable timestep mode.
	// e.g. for 60 FPS fixed timestep update logic, call:
	/*
	m_timer.SetFixedTimeStep(true);
	m_timer.SetTargetElapsedSeconds(1.0 / 60);
	*/

	auto device = m_deviceResources->GetD3DDevice();
	auto context = m_deviceResources->GetD3DDeviceContext();

	// <コモンステートの作成>
	Register(std::make_unique<CommonStates>(device));
	// <スプライトバッチ作成>
	Register(std::make_unique<DirectX::SpriteBatch>(context));

	RegisterTexture();
	RegisterState();
	RegisterFont();
}

#pragma region Frame Update
// Executes the basic game loop.
void Game::Tick()
{
	auto& timer = Get<DX::StepTimer>();
	timer.Tick([&]()
	{
		Get<DirectX::Keyboard>().GetState();
		Get<DirectX::Mouse::ButtonStateTracker>().Update(Get<DirectX::Mouse>().GetState());
		Update(timer);
	});

	Render();
}

// Updates the world.
void Game::Update(DX::StepTimer const& timer)
{
	float elapsedTime = float(timer.GetElapsedSeconds());

	// TODO: Add your game logic here.
	elapsedTime;

	if (Get<DirectX::Keyboard>().GetState().Escape)
	{
		ExitGame();
	}

	Get<StateManager>().UpdateActiveState(*this);
}
#pragma endregion

#pragma region Frame Render
// Draws the scene.
void Game::Render()
{
	auto& timer = Get<DX::StepTimer>();
	// Don't try to render anything before the first Update.
	if (timer.GetFrameCount() == 0)
	{
		return;
	}

	Clear();

	m_deviceResources->PIXBeginEvent(L"Render");

	Get<StateManager>().RenderActiveState(*this);

	m_deviceResources->PIXEndEvent();

	// Show the new frame.
	m_deviceResources->Present();
}

// Helper method to clear the back buffers.
void Game::Clear()
{
	m_deviceResources->PIXBeginEvent(L"Clear");

	// Clear the views.
	auto context = m_deviceResources->GetD3DDeviceContext();
	auto renderTarget = m_deviceResources->GetRenderTargetView();
	auto depthStencil = m_deviceResources->GetDepthStencilView();

	context->ClearRenderTargetView(renderTarget, Colors::CornflowerBlue);
	context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	context->OMSetRenderTargets(1, &renderTarget, depthStencil);

	// Set the viewport.
	auto viewport = m_deviceResources->GetScreenViewport();
	context->RSSetViewports(1, &viewport);

	m_deviceResources->PIXEndEvent();
}
#pragma endregion

#pragma region Message Handlers
// Message handlers
void Game::OnActivated()
{
	// TODO: Game is becoming active window.
}

void Game::OnDeactivated()
{
	// TODO: Game is becoming background window.
}

void Game::OnSuspending()
{
	// TODO: Game is being power-suspended (or minimized).
}

void Game::OnResuming()
{
	auto& timer = Get<DX::StepTimer>();
	timer.ResetElapsedTime();

	// TODO: Game is being power-resumed (or returning from minimize).
}

void Game::OnWindowMoved()
{
	auto r = m_deviceResources->GetOutputSize();
	m_deviceResources->WindowSizeChanged(r.right, r.bottom);
}

void Game::OnWindowSizeChanged(int width, int height)
{
	if (!m_deviceResources->WindowSizeChanged(width, height))
		return;

	CreateWindowSizeDependentResources();

	// TODO: Game window is being resized.
}

// Properties
void Game::GetDefaultSize(int& width, int& height) const
{
	// TODO: Change to desired default window size (note minimum size is 320x200).
	width = 1280;
	height = 720;
}
const LPCWCHAR Game::GetWindowTitle()
{
	return L"Abyss";
}
const LPCWCHAR Game::GetWindowClass()
{
	return L"AbyssWindowClass";
}
#pragma endregion

#pragma region Direct3D Resources
// These are the resources that depend on the device.
void Game::CreateDeviceDependentResources()
{
	auto device = m_deviceResources->GetD3DDevice();

	// TODO: Initialize device dependent objects here (independent of window size).
	device;
}

// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateWindowSizeDependentResources()
{
	// TODO: Initialize windows-size dependent objects here.
}

void Game::RegisterTexture()
{
	Register(std::make_unique<TextureManager>());
	auto& manager = Get<TextureManager>();

	manager.Register(*this, L"Resources/Sprite/titleLogo.png", TextureID::Logo);
}

void Game::RegisterState()
{
	Register(std::make_unique<StateManager>());
	auto& manager = Get<StateManager>();

	//manager.Register(StateManager::StateID::PLAY, ...);
	manager.Register(StateManager::StateID::TITLE, TitleState::Create);

	manager.SetStartState(*this, StateManager::StateID::TITLE);
}

void Game::RegisterFont()
{
	Register(std::make_unique<FontManager>());
	auto& manager = Get<FontManager>();

	manager.Register(*this, L"Resources/Font/meiryo.spritefont", "Meiryo UI");
}

void Game::OnDeviceLost()
{
	// TODO: Add Direct3D resource cleanup here.
}

void Game::OnDeviceRestored()
{
	CreateDeviceDependentResources();

	CreateWindowSizeDependentResources();
}
#pragma endregion
