#include "GameState.h"


void GameState::initDeferredRender()
{
	this->renderTexture.create(
		this->stateData->gfxSettings->resolution.width,
		this->stateData->gfxSettings->resolution.height
	);

	this->renderSprite.setTexture(this->renderTexture.getTexture());
	this->renderSprite.setTextureRect(sf::IntRect(0, 0, this->stateData->gfxSettings->resolution.width, this->stateData->gfxSettings->resolution.height));
}

void GameState::initView()
{
	this->view.setSize(
		sf::Vector2f(
			static_cast<float>(this->stateData->gfxSettings->resolution.width / 2),
			static_cast<float>(this->stateData->gfxSettings->resolution.height / 2)
		)
	);

	this->view.setCenter(
		sf::Vector2f(
			static_cast<float>(this->stateData->gfxSettings->resolution.width) / 2.f,
			static_cast<float>(this->stateData->gfxSettings->resolution.height) / 2.f
		)
	);
}

void GameState::initKeybinds()
{
	std::ifstream ifs("Config/gamestate_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}

	ifs.close();


}

void GameState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Rodwick.otf"))
	{
		throw("Error to download font");
	}
}

void GameState::initTextures()
{
	if (!this->textures["PLAYER_IDLE"].loadFromFile("Resources/Images/Sprites/Player/playerSheet.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_IDLE_TEXTURE";
	}

	if (!this->textures["MUMMY_IDLE"].loadFromFile("Resources/Images/Sprites/Enemies/enemy_mummy.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_MUMMY_IDLE_TEXTURE";
	}
}

void GameState::initPauseMenu()
{
	this->pmenu = new PauseMenu(*this->window, this->font);

	this->pmenu->addButton("QUIT", 600.f, "Quit");

}

void GameState::initPlayers()
{
	this->player = new Player(273.f, 390.f, this->textures["PLAYER_IDLE"]);
}

void GameState::initPlayerGui()
{
	this->playerGui = new PlayerGui(this->player);
}

void GameState::initArrow()
{
	this->texture["ARROW"] = new sf::Texture();
	if (!this->texture["ARROW"]->loadFromFile("Resources/Images/Sprites/Player/Bullet.png"))
		std::cout << "ERROR" << "\n";
}

void GameState::initEnemySystem()
{
	this->enemySystem = new EnemySystem(this->activeEnemies, this->textures, *this->player);
}

//void GameState::initEnemy()
//{
//	this->enemySystem->createEnemy(MUMMY, 400.f, 400.f);
//}

void GameState::initTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, 100, 100, "Resources/Images/Tiles/grass2.png");
	this->tileMap->loadFromFile("text.slmp");
}

void GameState::initSystem()
{
	this->tts = new TextTagSystem("Fonts/Fun Games.ttf");
}

GameState::GameState(StateData* state_data)
	:State(state_data)
{
	this->initDeferredRender();
	this->initView();
	this->initKeybinds();
	this->initFonts();
	this->initTextures();
	this->initPauseMenu();

	this->initEnemySystem();
	this->initPlayers(); 
	this->initPlayerGui();
	//this->initEnemy();
	this->initArrow();
	this->initTileMap();
	this->initSystem();

}
GameState::~GameState()
{
	delete this->pmenu;
	delete this->player;
	delete this->playerGui;

	for (auto& i : this->texture)
	{
		delete i.second;
	}

	for (auto *i : this->arrows)
	{
		delete i;
	}

	delete this->enemySystem;
	delete this->tileMap;
	delete this->tts;

	for (size_t i = 0; i < this->activeEnemies.size(); i++)
	{
		delete this->activeEnemies[i];
	}

}

void GameState::updateView(const float& dt)
{
	this->view.setCenter(
		std::floor(this->player->getPosition().x + (static_cast<float>(this->mousePosWindow.x) - static_cast<float>(this->stateData->gfxSettings->resolution.width / 2)) / 5.f),
		std::floor(this->player->getPosition().y + (static_cast<float>(this->mousePosWindow.y) - static_cast<float>(this->stateData->gfxSettings->resolution.height / 2)) / 5.f)
	);
}

void GameState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeytime())
	{
		if (!this->paused)
			this->pauseState();
		else
			this->unpauseState(); 
	}
}

