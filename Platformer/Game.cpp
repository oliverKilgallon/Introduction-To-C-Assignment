//
// Game.cpp
//

#include "pch.h"
#include "Game.h"

using namespace DirectX;

using Microsoft::WRL::ComPtr;

Game::Game()
{
    m_deviceResources = std::make_shared<DX::DeviceResources>();
    m_deviceResources->RegisterDeviceNotify(this);
}

// Initialize the Direct3D resources required to run.
void Game::Initialize(HWND window, int width, int height)
{
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

	m_spriteResources = std::make_shared<SpriteResources>(m_deviceResources);

	m_spriteResources->LoadTexture(L"Assets/TrollWalkSide.png");
	m_spriteResources->LoadTexture(L"Assets/TileEmpty.png");
	m_spriteResources->LoadTexture(L"Assets/TilePlatform.png");
	m_spriteResources->LoadTexture(L"Assets/PlayerIdleStance.png");
	m_spriteResources->LoadTexture(L"Assets/PlayerWalkSide.png");
	m_spriteResources->LoadTexture(L"Assets/Pickup.png");

	m_gameState = GameStates::Menu_State;

	m_gameboard = std::make_shared<Gameboard>(m_deviceResources);
	m_menu = std::make_shared<Menu>(m_deviceResources);
	m_controller = std::make_shared<GameController>();
	m_gameover = std::make_shared<GameOver>(m_deviceResources);
}

#pragma region Frame Update
// Executes the basic game loop.
void Game::Tick()
{
    m_timer.Tick([&]()
    {
        Update(m_timer);
    });

    Render();
}

// Updates the world.
void Game::Update(DX::StepTimer const& timer)
{
    float elapsedTime = float(timer.GetElapsedSeconds());
	
	m_controller->Update();

	if (m_gameState == GameStates::Menu_State) 
	{
		m_gameState = m_menu->Update(m_controller);
	}

	else if (m_gameState == GameStates::GameOver_State) 
	{
		m_gameover->Update(m_controller);
	}

	else if (m_gameState == GameStates::Playing_State)
	{
		if (m_controller->WasButtonReleaseDetected(XINPUT_GAMEPAD_B)) 
		{
			m_gameState = GameStates::Menu_State;
		}

		else if (m_gameboard->GetPlayer()->IsDead() || m_gameboard->GetPlayer()->GetScore() == (5 * m_gameboard->GetPickupsAmount()))
		{
			m_gameState = GameStates::GameOver_State;
		}

		else 
		{
			m_gameboard->Update(timer.GetTotalSeconds(), timer.GetElapsedSeconds(), m_controller);
		}
	}
	
    elapsedTime;
}
#pragma endregion

#pragma region Frame Render
// Draws the scene.
void Game::Render()
{
    // Don't try to render anything before the first Update.
    if (m_timer.GetFrameCount() == 0)
    {
        return;
    }

    Clear();

    m_deviceResources->PIXBeginEvent(L"Render");
    auto context = m_deviceResources->GetD3DDeviceContext();

    // TODO: Add your rendering code here.
	m_spriteResources->GetSpriteBatch()->Begin(DirectX::SpriteSortMode_Deferred, m_spriteResources->GetCommonStates()->NonPremultiplied());


	if (m_gameState == GameStates::Menu_State) 
	{
		m_menu->Render(m_spriteResources);
	}
	else if (m_gameState == GameStates::Playing_State) 
	{
		m_gameboard->Render(m_spriteResources);
	}
	else
	{
		m_gameover->Render(m_spriteResources);
	}

	m_spriteResources->GetSpriteBatch()->End();

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
    m_timer.ResetElapsedTime();

    // TODO: Game is being power-resumed (or returning from minimize).
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
    width = 800;
    height = 600;
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
