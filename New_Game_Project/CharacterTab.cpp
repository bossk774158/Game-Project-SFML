#include "CharacterTab.h"

CharacterTab::CharacterTab(sf::Font& font, Player& player)
	:Tab(font, player, false)
{
	//Background
	this->back.setFillColor(sf::Color(50, 50, 50, 180));
	this->back.setSize(sf::Vector2f(400.f, 500.f));
	this->back.setPosition(sf::Vector2f(760.f, 215.f));

	//Text
	this->infoText.setFont(this->font);
	this->infoText.setCharacterSize(20.f);
	this->infoText.setFillColor(sf::Color::White);
	this->infoText.setPosition(this->back.getPosition().x + 20.f, this->back.getPosition().y + 20.f);
}

CharacterTab::~CharacterTab()
{

}

void CharacterTab::update()
{
	if (!this->hidden)
	{

	}
}

void CharacterTab::render(sf::RenderTarget& target)
{
	if (!this->hidden)
	{
		target.draw(back);
		target.draw(infoText);
	}
	
}
