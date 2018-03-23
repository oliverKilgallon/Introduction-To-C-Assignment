#pragma once

#include "DeviceResources.h"
#include "SpriteResources.h"
#include "SimpleMath.h"
#include "Entity.h"
#include "GameController.h"
#include "States.h"
#include "Tile.h"
#include <vector>
#include <Math.h>
class Player : public Entity
{
public:
	Player::Player(std::wstring textureId, DirectX::SimpleMath::Vector2 offset, std::pair<int, int> columnRow);
	~Player();

private:
	bool isMoving;
	bool isDead;
	int score;

public:
	void Update(double totalTime, double timeDelta, std::shared_ptr<GameController> m_controller, std::vector<std::shared_ptr<Tile>> collidable);
	DirectionStates GetDirectionState();
	void SetDirectionState(DirectionStates newState);
	void KillPlayer();
	bool IsDead();
	int GetScore();
	void SetScore(int newScore);

private:
	void Move(double timeDelta, std::shared_ptr<GameController> m_controller);
	void StopPlayer(DirectionStates state);
	void CheckCollison(std::vector<std::shared_ptr<Tile>> collidable);
	bool stopping;
	DirectionStates direction;
};

