#include "PlayerGui.h"

void PlayerGui::initFont()
{
	this->font.loadFromFile("Fonts/novem___.ttf");
}

void PlayerGui::initLevelBar()
{
	float width = 30.f;
	float height = 30.f;
	float x = 20.f;
	float y = 30.f;

	this->levelBarBack.setSize(sf::Vector2f(width, height));
	this->levelBarBack.setFillColor(sf::Color(50, 50, 50, 200));
	this->levelBarBack.setPosition(x, y);

	this->levelBarText.setFont(this->font); 
	this->levelBarText.setCharacterSize(18);
	this->levelBarText.setPosition(this->levelBarBack.getPosition().x + 10.f, this->levelBarBack.getPosition().y + 5.f);
}

void PlayerGui::initEXPBar()
{
	float width = 400.f;
	float height = 35.f;
	float x = 20.f;
	float y = 80.f;

	this->expBarMaxWidth = width;

	this->expBarBack.setSize(sf::Vector2f(width, height));
	this->expBarBack.setFillColor(sf::Color(50, 50, 50, 200));
	this->expBarBack.setPosition(x, y);

	this->expBarInner.setSize(sf::Vector2f(width, height));
	this->expBarInner.setFillColor(sf::Color(250, 250, 20, 200));
	this->expBarInner.setPosition(this->expBarBack.getPosition());

	this->expBarText.setFont(this->font);
	this->expBarText.setCharacterSize(16);
	this->expBarText.setPosition(this->expBarInner.getPosition().x + 10.f, this->expBarInner.getPosition().y + 5.f);
}

void PlayerGui::initHPBar()
{
	float width = 400.f;
	float height = 35.f;
	float x = 20.f;
	float y = 130.f;

	this->hpBarMaxWidth = width;

	this->hpBarBack.setSize(sf::Vector2f(width, height));
	this->hpBarBack.setFillColor(sf::Color(50, 50, 50, 200));
	this->hpBarBack.setPosition(x, y);

	this->hpBarInner.setSize(sf::Vector2f(width, height));
	this->hpBarInner.setFillColor(sf::Color(250, 20, 20, 200));
	this->hpBarInner.setPosition(this->hpBarBack.getPosition());

	this->hpBarText.setFont(this->font);
	this->hpBarText.setCharacterSize(18);
	this->hpBarText.setPosition(this->hpBarInner.getPosition().x + 10.f, this->hpBarInner.getPosition().y + 5.f);
}

void PlayerGui::initPlayerTabs(sf::Font& font, Player& player)
{
	this->playerTabs = new PlayerGUITabs(font, player);
}



PlayerGui::PlayerGui(Player* player)
{
	this->player = player;

	this->initFont();
	this->initLevelBar();
	this->initEXPBar();
	this->initHPBar();
	this->initPlayerTabs(font ,*player);
}

PlayerGui::~PlayerGui()
{
	delete this->playerTabs;
}

const bool PlayerGui::getTabOpen() const
{
	return this->playerTabs->tabsOpen();
}

void PlayerGui::toggleCharacterTab()
{
	this->playerTabs->toggleCharacterTab();
}

void PlayerGui::updateLevelBar()
{
	this->levelBarString = std::to_string(this->player->getAttributeComponent()->level);
	this->levelBarText.setString(this->levelBarString);
}

void PlayerGui::updateEXPBar()
{
	float percent = static_cast<float>(std::floor(this->player->getAttributeComponent()->exp)) / static_cast<float>(std::floor(this->player->getAttributeComponent()->expNext));

	this->expBarInner.setSize(
		sf::Vector2f(
			static_cast<float>(std::floor(this->expBarMaxWidth * percent)),
			this->expBarInner.getSize().y
		)
	);

	this->expBarString = std::to_string(this->player->getAttributeComponent()->exp) + " / " + std::to_string(this->player->getAttributeComponent()->expNext);
	this->expBarText.setString(this->expBarString);
}

//Functions
void PlayerGui::updateHPBar()
{
	float percent = static_cast<float>(std::floor(this->player->getAttributeComponent()->hp_player)) / static_cast<float>(std::floor(this->player->getAttributeComponent()->hpMax_player));

	this->hpBarInner.setSize(
		sf::Vector2f(
			static_cast<float>(std::floor(this->hpBarMaxWidth * percent)),
			this->hpBarInner.getSize().y
		)
	);

	this->hpBarString = std::to_string(this->player->getAttributeComponent()->hp_player) + " / " + std::to_string(this->player->getAttributeComponent()->hpMax_player);
	this->hpBarText.setString(this->hpBarString);
}

void PlayerGui::updatePlayerTabs()
{
	this->playerTabs->update();
}

void PlayerGui::update(const float& dt)
{
	this->updateLevelBar();
	this->updateEXPBar();
	this->updateHPBar();
	this->updatePlayerTabs();
}

void PlayerGui::renderLevelBar(sf::RenderTarget& target)
{
	target.draw(this->levelBarBack);
	target.draw(this->levelBarText);
}

void PlayerGui::renderEXPBar(sf::RenderTarget& target)
{
	target.draw(this->expBarBack);
	target.draw(this->expBarInner);
	target.draw(this->expBarText);
}

void PlayerGui::renderHPBar(sf::RenderTarget& target)
{
	target.draw(this->hpBarBack);
	target.draw(this->hpBarInner);
	target.draw(this->hpBarText);
}

void PlayerGui::renderPlayerTabs(sf::RenderTarget& target)
{
	this->playerTabs->render(target);
}

void PlayerGui::render(sf::RenderTarget& target)
{
	this->renderLevelBar(target);
	this->renderEXPBar(target);
	this->renderHPBar(target);
	this->renderPlayerTabs(target);
}
