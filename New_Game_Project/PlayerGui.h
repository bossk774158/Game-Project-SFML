#pragma once
#include "PlayerGUITabs.h"

class Player;
class sf::RectangleShape;

class PlayerGui
{
private:
	Player* player;
	sf::Font font;


	//Level bar
	std::string levelBarString;
	sf::Text levelBarText;
	sf::RectangleShape levelBarBack;


	//Exp Bar
	std::string expBarString;
	sf::Text expBarText;
	float expBarMaxWidth;
	sf::RectangleShape expBarBack;
	sf::RectangleShape expBarInner;

	//Hp Bar
	std::string hpBarString;
	sf::Text hpBarText;
	float hpBarMaxWidth;
	sf::RectangleShape hpBarBack;
	sf::RectangleShape hpBarInner;

	//Player GUI Tabs
	PlayerGUITabs* playerTabs;

	void initFont();
	void initLevelBar();
	void initEXPBar();
	void initHPBar();
	void initPlayerTabs(sf::Font& font, Player& player);


public:
	PlayerGui(Player* player);
	virtual ~PlayerGui();

	//Accessors
	const bool getTabOpen() const;
	void toggleCharacterTab();

	//Functions
	void updateLevelBar();
	void updateEXPBar();
	void updateHPBar();
	void updatePlayerTabs();

	void update(const float& dt);

	void renderLevelBar(sf::RenderTarget& target);
	void renderEXPBar(sf::RenderTarget& target);
	void renderHPBar(sf::RenderTarget& target);
	void renderPlayerTabs(sf::RenderTarget& target);

	void render(sf::RenderTarget& target);
};

