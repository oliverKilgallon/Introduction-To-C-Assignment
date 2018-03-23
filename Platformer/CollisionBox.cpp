#include "pch.h"
#include "CollisionBox.h"
#include <SimpleMath.h>

CollisionBox::CollisionBox(DirectX::SimpleMath::Vector2 centre, DirectX::SimpleMath::Vector2 extents)
	: centre{ centre }
	, extents{ extents }
{
	this->centre = centre;
	this->extents = extents;
}

CollisionBox::~CollisionBox()
{

}

bool CollisionBox::DoesIntersect(const CollisionBox& otherAabb) const
{
	//Test whether the two rectangles are disjoint (do not intersect)
	// build the rectangles...
	float thisTop = this->centre.y - this->extents.y;
	float thisLeft = this->centre.x - this->extents.x;
	float thisBottom = this->centre.y + this->extents.y;
	float thisRight = this->centre.x + this->extents.x;

	float otherTop = otherAabb.centre.y - otherAabb.extents.x;
	float otherLeft = otherAabb.centre.x - otherAabb.extents.x;
	float otherBottom = otherAabb.centre.y + otherAabb.extents.y;
	float otherRight = otherAabb.centre.x + otherAabb.extents.x;


	// if the two rectangles are disjoint then dont do anything...
	if ((thisTop > otherBottom)
		|| (thisLeft > otherRight)
		|| (thisBottom < otherTop)
		|| (thisRight < otherLeft))
	{
		return false;
	}
	else
	{
		return true;
	}
}


void CollisionBox::SetAABB(const DirectX::SimpleMath::Vector2& topLeft)
{
	// we receive a reference to the top left corner of our AABB
	this->centre = topLeft + extents;
}