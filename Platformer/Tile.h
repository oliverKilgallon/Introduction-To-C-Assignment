#pragma once
#include <SimpleMath.h>
#include <string>
#include "DeviceResources.h"
#include "SpriteResources.h"
#include "CollisionBox.h"

///<summary>Indicates what sort of tile this is.</summary>
///<remarks>
///For this simple demo a tile has two possible states: empty, so is is neither 
///rendered nor updated; or it is a platform, so is rendered but not updated.  
///In a more complex game a tile may change state, e.g. to show a collectible.
///</remarks>
enum class TileState
{
	Empty,
	Platform
};

class Tile
{
public:
	Tile(std::wstring textureId,
		DirectX::SimpleMath::Vector2 offset,
		std::pair<int, int> columnRow,
		float scale);
	~Tile();

public:
	void Update();
	void Render(const std::shared_ptr<SpriteResources>& spriteResources);
	TileState GetState();
	CollisionBox GetAABB();

private:
	std::wstring textureId;
	DirectX::SimpleMath::Color spriteTint;
	//The *order of declaration* determines the *order of initialization* in the 
	//constructor initialization list.  Since spritePosition will depend on the 
	//offset of the board and the row and column the Tile is on it must be declared 
	//after these, or initialized in the constructor body.  We'll initialise it 
	//in the constructor body.
	DirectX::SimpleMath::Vector2 spritePosition;
	std::unique_ptr<RECT> spriteSourceRectangle;
	float textureHeight;
	float textureWidth;
	DirectX::SimpleMath::Vector2 boardOffset;
	float scale;
	std::pair<int, int> columnRow;
	TileState state;
	CollisionBox aabb;
};

