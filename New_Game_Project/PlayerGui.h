#pragma once
#include"Player.h"
#include "GUI.h"

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

	void initFont();
	void initLevelBar();
	void initEXPBar();
	void initHPBar();


public:
	PlayerGui(Player* player);
	virtual ~PlayerGui();

	//Functions


	void updateLevelBar();
	void updateEXPBar();
	void updateHPBar();
	void update(const float& dt);

	void renderLevelBar(sf::RenderTarget& target);
	void renderEXPBar(sf::RenderTarget& target);
	void renderHPBar(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);
};

