#include "CharacterTab.h"

void CharacterTab::initText()
{
	//Text
	this->topic.setFont(this->font);
	this->topic.setCharacterSize(30.f);
	this->topic.setFillColor(sf::Color::White);
	this->topic.setPosition(this->back.getPosition().x + 115.f, this->back.getPosition().y + 20.f);

	this->topic.setString("Player Status");

	this->infoText.setFont(this->font);
	this->infoText.setCharacterSize(25.f);
	this->infoText.setFillColor(sf::Color::White);
	this->infoText.setPosition(this->back.getPosition().x, this->back.getPosition().y + 80.f);

	this->infoText.setString(this->player.toStringCharacterTab());
}

CharacterTab::CharacterTab(sf::Font& font, Player& player)
	:Tab(font, player, false)
{
	//Background
	this->back.setFillColor(sf::Color(50, 50, 50, 250));
	this->back.setSize(sf::Vector2f(400.f, 500.f));
	this->back.setPosition(sf::Vector2f(760.f, 215.f));

	this->initText();
}

CharacterTab::~CharacterTab()
{

}

void CharacterTab::update()
{
	if (!this->hidden)
	{
		this->infoText.setString(this->player.toStringCharacterTab());
	}
}

void CharacterTab::render(sf::RenderTarget& target)
{
	if (!this->hidden)
	{
		target.draw(back);
		target.draw(topic);
		target.draw(infoText);
	}
	
}
