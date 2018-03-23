#pragma once
#include "DeviceResources.h"
#include "SpriteResources.h"
#include "TextWriter.h"
#include "GameController.h"
#include <vector>
class GameOver
{
public:
	GameOver(std::shared_ptr<DX::DeviceResources> deviceResources);
	~GameOver();

	void Render(std::shared_ptr<SpriteResources> spriteResources);
	void Update(std::shared_ptr<GameController> m_controller);

private:
	std::shared_ptr<TextWriter> gameOverMessage;
	std::shared_ptr<TextWriter> buttonPrompt;
	std::wstring gameover_text;
};

