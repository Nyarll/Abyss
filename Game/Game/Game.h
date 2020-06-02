//
// Game.h
//

#pragma once

#include "../Framework/Context/GameContext.h"

#include "../Common/DeviceResources.h"
#include "../Common/StepTimer.h"


// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game : public DX::IDeviceNotify, public GameContext
{
public:

    Game() noexcept(false);

    // Initialization and management
    void Initialize(HWND window, int width, int height);

    // Basic game loop
    void Tick();

    // IDeviceNotify
    virtual void OnDeviceLost() override;
    virtual void OnDeviceRestored() override;

    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowMoved();
    void OnWindowSizeChanged(int width, int height);

    // Properties
    void GetDefaultSize( int& width, int& height ) const;

	const LPCWCHAR GetWindowTitle();
	const LPCWCHAR GetWindowClass();

private:

    void Update(DX::StepTimer const& timer);
    void Render();

    void Clear();

    void CreateDeviceDependentResources();
    void CreateWindowSizeDependentResources();

	void RegisterTexture();
	void RegisterState();
	void RegisterFont();

    // Device resources.
    DX::DeviceResources*    m_deviceResources;

    // Rendering loop timer.
    DX::StepTimer*			m_timer;
};