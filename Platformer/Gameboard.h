#pragma once
#include "Tile.h"
#include <vector>
#include "Troll.h"
#include "Player.h"
#include "Pickup.h"
#include "States.h"
#include "TextWriter.h"
class Gameboard
{
public:
	Gameboard(std::shared_ptr<DX::DeviceResources> resources);
	~Gameboard();

private:
	std::vector<std::shared_ptr<Tile>> gameboard;
	std::vector<std::shared_ptr<Tile>> collidable;
	std::vector<std::shared_ptr<Troll>> trolls;
	std::vector<std::shared_ptr<Pickup>> pickups;
	std::wstring score_text;

public:
	void Update(double totalTime, double timeDelta, std::shared_ptr<GameController> m_controller);
	void Render(std::shared_ptr<SpriteResources> spriteResources);
	int GetPickupsAmount();
	const std::shared_ptr<Player> GetPlayer();

private:
	void GenerateGameBoard(std::shared_ptr<DX::DeviceResources> resources);
	std::shared_ptr<Troll> troll;
	std::shared_ptr<Player> player;
	std::shared_ptr<Pickup> pickup;
	int boardColCount;
	int boardRowCount;
	std::shared_ptr<TextWriter> score;
};

