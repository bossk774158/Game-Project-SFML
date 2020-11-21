#include "GameOverState.h"
void GameOverState::initVariables()
{

}

void GameOverState::initMusic()
{

}

void GameOverState::initBackground()
{
	this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x),
		static_cast<float>(this->window->getSize().y)));

	if (!this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/gameover.jpg"))
	{
		std::cout << "ERROR::GAME_OVER_STATE::COULD NOT LOAD FROM FILE GAMEOVER" << std::endl;
	}

	this->background.setTexture(&this->backgroundTexture);
	this->background.setPosition(this->window->getSize().x, this->window->getSize().y);
}

void GameOverState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Fun Games.ttf"))
	{
		std::cout << "ERROR::GAME_OVER_STATE::COULD NOT LOAD FROM FILE 04FONT" << std::endl;
	}
}

void GameOverState::initButtons()
{
	float width = 250.f;
	float height = 50.f;
	float x = this->container.getPosition().x + this->container.getSize().x / 2.f - width / 2.f;

	this->buttons["GAME_STATE"] = new gui::Button(
		x, 600.f, width, height,
		&this->font, "New Game", 50,
		sf::Color(80, 80, 80, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
}

void GameOverState::initKeybinds()
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


GameOverState::GameOverState(StateData* state_data)
	:State(state_data)
{
	//Init container
	this->container.setSize(
		sf::Vector2f
		(static_cast<float>(window->getSize().x) / 4.f,
			static_cast<float>(window->getSize().y - 300.f)
		)
	);
	this->container.setFillColor(sf::Color(20, 20, 20, 200));
	this->container.setPosition(
		static_cast<float>(window->getSize().x) / 2.f - this->container.getSize().x / 2.f,
		30.f);

	//Init text
	this->menuText.setFont(font);
	this->menuText.setFillColor(sf::Color(255, 255, 255, 200));
	this->menuText.setCharacterSize(60);
	this->menuText.setString("GAME OVER");
	this->menuText.setPosition(
		(this->container.getPosition().x + this->container.getSize().x / 2.f - this->menuText.getGlobalBounds().width / 2.f) - 140.f,
		this->container.getPosition().y + 40.f
	);

	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initButtons();
	this->initKeybinds();
	//this->initMusic();
}

GameOverState::~GameOverState()
{
	auto i = this->buttons.begin();
	for (i = this->buttons.begin(); i != this->buttons.end(); ++i)
	{
		delete i->second;
	}
}

const bool GameOverState::isButtonPressed(const std::string key)
{
	return this->buttons[key]->isPressed();
}

void GameOverState::addButton(const std::string key, float y, const std::string text)
{
	float width = 250.f;
	float height = 50.f;
	float x = this->container.getPosition().x + this->container.getSize().x / 2.f - width / 2.f;

	this->buttons[key] = new gui::Button(
		x, y, width, height,
		&this->font, text, 50,
		sf::Color(80, 80, 80, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
}

void GameOverState::endState()
{
	//this->bg_music.stop();
	std::cout << "Ending Game Over State" << std::endl;
}

void GameOverState::updateButtons()
{
	/*Update all the buttons and handle the functionality*/
	for (auto& i : this->buttons)
	{
		i.second->update(mousePosWindow);
	}

	//New Game
	if (this->buttons["GAME_STATE"]->isPressed())
	{
		this->states->push(new GameState(this->stateData));
		this->bg_music.stop();
	}
}

void GameOverState::updateInput(const float& dt)
{
	//this->checkForQuit();
}

void GameOverState::update(const float& dt)
{
	//this->updateMousePosition();
	this->updateInput(dt);
	this->updateButtons();
}

std::map<std::string, gui::Button*>& GameOverState::getButtons()
{
	return this->buttons;
}

void GameOverState::renderButtons(sf::RenderTarget& target)
{
	for (auto& i : this->buttons)
	{
		i.second->render(target);
	}
}

void GameOverState::render(sf::RenderTarget* target)
{
	target->draw(this->container);

	for (auto& i : this->buttons)
	{
		i.second->render(*target);
	}

	target->draw(this->menuText);

	target->draw(this->background);
}