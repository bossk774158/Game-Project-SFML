#include "PlayerGUITabs.h"

void PlayerGUITabs::initFont()
{
	this->font.loadFromFile("Fonts/novem___.ttf");
}

void PlayerGUITabs::initKeyTime()
{
	this->keyTimeMax = 0.2f;
	this->keyTimer.restart();
}

PlayerGUITabs::PlayerGUITabs(sf::Font& font, Player& player)
	:font(font), player(player), characterTab(font, player)
{
	this->initFont();
	this->initKeyTime();

}

PlayerGUITabs::~PlayerGUITabs()
{

}

const bool PlayerGUITabs::getKeyTime()
{
	if (this->keyTimer.getElapsedTime().asSeconds() >= this->keyTimeMax)
	{
		this->keyTimer.restart();
		return true;
	}
		

	return false;
}

const bool PlayerGUITabs::tabsOpen()
{
	return this->characterTab.getOpen();
}

void PlayerGUITabs::toggleCharacterTab()
{
	if (this->characterTab.getHidden())
		this->characterTab.show();
	else
		this->characterTab.hide();
}

void PlayerGUITabs::update()
{

}

void PlayerGUITabs::render(sf::RenderTarget& target)
{
	this->characterTab.render(target);
}






