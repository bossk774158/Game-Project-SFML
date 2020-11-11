#pragma once
#include "State.h"
#include"GUI.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "DefaultEditorMode.h"

class State;
class StateData;
class GUI;
class PauseMenu;
class TileMap;
class Tile;
class EditorMode;
class DefaultEditorMode;
class EditorStateData;

enum EditorModes {DEFAULT_MODE = 0, ENEMY};



class EditorState :
    public State
{
private:
    EditorStateData editorStateData;

    //Variables
    sf::View view;
    sf::Font font;
    sf::Font font_number;
    PauseMenu* pmenu;

    std::map<std::string, gui::Button*> buttons;

    TileMap* tileMap;

    std::vector<EditorMode*> modes;

    float cameraSpeed;

    //Functions
    void initVariables();
    void initEditorStateData();
    void initView();
    void initFonts();
    void initKeybinds();
    void initPauseMenu();
    void initButtons();
    void initGui();
    void initTileMap();

    void initModes();
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

