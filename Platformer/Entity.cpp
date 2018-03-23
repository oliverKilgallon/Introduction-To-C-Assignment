#include "pch.h"
#include "Entity.h"


Entity::Entity(std::wstring textureId, DirectX::SimpleMath::Vector2 offset, std::pair<int, int> columnRow)
	: width {64}
	, height{64}
	, position{ offset + DirectX::SimpleMath::Vector2(static_cast<float>(columnRow.first * this->width), static_cast<float>(columnRow.second * this->height)) }
	, aabb{ DirectX::SimpleMath::Vector2(position.x + (this->width / 2), position.y + (this->height / 2)), DirectX::SimpleMath::Vector2(31.0f, 31.0f) }
{
	this->boardOffset = DirectX::SimpleMath::Vector2(0,0);
	this->boardRowCount = 0;
	this->boardColumnCount = 0;

	this->frameCount = 6;
	this->frame = 0;
	this->lastFrameChange = 0.0;
	this->animationRate = 1.0 / 6.0;

	//Initial source rectangle defines the first frame of the sprite sheet
	this->sourceRectangle.left = 0L;
	this->sourceRectangle.top = 0L;
	this->sourceRectangle.right = static_cast<LONG>(this->width);
	this->sourceRectangle.bottom = static_cast<LONG>(this->height);

	this->width = 64;
	this->height = 64;
	this->position = offset + DirectX::SimpleMath::Vector2(static_cast<float>(columnRow.first * this->width), static_cast<float>(columnRow.second * this->height));
	this->tint = DirectX::Colors::White.v;
	
	this->spriteEffect = DirectX::SpriteEffects::SpriteEffects_None;
	this->velocity = DirectX::SimpleMath::Vector2(0.0f);

	aabb.SetAABB(this->position);
	this->textureId = textureId;


	
}


Entity::~Entity()
{
}

void Entity::Update(double totalTime, double timeDelta)
{
	this->aabb.SetAABB(this->position);
	this->Animate(totalTime);
	this->Move(timeDelta);
}

void Entity::Move(double timeDelta)
{
}

void Entity::Animate(double totalTime)
{
	if (totalTime >= this->lastFrameChange + this->animationRate)
	{
		//Time to show the next frame
		this->frame = this->frame + 1;

		//Check whether we have gone past the last frame
		if (this->frame >= this->frameCount)
		{
			this->frame = 0;
		}

		this->sourceRectangle.left = this->frame * this->width;
		this->sourceRectangle.top = 0L;
		this->sourceRectangle.right = sourceRectangle.left + this->width;
		this->sourceRectangle.bottom = this->height;

		//Record the time when we changed the frame
		this->lastFrameChange = totalTime;
	}
}

void Entity::Render(std::shared_ptr<SpriteResources> spriteResources)
{
	//Get the DirectX::SpriteBatch from the SpriteResources object
//	spriteResources->GetSpriteBatch()->Draw(
//		spriteResources->GetTexture(this->textureId).Get(),
//		this->position,
//		&sourceRectangle,  //Need the raw C++ pointer
//		this->tint,
//		0,  //Angle of rotation in radians
//		DirectX::SimpleMath::Vector2(0, 0), //Origin for the rotation
//		1.0f, //Scale factor
//		this->spriteEffect, //Reflections about the horizontal and verticle axes
//		0.0f  //Layer depth; not required as we use DirectX::SpriteSortMode_Deferred
//	);

	spriteResources->GetSpriteBatch()->Draw(
		spriteResources->GetTexture(this->textureId).Get(),
		this->position,
		&sourceRectangle,
		this->tint,
		0,
		DirectX::SimpleMath::Vector2(0, 0),
		1.0f,
		this->spriteEffect,
		0.0f
	);
}

void Entity::FlashColors(DirectX::SimpleMath::Color tint1, DirectX::SimpleMath::Color tint2, int time, double totalTime) {
	this->SetTimeToFlash(timeToFlash);
	for (int timeToFlash = time; timeToFlash > 0;timeToFlash--) {
		this->SetTint(tint1);
		if (totalTime - timeToFlash > 0.5) {
			this->SetTint(tint2);
		}
		this->SetTimeToFlash(this->GetTimeToFlash() - 1);
	}

	// on collision set member variable timeToFlash to 5
	// if totalTime - time > 0.5 flash
	// timeToFlash--
}

//Accessors
DirectX::SimpleMath::Vector2 Entity::GetBoardOffset(){
	return DirectX::SimpleMath::Vector2(2,2);
}

int Entity::GetTimeToFlash() {
	return timeToFlash;
}

DirectX::SimpleMath::Vector2 Entity::GetPosition() {
	return position;
}

DirectX::SimpleMath::Vector2 Entity::GetVelocity() {
	return velocity;
}

DirectX::SimpleMath::Color Entity::GetTint() {
	return tint;
}

DirectX::SpriteEffects Entity::GetSpriteEffect() {
	return spriteEffect;
}

int Entity::GetHeight() {
	return height;
}

int Entity::GetWidth() {
	return width;
}

int Entity::GetBoardColCount() {
	return boardColumnCount;
}

int Entity::GetBoardRowCount() {
	return boardRowCount;
}

CollisionBox Entity::GetAABB() {
	return aabb;
}

//Mutators
void Entity::SetBoardOffset(DirectX::SimpleMath::Vector2 newOffset) {
	boardOffset = newOffset;
}

void Entity::SetPosition(DirectX::SimpleMath::Vector2 newPos) {
	this->position = newPos;
}

void Entity::SetVelocity(DirectX::SimpleMath::Vector2 newVel) {
	this->velocity = newVel;
}

void Entity::SetSpriteEffect(DirectX::SpriteEffects newSpriteEffect) {
	this->spriteEffect = newSpriteEffect;
}

void Entity::SetHeight(int newHeight) {
	this->height = newHeight;
}

void Entity::SetWidth(int newWidth) {
	this->width = newWidth;
}

void Entity::SetBoardBounds(int columns, int rows) {
	this->boardColumnCount = columns;
	this->boardRowCount = rows;
}

void Entity::SetAABB(DirectX::SimpleMath::Vector2 position) {
	this->aabb.SetAABB(position);
}

void Entity::SetTint(DirectX::SimpleMath::Color tint) {
	this->tint = tint;
}

void Entity::SetTimeToFlash(int time) {
	this->timeToFlash = time;
}