void GameState::updatePlayerInput(const float& dt)
{
	//Update player Input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
		this->player->move(-1.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
		this->player->move(1.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
		this->player->move(0.f, -1.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
	{
		this->player->move(0.f, 1.f, dt);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("SHOOT"))))
	{
		if (this->shootTimer.getElapsedTime().asSeconds() > 0.5f)
		{
			this->arrows.push_back(new Arrow(this->texture["ARROW"], this->player->getPos().x, this->player->getPos().y, 1.f, 0.f, 1500.f));
			this->shootTimer.restart();
			std::cout << "shot!" << "\n";
		}
	}
		
}

void GameState::updatePlayerGui(const float& dt)
{
	this->playerGui->update(dt);
}

void GameState::updatePauseMenuButtons()
{
	if (this->pmenu->isButtonPressed("QUIT"))
		this->endState();
}

void GameState::updateTileMap(const float& dt)
{
	this->tileMap->updateWorldBoundCollision(this->player, dt);
	this->tileMap->updateTilecollision(this->player, dt);
	this->tileMap->updateTiles(this->player, dt, *this->enemySystem);
}

void GameState::updatePlayer(const float& dt)
{

}

void GameState::updateArrow(const float& dt)
{
	unsigned counter = 0;
	for (auto* arrow : this->arrows)
	{
		arrow->update(dt);
	}
}

//void GameState::updateSpawnEnemy(const float& dt)
//{
//	if (this->spawnTimer.getElapsedTime().asSeconds() > 30.f)
//	{
//		this->enemySystem->createEnemy(MUMMY, 400.f, 400.f);
//	}
//}

void GameState::updateCombatAndEnemies(const float& dt)
{
	unsigned index = 0;
	for (auto* enemy : this->activeEnemies)
	{
		enemy->update(dt,this->view);

		this->tileMap->updateWorldBoundCollision(enemy, dt);
		this->tileMap->updateTilecollision(enemy, dt);

		this->updateCombat(enemy, index, dt);

		//DANGEROUS
		if (enemy->isDead())
		{
			this->player->gainEXP(enemy->getGainExp());
			this->tts->addTextTag(EXP_TAG, this->player->getPosition().x - 50.f, this->player->getPosition().y + 30.f, static_cast<int>(enemy->getGainExp()), "+" , "EXP");

			this->enemySystem->removeEnemy(index);
			continue;
		}
		else if (enemy->getDespawnTimerDone())
		{
			this->enemySystem->removeEnemy(index);
			continue;
		}

		++index;
	}
}

void GameState::updateCombat(Enemy* enemy, const int index, const float& dt)
{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) 
			&& enemy->getGlobalBounds().contains(this->mousePosView)
			&& enemy->getDistance(*this->player) < 40.f)
		{
			if (this->punchTimer.getElapsedTime().asSeconds() > 0.3f && enemy->getDamageTimerDone())
			{
					int dmg = static_cast<int>(this->player->getDamage());
					enemy->loseHP(dmg);
					enemy->resetDamageTimer();
					this->tts->addTextTag(NEGATIVE_TAG, enemy->getCenter().x, enemy->getCenter().y, dmg, "" , "");
					this->punchTimer.restart(); 
			}
		}
		if (enemy->getGlobalBounds().intersects(this->player->getGlobalBounds()) && this->player->getDamageTimer())
		{
			int dmg = enemy->getAttributeComp()->damageMax;
			this->player->loseHP(dmg);
			this->tts->addTextTag(NEGATIVE_TAG, this->player->getPosition().x, this->player->getPosition().y, dmg, "-", "HP");
		}
}

void GameState::update(const float& dt)
{
	this->updateMousePositions(&this->view);
	this->updateKeytime(dt);
	this->updateInput(dt);

	if (!this->paused) //Unpause
	{
		this->updateView(dt);

		this->updatePlayerInput(dt);

		this->updateTileMap(dt);

		this->player->update(dt, this->view);

		this->playerGui->update(dt);

		this->updateArrow(dt);

		this->updateCombatAndEnemies(dt);

		//this->updateSpawnEnemy(dt);

		this->tts->update(dt);
	}
	else //Pause
	{
		this->pmenu->update(this->mousePosWindow);
		this->updatePauseMenuButtons();
	}
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	this->renderTexture.clear();

	this->renderTexture.setView(this->view);

	this->tileMap->render(this->renderTexture, this->player->getGridPosition(static_cast<int>(this->stateData->gridSize)));

	this->player->render(this->renderTexture);

	for (auto* enemy : this->activeEnemies)
	{
		enemy->render(this->renderTexture);
	}

	for (auto* arrow : this->arrows)
	{
		arrow->render(this->renderTexture);
	}

	this->tts->render(this->renderTexture);

	//Render Gui
	this->renderTexture.setView(this->renderTexture.getDefaultView());
	this->playerGui->render(this->renderTexture);

	if (this->paused) //Pause menu render
	{
		this->renderTexture.setView(this->renderTexture.getDefaultView());
		this->pmenu->render(this->renderTexture);
	}

	//FINAL RENDER
	this->renderTexture.display();
	//this->renderSprite.setTexture(this->renderTexture.getTexture());
	target->draw(this->renderSprite);
}
