#include "pch.h"
#include "GameOver.h"


GameOver::GameOver(std::shared_ptr<DX::DeviceResources> deviceResources)
{
	gameover_text = L"Game Over!";

	float width = (deviceResources->GetScreenViewport().Width / 2) - ( static_cast<float>( gameover_text.length() ) );
	float height = (deviceResources->GetScreenViewport().Height / 2) - 200.0f;

	DirectX::SimpleMath::Vector2 position(width, height);

	gameOverMessage = std::shared_ptr<TextWriter>(new TextWriter(gameover_text, position));
	buttonPrompt = std::shared_ptr<TextWriter>(new TextWriter(L"Press B to exit game", position + DirectX::SimpleMath::Vector2(0.0f, 200.0f)));
}


GameOver::~GameOver()
{
}

void GameOver::Update(std::shared_ptr<GameController> m_controller)
{
	if (m_controller->WasButtonReleaseDetected(XINPUT_GAMEPAD_B)) 
	{
		exit(EXIT_SUCCESS);
	}
}
void GameOver::Render(std::shared_ptr<SpriteResources> resources)
{
	gameOverMessage->Render(resources);
	buttonPrompt->Render(resources);
}
