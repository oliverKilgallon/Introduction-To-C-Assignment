#pragma once
#include "DeviceResources.h"
#include "SpriteResources.h"
#include "GameController.h"
#include <SimpleMath.h>
#include <string>
class TextWriter
{
public:
	TextWriter(std::wstring text, DirectX::SimpleMath::Vector2 textPosition);
	~TextWriter();

public:
	void Render(std::shared_ptr<SpriteResources> resources);
	void Update(std::wstring newText);
	void SetTintColour(DirectX::SimpleMath::Color);
private:
	DirectX::SimpleMath::Vector2 m_textPosition;
	DirectX::SimpleMath::Color m_textTint;
	std::wstring m_output;
};