 #pragma once
#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "PlayerGui.h"
#include "Arrow.h"
#include "TextTagSystem.h"
#include "Item.h"
#include "GameOverState.h"
#include "Dragon.h"
#include "EnemySpawnerTile.h"

class GameState :
    public State
{
private:
    sf::View view;
    sf::RenderTexture renderTexture;
    sf::Sprite renderSprite;

    int i;

    //Music
    sf::Music bg_music;

    //Sounds Effect
    std::map<std::string, sf::SoundBuffer*> soundEffects;
    sf::Sound swordSound;
    sf::Sound bowSound;
    sf::Sound pickupitemSound;
    sf::Sound dead;
    sf::Sound playerGetAttack;
    sf::Sound playerFootStep;

    //Sound Clock
    sf::Clock soundClock;
    

    //Gui
    sf::Font font;
    sf::Font font_number;
    PauseMenu* pmenu;

    //Debug
    sf::Text debugText;

    //Player
    Player* player;
    PlayerGui* playerGui;

    //Item
    std::vector<Item*> items;

    //Enemy
    std::vector<Enemy*> activeEnemies;
    EnemySystem* enemySystem;

    //Tilemap
    TileMap* tileMap;

    //Texttag
    TextTagSystem* tts;

    //Arrow
    std::map<std::string, sf::Texture*> texture;
    std::vector<Arrow*> arrows;

    sf::Clock shootTimer;
    sf::Clock punchTimer;

    sf::Clock spawnTimer;

    //Functions
    void initDeferredRender();
    void initView();
    void initKeybinds();
    void initFonts();
    void initTextures();
    void initPauseMenu();
    void initDebugText();
    void initPlayers();
    void initDragon();
    void initPlayerGui();
    void initArrow();
    void initEnemySystem();
    void initEnemy();
    void initTileMap();
    void initSystem();
    void initMusic();
    void initSoundEffect();
 

public:
    GameState(StateData* state_data);
    virtual ~GameState();

    //Modifiers
    void random();
    void itemsRandom();


    //Functions
    void updateView(const float& dt);
    void updateInput(const float& dt);
    void updatePlayerInput(const float& dt);
    void updatePlayerGui(const float& dt);
    void updatePauseMenuButtons();
    void updateDebugText(const float& dt);
    void updateTileMap(const float& dt);
    void updatePlayer(const float& dt);
    void updatePlayerIsDead(const float& dt);
    void updateArrow(const float& dt);
    //void updateSpawnEnemy(const float& dt);
    void updateCombatAndEnemies(const float& dt);
    void updateCombat(Enemy* enemy ,const int index, const float& dt);
    void updatePlayerInputAndSound(const float& dt);
    void updateItemCollision(const float& dt);
    void update(const float& dt);
    void render(sf::RenderTarget* target = NULL);
};

