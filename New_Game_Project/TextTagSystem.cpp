#include "TextTagSystem.h"

void TextTagSystem::initVariables()
{

}

void TextTagSystem::initFonts(std::string font_file)
{
	if (this->font.loadFromFile(font_file))
		std::cout << "ERROR LOAD FONT TEXTTAG" << font_file << "\n";
}

void TextTagSystem::initTagTemplates()
{
	this->tagTemplates[DEFAULT_TAG] = new TextTag(this->font, "lol", 0.f, 0.f,0.f,-1.f, sf::Color::Red, 50, 1000.f, 200.f);
}

TextTagSystem::TextTagSystem(std::string font_file)
{
	this->initFonts(font_file);
	this->initVariables();
	this->initTagTemplates();
}

TextTagSystem::~TextTagSystem()
{
	//Clean up tag
	for (auto* tag : this->tags)
	{
		delete tag;
	}
	//Clean up templates
	for (auto& tag : this->tagTemplates)
	{
		delete tag.second;
	}
}

void TextTagSystem::addTextTag(unsigned tag_type)
{
	this->tags.push_back(new TextTag(*this->tagTemplates[DEFAULT_TAG]));
}

void TextTagSystem::removeTextTag()
{

}

void TextTagSystem::update(const float& dt)
{
	for (auto& tag : this->tags)
	{
		tag->update(dt);
	}
}

void TextTagSystem::render(sf::RenderTarget& target)
{
	for (auto& tag : this->tags)
	{
		tag->render(target);
	}
}
