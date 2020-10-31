#pragma once
#include "State.h"
#include "GUI.h"
class SettingsState :
    public State
{
private:
    //Variables
    GraphicsSettings& gfxSettings;
    sf::Texture bgTexture;
    sf::RectangleShape background;
    sf::Font font;
    sf::Font fontNumber;

    std::map<std::string, gui::Button*> buttons;
    std::map<std::string, gui::DropDonwList*> dropdownList;

    sf::Text optionsText;

    std::vector<sf::VideoMode> modes;


    //Functions
    void initVariables();
    void initBackground();
    void initFonts();
    void initKeybinds();
    void initGui();
    void initText();

public:
    SettingsState(sf::RenderWindow* window, GraphicsSettings& gfxSettings, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~SettingsState();

    //Accessors


    //Functions

    void updateInput(const float& dt);
    void updateGui(const float& dt);
    void update(const float& dt);
    void renderGui(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = NULL);
};

