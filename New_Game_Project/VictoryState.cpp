#include "VictoryState.h"

void VictoryState::initVariables()
{

}

void VictoryState::initMusic()
{
	if (!this->vic_music.openFromFile("Sound and Music/Victory.wav"))
	{
		std::cout << "Victory music error" << "\n";
	}
}

void VictoryState::initBackground()
{
	this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x),
		static_cast<float>(this->window->getSize().y)));

	this->background.setTexture(&this->backgroundTexture);
	this->background.setPosition(this->window->getSize().x, this->window->getSize().y);
}

void VictoryState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Fun Games.ttf"))
	{
		std::cout << "ERROR::GAME_OVER_STATE::COULD NOT LOAD FROM FILE 04FONT" << std::endl;
	}
}

void VictoryState::initButtons()
{
	float width = 250.f;
	float height = 50.f;
	float x = this->container.getPosition().x + this->container.getSize().x / 2.f - width / 2.f;

	this->buttons["EXIT_STATE"] = new gui::Button(
		x, 600.f, width, height,
		&this->font, "Back", 50,
		sf::Color(80, 80, 80, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
}

void VictoryState::initKeybinds()
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

VictoryState::VictoryState(StateData* state_data)
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
	this->menuText.setString("VICTORY");
	this->menuText.setPosition(
		(this->container.getPosition().x + this->container.getSize().x / 2.f - this->menuText.getGlobalBounds().width / 2.f) - 120.f,
		this->container.getPosition().y + 80.f
	);

	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();
	this->initMusic();
	
	this->vic_music.play();
	this->vic_music.setVolume(30.f);
	this->vic_music.setLoop(true);
}

VictoryState::~VictoryState()
{
	auto i = this->buttons.begin();
	for (i = this->buttons.begin(); i != this->buttons.end(); ++i)
	{
		delete i->second;
	}
}

const bool VictoryState::isButtonPressed(const std::string key)
{
	return this->buttons[key]->isPressed();
}

void VictoryState::addButton(const std::string key, float y, const std::string text)
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

void VictoryState::endState()
{

}

void VictoryState::updateButtons()
{
	/*Update all the buttons and handle the functionality*/
	for (auto& i : this->buttons)
	{
		i.second->update(mousePosWindow);
	}

	//Back to main menu
	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->states->pop();
		this->states->push(new MainMenuState(this->stateData));
		this->vic_music.pause();
	}
}

void VictoryState::updateInput(const float& dt)
{
	//this->checkForQuit();
}

void VictoryState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);
	this->updateButtons();
}

void VictoryState::renderButtons(sf::RenderTarget& target)
{
	for (auto& i : this->buttons)
	{
		i.second->render(target);
	}
}

void VictoryState::render(sf::RenderTarget* target)
{

	target->draw(this->container);

	for (auto& i : this->buttons)
	{
		i.second->render(*target);
	}

	target->draw(this->menuText);

	target->draw(this->background);
}
