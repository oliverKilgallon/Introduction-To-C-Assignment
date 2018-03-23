#pragma once
#include "DeviceResources.h"
#include "SpriteResources.h"
#include "SimpleMath.h"
#include "CollisionBox.h"
class Entity
{
public:
	Entity(std::wstring textureId, DirectX::SimpleMath::Vector2 offset, std::pair<int, int> columnRow);
	~Entity();
private:
	std::wstring textureId;
	DirectX::SimpleMath::Vector2 position;
	DirectX::SimpleMath::Vector2 velocity;
	DirectX::SimpleMath::Vector2 boardOffset;

	// for animation
	RECT sourceRectangle;
	double lastFrameChange;
	double animationRate;
	int height;
	int width;
	int frameCount;
	int frame;
	int boardColumnCount;
	int boardRowCount;
	DirectX::SimpleMath::Color tint;
	DirectX::SpriteEffects spriteEffect;
	int timeToFlash;

	CollisionBox aabb;
public:
	void Update(double totalTime, double timeDelta);
	void Render(std::shared_ptr<SpriteResources> resources);
	void FlashColors(DirectX::SimpleMath::Color tint1, DirectX::SimpleMath::Color tint2, int timeToFlash, double totalTime);


	//Mutators
	void SetVelocity(DirectX::SimpleMath::Vector2 newVel);
	void SetPosition(DirectX::SimpleMath::Vector2 newPos);
	void SetBoardOffset(DirectX::SimpleMath::Vector2 boardOffset);
	void SetHeight(int newHeight);
	void SetWidth(int newWidth);
	void SetBoardBounds(int columns, int rows);
	void SetSpriteEffect(DirectX::SpriteEffects newSpriteEffects);
	void SetAABB(DirectX::SimpleMath::Vector2);
	void Animate(double totalTime);
	void SetTint(DirectX::SimpleMath::Color tint);
	void SetTimeToFlash(int time);

	//Accessors
	DirectX::SimpleMath::Vector2 GetPosition();
	DirectX::SimpleMath::Vector2 GetVelocity();
	DirectX::SimpleMath::Vector2 GetBoardOffset();
	DirectX::SimpleMath::Color GetTint();
	int GetHeight();
	int GetWidth();
	int GetBoardColCount();
	int GetBoardRowCount();
	DirectX::SpriteEffects GetSpriteEffect();
	CollisionBox GetAABB();
	virtual void Move(double timeDelta);
	int GetTimeToFlash();
	
};

