#include "pch.h"
#include "Troll.h"
#include "Entity.h"


Troll::Troll(std::wstring textureId, DirectX::SimpleMath::Vector2 offset, std::pair<int, int> columnRow, DirectX::SpriteEffects spriteEffects)
	: Entity(textureId, offset, columnRow)
{
	this->SetSpriteEffect(spriteEffects);
	this->SetVelocity(DirectX::SimpleMath::Vector2(this->GetSpriteEffect() == DirectX::SpriteEffects::SpriteEffects_None ? 64.0f: -64.0f, 0.0f));
	//this->SetState(this->GetSpriteEffect() == DirectX::SpriteEffects::SpriteEffects_None ? this->moveState = TrollState::LeftToRight : this->moveState = TrollState::RightToLeft);
}


Troll::~Troll()
{
}

TrollStates Troll::GetState() 
{
	return moveState;
}

void Troll::SetState(TrollStates state) 
{
	this->moveState = state;
}

double lastTime = 0;

void Troll::Update(double totalTime, double timeDelta, const std::shared_ptr<Player> player) 
{
	//Reset bounding box and animate sprite
	this->SetAABB(this->GetPosition());
	this->Animate(totalTime);

	//Swap sprite effects to turn around depending on velocity
	if (this->GetVelocity().x > 0) 
	{
		this->SetSpriteEffect(DirectX::SpriteEffects::SpriteEffects_None);
	}
	else 
	{
		this->SetSpriteEffect(DirectX::SpriteEffects::SpriteEffects_FlipHorizontally);
	}
	Move(timeDelta, player);
}

void Troll::Move(double timeDelta, const std::shared_ptr<Player> player)
{
	//Set how much to move and what the new position is
	DirectX::SimpleMath::Vector2 distanceToMove = static_cast<float>(timeDelta)* this->GetVelocity();
	DirectX::SimpleMath::Vector2 newPosition = this->GetPosition() + distanceToMove;

	//Set world bounds
	float leftWall = this->GetBoardOffset().x + ((this->GetBoardColCount() - this->GetBoardColCount()) * this->GetWidth());
	float rightWall = this->GetBoardOffset().x + ((this->GetBoardColCount() - 1) * this->GetWidth());

	//Check for collision with player
	float posX = this->GetPosition().x;
	float playerX = player->GetPosition().x;

	if (this->GetAABB().DoesIntersect(player->GetAABB())) 
	{
		if (posX > playerX && this->GetSpriteEffect() == DirectX::SpriteEffects::SpriteEffects_FlipHorizontally) 
		{
			
			this->SetVelocity(DirectX::SimpleMath::Vector2(this->GetVelocity().x * -1.0f, this->GetVelocity().y));
		}
		else if (posX < playerX && this->GetSpriteEffect() == DirectX::SpriteEffects::SpriteEffects_None) 
		{
			this->SetVelocity(DirectX::SimpleMath::Vector2(this->GetVelocity().x * -1.0f, this->GetVelocity().y));

		}
		player->KillPlayer();
	}
	
	//Flip if troll hits the wall
	if (newPosition.x >= rightWall) 
	{
		this->SetVelocity(DirectX::SimpleMath::Vector2(this->GetVelocity().x * -1.0f, this->GetVelocity().y));
	}
	else if (newPosition.x <= leftWall) 
	{
		this->SetVelocity(DirectX::SimpleMath::Vector2(this->GetVelocity().x * -1.0f, this->GetVelocity().y));
	}
	this->SetPosition(newPosition);
}