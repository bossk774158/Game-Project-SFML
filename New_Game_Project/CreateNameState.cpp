#include "CreateNameState.h"

void CreateNameState::initVariables()
{
	//this->player = new Player();
	this->player->setPosition(0.f, 0.f);

	this->textHolder.setFillColor(sf::Color::Transparent);
	this->textHolder.setSize(sf::Vector2f(200.f, 50.f));
	this->textHolder.setOutlineThickness(2.f);
	this->textHolder.setOutlineColor(sf::Color::White);
	this->textHolder.setPosition(sf::Vector2f());
}

void CreateNameState::initMusic()
{
	this->bg_music.openFromFile("Resources/Sound and Music/");
	this->bg_music.setLoop(true);
	this->bg_music.setVolume(10.f);
	this->bg_music.play();
}

void CreateNameState::initFont()
{
	if (!this->font.loadFromFile("Fonts/novem___.ttf"))
	{
		std::cout << "ERROR::MAINMENUSTATE::COULD NOT LOAD FONT!" << std::endl;
	}
}

void CreateNameState::initText()
{
	this->input = "";
	this->text.setFont(this->font);
	this->text.setCharacterSize(25.f);
	this->text.setPosition(sf::Vector2f(960.f, 400.f));
}

void CreateNameState::initKeybinds()
{
	std::ifstream ifs("config/createnamestate_keybinds.ini");

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

void CreateNameState::initButtons()
{
	this->buttons["GAME_STATE"] = new gui::Button(
		880.f, 500.f,
		this->p2pX(7.8f), this->p2pY(4.6f),
		&this->font, "New Game", 50,
		sf::Color(255, 255, 255, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
}

CreateNameState::CreateNameState(StateData* state_data)
	: State(state_data)
{
	this->initVariables();
	this->initMusic();
	this->initFont();
	this->initText();
	this->initKeybinds();
	this->initButtons();

}

CreateNameState::~CreateNameState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

void CreateNameState::endState()
{
	std::cout << "Ending CreateNameState" << std::endl;
}

void CreateNameState::updateButtons()
{
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosWindow);
	}

	//New game
	if (this->buttons["GAME_STATE"]->isPressed())
	{
		this->states->push(new GameState(this->stateData));
	}
}

void CreateNameState::updateInput(const float& dt)
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("NEW_GAME"))) && !this->nameString.empty())
	{
		this->player->setName(this->nameString);
		if (!this->states->empty())
			this->states->pop();
		this->states->push(new GameState(this->stateData));
		this->bg_music.stop();
	}
}

void CreateNameState::update(const float& dt)
{
	while (this->window->pollEvent(this->nameEvent))
	{
		if (this->nameEvent.type == sf::Event::TextEntered)
		{
			if (this->nameEvent.text.unicode < 128)
			{
				std::cout << "Text entered: " << (this->nameEvent.text.unicode) << std::endl;
				if (this->nameEvent.text.unicode == static_cast<sf::Uint32>(8) && this->input.getSize() > 0)
				{
					this->input.erase(this->input.getSize() - 1);
					this->nameString.erase(this->nameString.size() - 1);
				}
				else
				{
					if (this->input.getSize() < 13 && this->nameEvent.text.unicode != 13)
					{
						if (this->nameEvent.text.unicode >= 97 && this->nameEvent.text.unicode <= 122)
						{
							this->nameEvent.text.unicode -= 32;
						}
						this->input += this->nameEvent.text.unicode;
						this->nameString += this->nameEvent.text.unicode;
					}
				}

			}
		}
	}
	this->updateInput(dt);
	this->updateButtons();


	this->text.setString(this->input);
}

void CreateNameState::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void CreateNameState::render(sf::RenderTarget& target)
{
	/*if (!target)
		target = this->window;*/

	this->renderButtons(target);

	target.draw(this->textHolder);
	target.draw(this->text);
}