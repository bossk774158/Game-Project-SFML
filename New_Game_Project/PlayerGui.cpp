#include "PlayerGui.h"

void PlayerGui::initFont()
{
	this->font.loadFromFile("Fonts/novem___.ttf");
}

void PlayerGui::initHPBar()
{
	float width = 300.f;
	float height = 40.f;
	float x = 20.f;
	float y = 20.f;

	this->hpBarMaxWidth = width;

	this->hpBarBack.setSize(sf::Vector2f(width, height));
	this->hpBarBack.setFillColor(sf::Color(50, 50, 50, 200));
	this->hpBarBack.setPosition(x, y);

	this->hpBarInner.setSize(sf::Vector2f(width, height));
	this->hpBarInner.setFillColor(sf::Color(250, 20, 20, 200));
	this->hpBarInner.setPosition(this->hpBarBack.getPosition());

	this->hpBarText.setFont(this->font);
	this->hpBarText.setPosition(this->hpBarInner.getPosition().x + 10.f, this->hpBarInner.getPosition().y + 5.f);
}

PlayerGui::PlayerGui(Player* player)
{
	this->player = player;

	this->initFont();
	this->initHPBar();
}

PlayerGui::~PlayerGui()
{

}

//Functions
void PlayerGui::updateHPBar()
{
	float percent = static_cast<float>(std::floor(this->player->getAttributeComponent()->hp)) / static_cast<float>(std::floor(this->player->getAttributeComponent()->hpMax));

	this->hpBarInner.setSize(
		sf::Vector2f(
			static_cast<float>(std::floor(this->hpBarMaxWidth * percent)),
			this->hpBarInner.getSize().y
		)
	);

	this->hpBarString = std::to_string(this->player->getAttributeComponent()->hp) + " / " + std::to_string(this->player->getAttributeComponent()->hpMax);
	this->hpBarText.setString(this->hpBarString);
}

void PlayerGui::update(const float& dt)
{
	this->updateHPBar();
}

void PlayerGui::renderHPBar(sf::RenderTarget& target)
{
	target.draw(this->hpBarBack);
	target.draw(this->hpBarInner);
	target.draw(this->hpBarText);
}

void PlayerGui::render(sf::RenderTarget& target)
{
	this->renderHPBar(target);
}
