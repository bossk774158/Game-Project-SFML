#pragma once
#include"Player.h"

class Player;
class sf::RectangleShape;

class PlayerGui
{
private:
	Player* player;
	
	sf::Font font;

	//Exp Bar

	//Hp Bar
	std::string hpBarString;
	sf::Text hpBarText;
	float hpBarMaxWidth;
	sf::RectangleShape hpBarBack;
	sf::RectangleShape hpBarInner;

	void initFont();
	void initHPBar();

public:
	PlayerGui(Player* player);
	virtual ~PlayerGui();

	//Functions
	void updateHPBar();
	void update(const float& dt);

	void renderHPBar(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);
};

