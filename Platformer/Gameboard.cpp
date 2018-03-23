#include "pch.h"
#include "Gameboard.h"
#include <fstream>
#include <string>
#include <iostream>
Gameboard::Gameboard(std::shared_ptr<DX::DeviceResources> resources)
{
	this->boardColCount = 0;
	this->boardRowCount = 0;

	GenerateGameBoard(resources);
	for (unsigned int i = 0; i < trolls.size(); i++) {
		trolls[i]->SetBoardBounds(boardColCount, boardRowCount);
	}

	player->SetBoardBounds(boardColCount, boardRowCount);
	
	score_text = player->GetScore();

	score = std::shared_ptr<TextWriter>(new TextWriter(std::wstring(L"Score: " + score_text), DirectX::SimpleMath::Vector2(10.0f, 700.0f)));
}


Gameboard::~Gameboard()
{
}

const std::shared_ptr<Player> Gameboard::GetPlayer() 
{
	return player ? player : NULL;
}

int Gameboard::GetPickupsAmount() 
{
	return pickups.empty() ? 1 : pickups.size();
}
void Gameboard::GenerateGameBoard(std::shared_ptr<DX::DeviceResources> resources)
{
	// load in the file 
	std::ifstream myFile("Assets/LevelOne.csv");
	std::string rowStr;

	std::wstring imageFilePathName;
	bool isPlayerSpawned = false;
	DirectX::SimpleMath::Vector2 spawn;
	int rowCount = 0;
	int colCount = 0;
	// get the first line and store in the variable "line"
	while (std::getline(myFile, rowStr))
	{
		for (unsigned int col = 0; col < rowStr.size(); col++)
		{
			if (rowStr[col] != ',')
			{
				// set up the paramaters
				std::pair<int, int>colRow;
				float scale = 1.0f;

				switch (rowStr[col]) {
					case '0':
						imageFilePathName = L"Assets/TileEmpty.png";
						colRow.first = colCount;
						colRow.second = rowCount;
						colCount++;
						break;

					case '1':
						imageFilePathName = L"Assets/TilePlatform.png";
						colRow.first = colCount;
						colRow.second = rowCount;
						colCount++;
						break;

					case '2':
						//Tile Information
						imageFilePathName = L"Assets/TileEmpty.png";
						colRow.first = colCount;
						colRow.second = rowCount;

						//Troll information
						troll = std::shared_ptr<Troll>(new Troll(L"Assets/TrollWalkSide.png", DirectX::SimpleMath::Vector2(0.0f, 0.0f), 
							colRow, DirectX::SpriteEffects::SpriteEffects_None));

						trolls.push_back(troll);
						colCount++;
						break;

					case '3':
						//Tile Information
						imageFilePathName = L"Assets/TileEmpty.png";
						colRow.first = colCount;
						colRow.second = rowCount;

						//Player Information
						if (!isPlayerSpawned) {
							player = std::shared_ptr<Player>(new Player(L"Assets/PlayerIdleStance.png", DirectX::SimpleMath::Vector2(0, 0), colRow));
							isPlayerSpawned = true;
						}
						colCount++;
						break;

					case '4':
						//Tile information
						imageFilePathName = L"Assets/TileEmpty.png";
						colRow.first = colCount;
						colRow.second = rowCount;
						
						//Troll information
						troll = std::shared_ptr<Troll>(new Troll(L"Assets/TrollWalkSide.png", DirectX::SimpleMath::Vector2(0.0f, 0.0f), 
							colRow, DirectX::SpriteEffects::SpriteEffects_FlipHorizontally));

						trolls.push_back(troll);
						colCount++;
						break;
					case '5':
						//Collidable tile info
						imageFilePathName = L"Assets/TilePlatform.png";
						colRow.first = colCount;
						colRow.second = rowCount;
						collidable.push_back(
							std::make_shared<Tile>(
								imageFilePathName,
								DirectX::SimpleMath::Vector2(0.0f, 0.0f),
								colRow,
								scale)
						);
						colCount++;
						break;
					case '6':
						//Tile info for the pickup
						imageFilePathName = L"Assets/TileEmpty.png";
						colRow.first = colCount;
						colRow.second = rowCount;

						pickup = std::shared_ptr<Pickup>(new Pickup(L"Assets/Pickup.png", DirectX::SimpleMath::Vector2(0.0f, 0.0f), colRow));
						pickups.push_back(pickup);
						colCount++;
					default:
						break;
				}
				
				gameboard.push_back(
					std::make_shared<Tile>(
						imageFilePathName,
						DirectX::SimpleMath::Vector2(0.0f, 0.0f),
						colRow,
						scale)
				);
			}
		}
		boardColCount = colCount;
		colCount = 0;
		rowCount++;
	}
	boardRowCount = rowCount;
	myFile.close();
}

void Gameboard::Update(double totalTime, double timeDelta, std::shared_ptr<GameController> m_controller)
{
	for (unsigned int i = 0; i < trolls.size(); i++) {
		trolls[i]->Update(totalTime, timeDelta, player);
	}

	player->Update(totalTime, timeDelta, m_controller, collidable);

	for (unsigned int i = 0; i < pickups.size(); i++)
	{
		if (!pickups[i]->IsCaught()) 
		{
			pickups[i]->Update(player);
		}
	}

	score_text = std::to_wstring(player->GetScore());
	score->Update(L"Score: " + score_text);
}

void Gameboard::Render(std::shared_ptr<SpriteResources> spriteResources)
{	
	for (unsigned int i = 0; i < gameboard.size(); i++)
	{
		this->gameboard[i]->Render(spriteResources);
	}

	for (unsigned int i = 0; i < pickups.size(); i++)
	{
		if (!pickups[i]->IsCaught())
		{
			this->pickups[i]->Render(spriteResources);
		}
	}

	for (unsigned int i = 0; i < trolls.size(); i++) {
		trolls[i]->Render(spriteResources);
	}

	this->player->Render(spriteResources);
	this->score->Render(spriteResources);
}

