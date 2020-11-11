#pragma once
#include<iostream>
#include<ctime>
#include<cstdlib>
#include<vector>
#include<fstream>
#include<sstream>
#include<stack>
#include<map>

#include <SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
#include<SFML/System.hpp>

#include "EditorMode.h"

class State;
class StateData;
class EditorMode;
class TileMap;
class Tile;

class DefaultEditorMode :
    public EditorMode
{
private:
    sf::Text cursorText;
    sf::RectangleShape sidebar;
    sf::IntRect textureRect;
    sf::RectangleShape selectorRect;
    gui::TextureSelector* textureSelector;
    sf::RectangleShape collisionBox;
    bool collision;
    short type;
    int layer;
    bool tileAddlock;

    void initVariables();
    void initGui();

public:
    DefaultEditorMode(StateData* state_data, TileMap* tile_map, EditorStateData* editor_state_data);
    virtual ~DefaultEditorMode();

    void updateInput(const float& dt);
    void updateGui(const float& dt);
    void update(const float& dt);

    void renderGui(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = NULL);
};

