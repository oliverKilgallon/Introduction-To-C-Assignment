#include "pch.h"
#include "Pickup.h"
#include "Entity.h"


Pickup::Pickup(std::wstring textureId, DirectX::SimpleMath::Vector2 offset, std::pair<int, int> columnRow)
	: Entity(textureId, offset, columnRow)
{
	this->SetAABB(this->GetPosition() - DirectX::SimpleMath::Vector2(this->GetWidth() / 2, this->GetHeight() / 2));
	caught = false;
}


Pickup::~Pickup()
{
}

void Pickup::Update(std::shared_ptr<Player> player)
{
	checkForPlayer(player);
}

void Pickup::checkForPlayer(const std::shared_ptr<Player> player) 
{
	if (this->GetAABB().DoesIntersect(player->GetAABB())) 
	{
		caught = true;
		player->SetScore(player->GetScore() + 5);
	}
}

bool Pickup::IsCaught() 
{
	return caught;
}
