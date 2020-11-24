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
	if (!this->font_number.loadFromFile("Fonts/Honeybae.otf"))
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

	if (!this->textures["DRAGON_IDLE"].loadFromFile("Resources/Images/Sprites/Enemies/boss_demon.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_DRAGON_IDLE_TEXTURE";
	}

	if (!this->textures["BIRD_IDLE"].loadFromFile("Resources/Images/Sprites/Enemies/enemy_bird.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_DRAGON_IDLE_TEXTURE";
	}

	if (!this->textures["HEALTH_POTION"].loadFromFile("Resources/Images/Potions/health_potion.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_HEALTH_POTION_TEXTURE";
	}

	if (!this->textures["POISON_POTION"].loadFromFile("Resources/Images/Potions/poison_potion.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_HEALTH_POTION_TEXTURE";
	}

	if (!this->textures["SPEED_POTION"].loadFromFile("Resources/Images/Potions/speed_potion.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_HEALTH_POTION_TEXTURE";
	}

	if (!this->textures["EXP_POTION"].loadFromFile("Resources/Images/Potions/exp_potion.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_HEALTH_POTION_TEXTURE";
	}

	if (!this->textures["RANDOM_POTION"].loadFromFile("Resources/Images/Potions/random_potion.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_HEALTH_POTION_TEXTURE";
	}

	if (!this->textures["STRENGTH_POTION"].loadFromFile("Resources/Images/Potions/strength_potion.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_HEALTH_POTION_TEXTURE";
	}

	if (!this->textures["RANDOM_BOX"].loadFromFile("Resources/Images/Potions/random_box.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_HEALTH_POTION_TEXTURE";
	}
	
}

void GameState::initPauseMenu()
{
	this->pmenu = new PauseMenu(*this->window, this->font);

	this->pmenu->addButton("QUIT", 600.f, "Quit");
}

void GameState::initDebugText()
{
	this->debugText.setFont(this->font_number);
	this->debugText.setFillColor(sf::Color::White);
	this->debugText.setCharacterSize(16);
	this->debugText.setPosition(15.f, this->window->getSize().y / 2.f);
}

void GameState::initPlayers()
{
	this->player = new Player(273.f, 390.f, this->textures["PLAYER_IDLE"]);
}

void GameState::initDragon()
{
	//this->dragon = new Dragon(850.f, 1320.f, this->textures["DRAGON_IDLE"]);
}

void GameState::initPlayerGui()
{
	this->playerGui = new PlayerGui(this->player);
}

void GameState::initArrow()
{
	this->texture["ARROW"] = new sf::Texture();
	if (!this->texture["ARROW"]->loadFromFile("Resources/Images/Sprites/Player/Bullet.png"))
		std::cout << "ERROR_BULLET" << "\n";
}

void GameState::initEnemySystem()
{
	this->enemySystem = new EnemySystem(this->activeEnemies, this->textures, *this->player);
}

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
	this->initDebugText();
	this->initPlayers(); 

	this->initEnemySystem();
	this->initPlayerGui();
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

	for (auto* item : this->items)
	{
		delete item;
	}

	delete this->enemySystem;
	delete this->tileMap;
	delete this->tts;

	for (size_t i = 0; i < this->activeEnemies.size(); i++)
	{
		delete this->activeEnemies[i];
	}

}

void GameState::random()
{
	this->i = rand() % 5;
}

void GameState::itemsRandom()
{
	for (int a = 0; a <= 5; a++)
	{
		random();
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
		this->player->move(0.f, 1.f, dt);

	
		
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

void GameState::updateDebugText(const float& dt)
{
	std::stringstream ss;

	ss << "Mouse Pos View: " << this->mousePosView.x << " " << this->mousePosView.y << "\n"
		<< "Active Enemies: " << this->activeEnemies.size() << "\n";

	this->debugText.setString(ss.str());
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

void GameState::updatePlayerIsDead(const float& dt)
{
	if (this->player->getAttributeComponent()->hp_player <= 0)
	{
		this->states->pop();
		this->states->push(new GameOverState(this->stateData));
	}
}

void GameState::updateArrow(const float& dt)
{
	unsigned counter = 0;
	for (auto* arrow : this->arrows)
	{
		arrow->update(dt);

		for (auto* enemy : this->activeEnemies)
		{
			if (arrow->getbounds().intersects(enemy->getGlobalBounds()))
			{
				enemy->loseHP(10);
				if (enemy->isDead())
				{
					if (enemy->getIsDrop())
					{
						random();
						if (this->i == 1)
						{
							this->items.push_back(new Item(&this->textures["HEALTH_POTION"], "HEAL", enemy->getCenter().x + 10.f, enemy->getCenter().y + enemy->getGlobalBounds().height - 40.f));
							std::cout << "Item::heal drop!" << "\n";
						}
						else if (this->i == 2)
						{
							this->items.push_back(new Item(&this->textures["POISON_POTION"], "POISON", enemy->getCenter().x + 10.f, enemy->getCenter().y + enemy->getGlobalBounds().height - 40.f));
							std::cout << "Item::heal drop!" << "\n";
						}
						else if (this->i == 3)
						{
							this->items.push_back(new Item(&this->textures["EXP_POTION"], "EXP", enemy->getCenter().x + 10.f, enemy->getCenter().y + enemy->getGlobalBounds().height - 40.f));
							std::cout << "Item::heal drop!" << "\n";
						}
						else if (this->i == 4)
						{
							this->items.push_back(new Item(&this->textures["STRENGTH_POTION"], "STRENGTH", enemy->getCenter().x + 10.f, enemy->getCenter().y + enemy->getGlobalBounds().height - 40.f));
							std::cout << "Item::heal drop!" << "\n";
						}
						else
						{
							this->items.push_back(new Item(&this->textures["RANDOM_POTION"], "RANDOM", enemy->getCenter().x + 10.f, enemy->getCenter().y + enemy->getGlobalBounds().height - 40.f));
							std::cout << "Item::heal drop!" << "\n";
						}
					}
				}
				delete this->arrows.at(counter);
				this->arrows.erase(this->arrows.begin() + counter);
				--counter;
			}
		}
	}
	++counter;
}

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
			&& enemy->getDistance(*this->player) < 55.f)
		{
			if (this->punchTimer.getElapsedTime().asSeconds() > 0.1f && enemy->getDamageTimerDone())
			{
					int dmg = static_cast<int>(this->player->getDamage());
					enemy->loseHP(dmg);
					if (enemy->isDead())
					{
						if (enemy->getIsDrop())
						{
							random();
							if (this->i == 1)
							{
								this->items.push_back(new Item(&this->textures["HEALTH_POTION"], "HEAL", enemy->getCenter().x + 10.f, enemy->getCenter().y + enemy->getGlobalBounds().height - 40.f));
								std::cout << "Item::heal drop!" << "\n";
							}
							else if (this->i == 2)
							{
								this->items.push_back(new Item(&this->textures["POISON_POTION"], "POISON", enemy->getCenter().x + 10.f , enemy->getCenter().y + enemy->getGlobalBounds().height - 40.f));
								std::cout << "Item::heal drop!" << "\n";
							}
							else if (this->i == 3)
							{
								this->items.push_back(new Item(&this->textures["EXP_POTION"], "EXP", enemy->getCenter().x + 10.f, enemy->getCenter().y + enemy->getGlobalBounds().height - 40.f));
								std::cout << "Item::heal drop!" << "\n";
							}
							else if(this->i == 4)
							{
								this->items.push_back(new Item(&this->textures["STRENGTH_POTION"], "STRENGTH", enemy->getCenter().x + 10.f, enemy->getCenter().y + enemy->getGlobalBounds().height - 40.f));
								std::cout << "Item::heal drop!" << "\n";
							}
							else
							{
								this->items.push_back(new Item(&this->textures["RANDOM_POTION"], "RANDOM", enemy->getCenter().x + 10.f, enemy->getCenter().y + enemy->getGlobalBounds().height - 40.f));
								std::cout << "Item::heal drop!" << "\n";
							}
							
						}
					}
					enemy->resetDamageTimer();
					this->tts->addTextTag(NEGATIVE_TAG, enemy->getCenter().x, enemy->getCenter().y, dmg, "" , "");
					this->punchTimer.restart(); 
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("SHOOT"))))
		{
			if (this->shootTimer.getElapsedTime().asSeconds() > 0.5f && this->player->getIsShoot() == false)
			{
				if(this->player->getIsFaceRight())
						this->arrows.push_back(new Arrow(this->texture["ARROW"], this->player->getPos().x, this->player->getPos().y, -1.f, 0.f, 1500.f));
				else
						this->arrows.push_back(new Arrow(this->texture["ARROW"], this->player->getPos().x, this->player->getPos().y, 1.f, 0.f, 1500.f));
				this->shootTimer.restart();
				std::cout << "shot!" << "\n";
			}
		}

		if (enemy->getGlobalBounds().intersects(this->player->getGlobalBounds()) && this->player->getDamageTimer())
		{
			int dmg = enemy->getAttributeComp()->damageMax_enemy;
			this->player->loseHP(dmg);
			this->tts->addTextTag(NEGATIVE_TAG, this->player->getPosition().x, this->player->getPosition().y, dmg, "-", "HP");
		}
}

void GameState::updateItemCollision(const float& dt)
{
	unsigned itemCounter = 0;
	for (auto* item : items)
	{
		if (item->getGlobalBounds().intersects(this->player->getGlobalBounds()) && this->player->getAttributeComponent()->hp_player <= 50 && item->getType() == "HEAL")
		{
			this->player->gainHP(10);
			this->items.erase(this->items.begin() + itemCounter);
			--itemCounter;
		}
		else if (item->getGlobalBounds().intersects(this->player->getGlobalBounds()) && item->getType() == "POISON")
		{
			this->player->loseHP(5);
			this->items.erase(this->items.begin() + itemCounter);
			--itemCounter;
		}
		else if (item->getGlobalBounds().intersects(this->player->getGlobalBounds()) && item->getType() == "EXP")
		{
			this->player->gainEXP(30);
			this->items.erase(this->items.begin() + itemCounter);
			--itemCounter;
		}
		else if (item->getGlobalBounds().intersects(this->player->getGlobalBounds()) && item->getType() == "STRENGTH")
		{
			this->player->getAttributeComponent()->getStrength(10);
			this->items.erase(this->items.begin() + itemCounter);
			--itemCounter;
		}
		++itemCounter;
	}
}

void GameState::update(const float& dt)
{
	this->updateMousePositions(&this->view);
	this->updateKeytime(dt);
	this->updateInput(dt);
	this->updateDebugText(dt);

	if (!this->paused) //Unpause
	{
		this->updateView(dt);

		this->updatePlayerInput(dt);

		this->updateTileMap(dt);

		this->player->update(dt, this->view);

		this->playerGui->update(dt);

		this->updateArrow(dt);

		this->updateCombatAndEnemies(dt);

		this->updateItemCollision(dt);

		this->tts->update(dt);

		this->updatePlayerIsDead(dt);
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

	for (auto* enemy : this->activeEnemies)
	{
		enemy->render(this->renderTexture);
	}

	this->player->render(this->renderTexture);

	for (auto* Item : this->items)
	{
		Item->render(this->renderTexture);
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

	//DEBUG TEXT
	this->renderTexture.draw(this->debugText);

	//FINAL RENDER
	this->renderTexture.display();
	//this->renderSprite.setTexture(this->renderTexture.getTexture());
	target->draw(this->renderSprite);
}
