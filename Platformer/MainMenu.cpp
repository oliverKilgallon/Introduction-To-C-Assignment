#include "pch.h"
#include "MainMenu.h"


Menu::Menu(std::shared_ptr<DX::DeviceResources> deviceResources)
{
	std::shared_ptr<TextWriter> itemOne = std::shared_ptr<TextWriter>
		(new TextWriter(std::wstring(L"Start"), DirectX::SimpleMath::Vector2(100.0f, 100.0f)));

	std::shared_ptr<TextWriter> itemTwo = std::shared_ptr<TextWriter>
		(new TextWriter(L"Quit", DirectX::SimpleMath::Vector2(100.0f, 200.0f)));

	m_menuItems.push_back(itemOne);		// index 0
	m_menuItems.push_back(itemTwo);		// index 1

										// set the selected index to item 1
	m_selectedIndex = 0;
	m_menuItems[m_selectedIndex]->SetTintColour(DirectX::Colors::LightBlue.v);
}


Menu::~Menu()
{
}

GameStates Menu::Update(std::shared_ptr<GameController> gameController)
{
	GameStates state = GameStates::Menu_State;
	switch (m_selectedIndex)
	{
		case 0:
		{
			// if we are on the first item we are only interested if either A is down or the Down buttons on the DPAD
			if (gameController->WasButtonReleaseDetected(XINPUT_GAMEPAD_A))
			{
				state = GameStates::Playing_State;
			}
			else if (gameController->WasButtonReleaseDetected(XINPUT_GAMEPAD_DPAD_DOWN))
			{
				m_menuItems[m_selectedIndex]->SetTintColour(DirectX::Colors::White.v);
				m_selectedIndex = 1;
				m_menuItems[m_selectedIndex]->SetTintColour(DirectX::Colors::LightBlue.v);
			}
		}
		break;

		case 1:
		{
			// if we are on the first item we are only interested if either A is down or the Down buttons on the DPAD
			if (gameController->WasButtonReleaseDetected(XINPUT_GAMEPAD_A))
			{
				exit(EXIT_SUCCESS);
			}
			else if (gameController->WasButtonReleaseDetected(XINPUT_GAMEPAD_DPAD_UP))
			{
				m_menuItems[m_selectedIndex]->SetTintColour(DirectX::Colors::White.v);
				m_selectedIndex = 0;
				m_menuItems[m_selectedIndex]->SetTintColour(DirectX::Colors::LightBlue.v);
			}
		}
		break;

		default:
			break;
	}
	return state;
}

void Menu::Render(std::shared_ptr<SpriteResources> spriteResources)
{
	for (unsigned int i = 0; i < m_menuItems.size(); i++)
	{
		m_menuItems[i]->Render(spriteResources);
	}
}
