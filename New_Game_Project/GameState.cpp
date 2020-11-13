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
			static_cast<float>(this->stateData->gfxSettings->resolution.width),
			static_cast<float>(this->stateData->gfxSettings->resolution.height)
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

void GameState::initEnemySystem()
{
	this->enemySystem = new EnemySystem(this->activeEnemies, this->textures);
}

void GameState::initTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, 100, 100, "Resources/Images/Tiles/grass2.png");
	this->tileMap->loadFromFile("text.slmp");
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
	this->initTileMap();

}
GameState::~GameState()
{
	delete this->pmenu;
	delete this->player;
	delete this->playerGui;
	delete this->enemySystem;
	delete this->tileMap;

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
	{
		this->player->move(0.f, -1.f, dt);
		if (this->getKeytime())
			this->player->gainEXP(10);
	}
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

void GameState::updateTileMap(const float& dt)
{
	this->tileMap->updateWorldBoundCollision(this->player, dt);
	this->tileMap->updateTilecollision(this->player, dt);
	this->tileMap->updateTiles(this->player, dt, *this->enemySystem);

	for (auto* i : this->activeEnemies)
	{
		this->tileMap->updateWorldBoundCollision(i, dt);
		this->tileMap->updateTilecollision(i, dt);
	}
}

void GameState::updatePlayer(const float& dt)
{
}

void GameState::updateEnemies(const float& dt)
{
	this->activeEnemies.push_back(new Mummy(400.f, 400.f, this->textures["MUMMY_IDLE"]));
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

		this->player->update(dt);

		this->playerGui->update(dt);

		for (auto* i : this->activeEnemies)
		{
			i->update(dt);
		}
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

	for (auto* i : this->activeEnemies)
	{
		i->render(this->renderTexture);
	}

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
