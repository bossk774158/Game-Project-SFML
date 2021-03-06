#include "MainMenuState.h"

void MainMenuState::initVariables()
{

}

void MainMenuState::initMusic()
{
	if (!this->main_music.openFromFile("Sound and Music/mainmenu.wav"))
	{
		std::cout << "Error to open main munu music" << "\n";
	}
}

void MainMenuState::initBackground()
{
	this->background.setSize(
		sf::Vector2f
		(
		static_cast<float>(this->window->getSize().x),
		static_cast<float>(this->window->getSize().y)
		)
	);
	if (!this->bgTexture.loadFromFile("Resources/Images/Backgrounds/Battleground3.png"))
	{
		throw "Error to download Background";
	}

	this->background.setTexture(&this->bgTexture); 
}

void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Rodwick.otf"))
	{
		throw("Error to download font");
	}
}

void MainMenuState::initKeybinds()
{
	std::ifstream ifs("Config/mainmenustate_keybinds.ini");

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

void MainMenuState::initButtons()
{
	this->buttons["GAME_STATE"] = new gui::Button(
		880.f, 500.f,
		this->p2pX(7.8f), this->p2pY(4.6f),
		&this->font, "New Game", 50,
		sf::Color(220,220, 220, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150,0), sf::Color(20, 20, 20, 0));

	this->buttons["EDITOR_STATE"] = new gui::Button(
		880.f, 750.f,
		this->p2pX(7.8f), this->p2pY(4.6f),
		&this->font, "Editor", 50,
		sf::Color(220, 220, 220, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["EXIT_STATE"] = new gui::Button(
		880.f, 850.f,
		this->p2pX(7.8f), this->p2pY(4.6f),
		&this->font, "Quit", 50,
		sf::Color(220, 220, 220, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
}

MainMenuState::MainMenuState(StateData* state_data)
	:State(state_data)
{
	this->initVariables();
	this->initMusic();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();

	this->main_music.play();
	this->main_music.setVolume(30.f);
	this->main_music.setLoop(true);
}

MainMenuState::~MainMenuState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

void MainMenuState::updateInput(const float& dt)
{
	
}

void MainMenuState::updateButtons()
{
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosWindow);
	}

	//New game
	if (this->buttons["GAME_STATE"]->isPressed())
	{
		this->states->push(new GameState(this->stateData));
		this->main_music.pause();
	}

	//Editor
	if (this->buttons["EDITOR_STATE"]->isPressed())
	{
		this->states->push(new EditorState(this->stateData));
	}

	//Quit the game
	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->endState();
	}
}

void MainMenuState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);

	this->updateButtons();

}

void MainMenuState::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);

	this->renderButtons(*target);

}