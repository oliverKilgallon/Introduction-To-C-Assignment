#pragma once

#include "DeviceResources.h"
#include "SpriteResources.h"
#include "SimpleMath.h"
#include "States.h"
#include "Player.h"
#include "Entity.h"
class Troll : public Entity
{
public:
	Troll::Troll(std::wstring textureId,DirectX::SimpleMath::Vector2 offset, std::pair<int, int> columnRow, DirectX::SpriteEffects spriteEffects);
	~Troll();

public:
	void Update(double totalTime, double timeDelta, std::shared_ptr<Player> player);
	TrollStates GetState();
	void SetState(TrollStates state);
	
private:
	void Move(double timeDelta, const std::shared_ptr<Player> player);
	TrollStates moveState;
};

