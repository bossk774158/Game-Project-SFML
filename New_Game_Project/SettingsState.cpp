#include "SettingsState.h"

void SettingsState::initVariables()
{
	this->modes = sf::VideoMode::getFullscreenModes();
}

void SettingsState::initBackground()
{
	this->background.setSize(
		sf::Vector2f
		(
			static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)
		)
	);
	if (!this->bgTexture.loadFromFile("Resources/Images/Backgrounds/mainmenu_bg.png"))
	{
		throw "Error to download Background";
	}

	this->background.setTexture(&this->bgTexture);
}

void SettingsState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Rodwick.otf"))
	{
		throw("Error to download font");
	}
	if (!this->fontNumber.loadFromFile("Fonts/Fun Games.ttf"))
	{
		throw("Error to download font");
	}
}

void SettingsState::initKeybinds()
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

void SettingsState::initGui()
{
	this->buttons["BACK"] = new gui::Button(
		this->p2pX(83.33f), this->p2pY(87.96f),
		this->p2pX(7.81f), this->p2pY(4.63f),
		&this->font, "Back", 30,
		sf::Color(20, 20, 20, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["APPLY"] = new gui::Button(
		this->p2pX(72.91f), this->p2pY(87.96f),
		this->p2pX(7.81f), this->p2pY(4.63f),
		&this->font, "Apply", 30,
		sf::Color(20, 20, 20, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	std::vector<std::string> modes_str;
	for (auto &i : this->modes)
	{
		modes_str.push_back(std::to_string(i.width) + 'x' + std::to_string(i.height));
	}

	this->dropdownList["RESOLUTION"] = new gui::DropDonwList(800, 400, 200, 50, fontNumber, modes_str.data() , modes_str.size());
}

void SettingsState::initText()
{
	this->optionsText.setFont(this->font); 
	this->optionsText.setPosition(sf::Vector2f(888.f, 250.f));
	this->optionsText.setCharacterSize(30);
	this->optionsText.setFillColor(sf::Color(255, 255, 255, 200));

	this->optionsText.setString("Resolution");
}

SettingsState::SettingsState(StateData* state_data)
	: State(state_data)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initGui();
	this->initText();
}

SettingsState::~SettingsState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}

	auto it2 = this->dropdownList.begin();
	for (it2 = this->dropdownList.begin(); it2 != this->dropdownList.end(); ++it2)
	{
		delete it2->second;
	}

}


//Accessors


//Funstions
void SettingsState::updateInput(const float& dt)
{

}

void SettingsState::updateGui(const float& dt)
{
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosWindow);
	}

	//Quit the game
	if (this->buttons["BACK"]->isPressed())
	{
		this->endState();
	}

	//Apply selected settings
	if (this->buttons["APPLY"]->isPressed())
	{
		//TEST REMOVE LATER
		this->stateData->gfxSettings->resolution = this->modes[this->dropdownList["RESOLUTION"]->getActiveElementId()];

		this->window->create(this->stateData->gfxSettings->resolution, this->stateData->gfxSettings->title, sf::Style::Default);
	}


	//Dropdown lists
	for (auto& it : this->dropdownList)
	{
		it.second->update(this->mousePosWindow,dt);
	}

	//Dropdown list functionality

}

void SettingsState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);

	this->updateGui(dt);

	
}

void SettingsState::renderGui(sf::RenderTarget& target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}

	for (auto& it : this->dropdownList )
	{
		it.second->render(target);
	}
}

void SettingsState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);

	this->renderGui(*target);

	target->draw(this->optionsText);

	//REMOVE LATER
	sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);
	mouseText.setFont(this->fontNumber);
	mouseText.setCharacterSize(12);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());
	target->draw(mouseText);
}