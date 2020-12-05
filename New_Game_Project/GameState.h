 #pragma once
#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "PlayerGui.h"
#include "Arrow.h"
#include "TextTagSystem.h"
#include "Item.h"
#include "GameOverState.h"
#include "VictoryState.h"
#include "Dragon.h"
#include "EnemySpawnerTile.h"

class GameState :
    public State
{
private:
    sf::View view;
    sf::RenderTexture renderTexture;
    sf::Sprite renderSprite;

    sf::Clock clockScore;
    float score;

    int i;
    int j;

    //Music
    sf::Music bg_music;

    //Sounds Effect
    std::map<std::string, sf::SoundBuffer*> soundEffects;

    sf::Sound swordSound;
    sf::Sound bowSound;
    sf::Sound pickupitemSound;

    sf::Sound playerGetAttack;

    sf::Sound mummyAttack;
    sf::Sound mummyGetAttack;

    sf::Sound bossAttack;
    sf::Sound bossgetAttack;

    sf::Sound birdAttack;
    sf::Sound birdGetAttack;

    sf::Sound healPotion;
    sf::Sound expPotion;
    sf::Sound poisonPotion;
    sf::Sound strengthPotion;
    sf::Sound randomPotion;


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
    float dropChance;

    //Enemy
    std::vector<Enemy*> activeEnemies;
    EnemySystem* enemySystem;
    Dragon* dragon;

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
    void initVariables();
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

    void random2();
    void itemsRandom2();


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
    void updateSpawnEnemy(const float& dt);
    void updateCombatAndEnemies(const float& dt);
    void updateCombat(Enemy* enemy ,const int index, const float& dt);
    void updatePlayerInputAndSound(const float& dt);
    void updateItemCollision(const float& dt);
    void updateScore(const float& dt);
    void update(const float& dt);
    void render(sf::RenderTarget* target = NULL);
};

