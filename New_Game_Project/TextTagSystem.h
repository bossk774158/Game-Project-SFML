#pragma once
#include<iostream>
#include<ctime>
#include<cstdlib>
#include<vector>
#include<fstream>
#include<sstream>
#include<stack>
#include<map>
#include<math.h>

#include <SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
#include<SFML/System.hpp>

enum TAGTYPES {DEFAULT_TAG, NEGATIVE_TAG, POSITIVE_TAG, EXP_TAG, ENVIRONMENTAL_TAG};

class TextTagSystem
{
private:
	class TextTag
	{
	private:
		sf::Text text;
		float dirY;
		float dirX;
		float lifetime;
		float speed;

	public:
		TextTag(sf::Font& font, std::string text,
			float pos_x, float pos_y,
			float dir_x, float dir_y,
			sf::Color color,
			unsigned char_size,
			float lifetime, float speed)
		{
			this->text.setFont(font);
			this->text.setPosition(pos_x, pos_y);
			this->text.setFillColor(color);
			this->text.setCharacterSize(char_size);
			this->text.setString(text);

			this->dirX = dir_x;
			this->dirY = dir_y;
			this->lifetime = lifetime;
			this->speed = speed;
		}
		~TextTag()
		{

		}

		//accessors
		inline const bool canBeRemove() const { return this->lifetime <= 0.f; }

		void update(const float& dt)
		{
			if (this->lifetime >= 0.f)
			{
				//update the lifetime
				this->lifetime -= 100.f * dt;

				//move the tag
				this->text.move(this->dirX * this->speed * dt, this->dirY * this->speed * dt);
			}
		}
		void render(sf::RenderTarget& target)
		{
			target.draw(this->text);
		}
	};

	sf::Font font;
	std::map<unsigned, TextTag*> tagTemplates;
	std::vector<TextTag*> tags;

	void initVariables();
	void initFonts(std::string font_file);
	void initTagTemplates();

public:
	TextTagSystem(std::string font_file);
	virtual ~TextTagSystem();

	void addTextTag(unsigned tag_type);
	void removeTextTag();

	void update(const float& dt);
	void render(sf::RenderTarget& target);
};

