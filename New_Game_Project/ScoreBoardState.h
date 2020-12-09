#pragma once
//#include "MainMenuState.h"
#include "GUI.h"
#include<iostream>
#include<ctime>
#include<cstdlib>
#include<vector>
#include<fstream>
#include<sstream>
#include<stack>
#include<map>
#include<math.h>

#include <SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
#include<SFML/System.hpp>

using namespace std;
using namespace sf;

class ScoreBoardState
{
private:
    int player_score;
    sf::Font& font_number;
    sf::Font font_number2;
    sf::Text menu_text;

    sf::Text name_text[5];
    sf::Text score_text[5];
    std::string name[6];
    int score[6];
    int score_pos;
    int current_score;

    /// Input Name Gui ///
    sf::RectangleShape name_input_bg;
    sf::RectangleShape name_input_cursor;
    float total_time;
    sf::Clock clock;
    bool cursor_show;
    sf::Event* ev;
    char last_char = ' ';
    std::string input;
    sf::Text text_input;

    /// High Score Board ///
    sf::RectangleShape bg;
    sf::RectangleShape container;

    std::map<std::string, gui::Button*> buttons;

    void initFont();

public:
    ScoreBoardState(RenderWindow* window, Font& font, Event* ev);
    virtual ~ScoreBoardState(); 

    /// Accessors ///
    map<string, gui::Button*>& get_buttons();
    const bool is_button_pressed(const std::string key);

    /// Modifier ///
    void set_player_score(int player_score);

    /// Functions ///
    void add_button(const string key, float y, float width, float height, const string text);
    void check_score(std::string path);
    void save_high_score(std::string path);
    void update(const sf::Vector2i& mousePosWindow);
    void update(const float& dt);
    void render(sf::RenderTarget& target);
};

