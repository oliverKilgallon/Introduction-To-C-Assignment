#include "pch.h"
#include "Player.h"

Player::Player(std::wstring textureId,DirectX::SimpleMath::Vector2 offset, std::pair<int, int> columnRow)
	: Entity(textureId, offset, columnRow)
{
	//this->SetDirectionState(DirectionStates::Right);
	this->isDead = false;
	this->score = 0;
}


Player::~Player()
{
}

bool Player::IsDead() 
{
	return this->isDead;
}

int Player::GetScore() 
{
	return this->score;
}

void Player::SetScore(int newScore) 
{
	this->score = newScore;
}

DirectionStates Player::GetDirectionState()
{
	return this->direction;
}

void Player::SetDirectionState(DirectionStates newState)
{
	this->direction = newState;
}

void Player::Update(double totalTime, double timeDelta, std::shared_ptr<GameController> m_controller, std::vector<std::shared_ptr<Tile>> collidable)
{
	CheckCollison(collidable);
	Move(timeDelta, m_controller);
	this->Animate(totalTime);
	this->SetAABB(this->GetPosition() - DirectX::SimpleMath::Vector2(this->GetWidth() / 2, this->GetHeight() / 2));

}

void Player::CheckCollison(std::vector<std::shared_ptr<Tile>> collidable) 
{
	for (unsigned int i = 0; i < collidable.size(); i++) {
		if (this->GetAABB().DoesIntersect(collidable[i]->GetAABB())) 
		{
			this->SetVelocity(DirectX::SimpleMath::Vector2(0.0f, 0.0f));
			this->StopPlayer(this->GetDirectionState());
		}
	}
}

void Player::KillPlayer() {
	this->SetTint(DirectX::Colors::Red.v);
	this->isDead = true;
}

void Player::Move(double timeDelta, std::shared_ptr<GameController> m_controller)
{
	float boardBoundsUY = this->GetBoardOffset().y;
	float boardBoundsLX = this->GetBoardOffset().x;
	float boardBoundsRX = this->GetBoardOffset().x + ((this->GetBoardColCount() - 1) * this->GetWidth());
	float boardBoundsDY = this->GetBoardOffset().y + (this->GetBoardRowCount() * 32);

	if (m_controller->IsButtonDown(XINPUT_GAMEPAD_DPAD_LEFT)) 
	{
		if (!((this->GetPosition().x - 32) < boardBoundsLX)) 
		{
			this->SetVelocity(DirectX::SimpleMath::Vector2(-64.0f, 0.0f));
			this->SetDirectionState(DirectionStates::Left);
		}
	}

	else if (m_controller->IsButtonDown(XINPUT_GAMEPAD_DPAD_RIGHT)) 
	{
		if (!((this->GetPosition().x + 32) > boardBoundsRX)) 
		{
			this->SetVelocity(DirectX::SimpleMath::Vector2(64, 0));
			this->SetDirectionState(DirectionStates::Right);
		}
	}

	else if (m_controller->IsButtonDown(XINPUT_GAMEPAD_DPAD_UP)) 
	{
		if (!((this->GetPosition().y - 32) < boardBoundsUY)) 
		{
			this->SetVelocity(DirectX::SimpleMath::Vector2(0, -64));
			this->SetDirectionState(DirectionStates::Up);
			}
	}

	else if (m_controller->IsButtonDown(XINPUT_GAMEPAD_DPAD_DOWN)) 
	{
		if ((this->GetPosition().y + 32) <= boardBoundsDY) 
		{
			this->SetVelocity(DirectX::SimpleMath::Vector2(0, 64));
			this->SetDirectionState(DirectionStates::Down);
		}
	}
	else 
	{
		this->SetVelocity(DirectX::SimpleMath::Vector2(0.0f,0.0f));
	}

	DirectX::SimpleMath::Vector2 distanceToMove = static_cast<float>(timeDelta)* this->GetVelocity();
	DirectX::SimpleMath::Vector2 newPosition = this->GetPosition() + distanceToMove;
	this->SetPosition(newPosition);

}

//Displace player and set their velocity accordingly if they hit a tile in a certain direction
void Player::StopPlayer(DirectionStates state) 
{
	switch (state) {
	case DirectionStates::Right:
		this->SetPosition(DirectX::SimpleMath::Vector2(this->GetPosition().x - 1, this->GetPosition().y));
		this->SetVelocity(DirectX::SimpleMath::Vector2(0.0f, this->GetVelocity().y));
		break;
	case DirectionStates::Left:
		this->SetPosition(DirectX::SimpleMath::Vector2(this->GetPosition().x + 1, this->GetPosition().y));
		this->SetVelocity(DirectX::SimpleMath::Vector2(0.0f, this->GetVelocity().y));
		break;
	case DirectionStates::Down:
		this->SetPosition(DirectX::SimpleMath::Vector2(this->GetPosition().x, this->GetPosition().y - 1));
		this->SetVelocity(DirectX::SimpleMath::Vector2(this->GetVelocity().x, 0.0f));
		break;
	case DirectionStates::Up:
		this->SetPosition(DirectX::SimpleMath::Vector2(this->GetPosition().x, this->GetPosition().y + 1));
		this->SetVelocity(DirectX::SimpleMath::Vector2(this->GetVelocity().x, 0.0f));
		break;
	default:
		break;
	}
}
