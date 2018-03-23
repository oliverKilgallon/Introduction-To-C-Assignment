#include "pch.h"
#include "Tile.h"


Tile::Tile(std::wstring textureId,DirectX::SimpleMath::Vector2 offset,std::pair<int, int> columnRow, float scale) 
	: textureWidth {64}
	, textureHeight {64}
	, scale {scale}
	, boardOffset{ offset }
	, spritePosition { this->boardOffset + DirectX::SimpleMath::Vector2(columnRow.first * (this->textureWidth * scale), columnRow.second * (this->textureHeight * scale)) }
	, aabb { DirectX::SimpleMath::Vector2(spritePosition.x + (textureWidth / 2), spritePosition.y + (textureHeight / 2)), DirectX::SimpleMath::Vector2(20.0f, 20.0f) }
	, textureId { textureId }
	, columnRow { columnRow }
{

	this->spritePosition = DirectX::SimpleMath::Vector2(this->boardOffset + DirectX::SimpleMath::Vector2(columnRow.first * (this->textureWidth * scale), columnRow.second * (this->textureHeight * scale)));
	spriteTint = DirectX::Colors::White.v;
	aabb.SetAABB(this->spritePosition - DirectX::SimpleMath::Vector2(this->textureWidth / 2, this->textureHeight / 2));

	this->spriteSourceRectangle = std::unique_ptr<RECT>(new RECT());
	this->spriteSourceRectangle->left = 0;
	this->spriteSourceRectangle->top = 0;
	this->spriteSourceRectangle->right = static_cast<LONG>(textureWidth);
	this->spriteSourceRectangle->bottom = static_cast<LONG>(textureHeight);
}


Tile::~Tile()
{
}

void Tile::Update()
{
}

void Tile::Render(const std::shared_ptr<SpriteResources>& spriteResources)
{
	//Get the DirectX::SpriteBatch from the SpriteResources object
	spriteResources->GetSpriteBatch()->Draw(
		spriteResources->GetTexture(this->textureId).Get(),
		this->spritePosition,
		this->spriteSourceRectangle.get(),  //Need the raw C++ pointer
		this->spriteTint,
		0,  //Angle of rotation in radians
		DirectX::SimpleMath::Vector2(0, 0), //Origin for the rotation
		this->scale, //Scale factor
		DirectX::SpriteEffects_None, //Reflections about the horizontal and verticle axes
		0.0f  //Layer depth; not required as we use DirectX::SpriteSortMode_Deferred
		);
}

TileState Tile::GetState()
{
	return this->state;
}

CollisionBox Tile::GetAABB() {
	return aabb;
}