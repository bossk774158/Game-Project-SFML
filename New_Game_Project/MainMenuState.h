#pragma once
#include"GameState.h"
#include"EditorState.h"
#include"SettingsState.h"
#include"ScoreBoardState.h"
#include"GUI.h"

class MainMenuState :
    public State
{
private:
    //Variables
    sf::Texture bgTexture;
    sf::RectangleShape background;
    sf::Font font;

    sf::Music main_music;

    std::map<std::string, gui::Button*> buttons;

    //Functions
    void initVariables();
    void initMusic();
    void initBackground();
    void initFonts();
    void initKeybinds();
    void initButtons();

public:
    MainMenuState(StateData* state_data);
    virtual ~MainMenuState();


    //Functions

    void updateInput(const float& dt);
    void updateButtons();
    void update(const float& dt);
    void renderButtons(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = NULL);
};

