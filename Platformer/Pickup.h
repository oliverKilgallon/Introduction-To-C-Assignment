#pragma once

#include "DeviceResources.h"
#include "SpriteResources.h"
#include "SimpleMath.h"
#include "Entity.h"
#include "Player.h"

class Pickup : public Entity
{
public:
	Pickup(std::wstring textureId, DirectX::SimpleMath::Vector2 offset, std::pair<int, int> columnRow);
	~Pickup();
public:
	bool IsCaught();
	void Update(std::shared_ptr<Player> player);
private:
	bool caught;
	void checkForPlayer(const std::shared_ptr<Player> player);
};

