#pragma once
#include "DeviceResources.h"
#include "SpriteResources.h"
#include "TextWriter.h"
#include <vector>
#include "States.h"
class Menu
{
public:
	Menu(std::shared_ptr<DX::DeviceResources> deviceResources);
	~Menu();

public:
	void Render(std::shared_ptr<SpriteResources> resources);
	GameStates Update(std::shared_ptr<GameController> controller);

private:
	std::vector<std::shared_ptr<TextWriter>> m_menuItems;
	int m_selectedIndex;
};

