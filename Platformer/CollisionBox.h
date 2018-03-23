#pragma once
#include <SimpleMath.h>
class CollisionBox
{
public:
	CollisionBox(DirectX::SimpleMath::Vector2 centre, DirectX::SimpleMath::Vector2 extents);
	~CollisionBox();

public:
	bool DoesIntersect(const CollisionBox& otherAabb) const;
	void SetAABB(const DirectX::SimpleMath::Vector2& topLeft);

private:
	DirectX::SimpleMath::Vector2 centre;
	DirectX::SimpleMath::Vector2 extents;

};

