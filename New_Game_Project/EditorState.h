#pragma once
#include "State.h"
#include"GUI.h"
#include "PauseMenu.h"
#include "TileMap.h"

class State;
class GUI;
class PauseMenu;
class TileMap;

class EditorState :
    public State
{
private:
    //Variables
    sf::View view;

    sf::Font font;
    sf::Font fontNumber;
    sf::Text cursorText;
    PauseMenu* pmenu;

    std::map<std::string, gui::Button*> buttons;

    TileMap* tileMap;

    sf::RectangleShape sidebar;

    sf::IntRect textureRect;
    sf::RectangleShape selectorRect; 

    gui::TextureSelector* textureSelector;

    bool collision;
    short type;
    float cameraSpeed;

    //Functions
    void initVariables();
    void initView();
    void initBackground();
    void initFonts();
    void initText();
    void initKeybinds();
    void initPauseMenu();
    void initButtons();
    void initGui();
    void initTileMap();

public:
    EditorState(StateData* state_data);
    virtual ~EditorState();


    //Functions

    void updateInput(const float& dt);
    void updateEditorInput(const float& dt);
    void updateButtons();
    void updateGui(const float& dt);
    void updatePauseMenuButtons();
    void update(const float& dt);
    void renderButtons(sf::RenderTarget& target);
    void renderGui(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = NULL);
};
