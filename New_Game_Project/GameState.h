 #pragma once
#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "PlayerGui.h"
#include "Bow.h"

class GameState :
    public State
{
private:
    sf::View view;
    sf::RenderTexture renderTexture;
    sf::Sprite renderSprite;

    sf::Font font;
    PauseMenu* pmenu;

    Player* player;
    PlayerGui* playerGui;

    std::vector<Enemy*> activeEnemies;
    EnemySystem* enemySystem;

    TileMap* tileMap;


    //Functions
    void initDeferredRender();
    void initView();
    void initKeybinds();
    void initFonts();
    void initTextures();
    void initPauseMenu();
    void initPlayers();
    void initPlayerGui();
    void initEnemySystem();
    void initTileMap();
 

public:
    GameState(StateData* state_data);
    virtual ~GameState();


    //Functions
    void updateView(const float& dt);
    void updateInput(const float& dt);
    void updatePlayerInput(const float& dt);
    void updatePlayerGui(const float& dt);
    void updatePauseMenuButtons();
    void updateTileMap(const float& dt);
    void updatePlayer(const float& dt);
    void updateEnemies(const float& dt);
    void update(const float& dt);
    void render(sf::RenderTarget* target = NULL);
};

