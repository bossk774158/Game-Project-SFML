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
		float acceleration;
		sf::Vector2f velocity;
		int fadeValue;

	public:
		TextTag(sf::Font& font, std::string text,
			float pos_x, float pos_y,
			float dir_x, float dir_y,
			sf::Color color,
			unsigned char_size,
			float lifetime, float speed, float acceleration, int fade_value)
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
			this->acceleration = acceleration;
			this->fadeValue = fade_value;
		}

		TextTag(TextTag* tag, float pos_x, float pos_y, std::string str)
		{
			this->text = tag->text;
			this->text.setString(str);
			this->text.setPosition(pos_x, pos_y);

			this->dirX = tag->dirX;
			this->dirY = tag->dirY;
			this->lifetime = tag->lifetime;
			this->speed = tag->speed;
			this->acceleration = tag->acceleration;
			this->fadeValue = tag->fadeValue;
		}

		~TextTag()
		{

		}

		//accessors
		inline const bool isExpired() const { return this->lifetime <= 0.f; }

		void update(const float& dt)
		{
			if (this->lifetime >= 0.f)
			{
				//update the lifetime
				this->lifetime -= 100.f * dt;

				//Accelerate
				if (this->acceleration > 0.f)
				{
					this->velocity.x += this->dirX * this->acceleration * dt;
					this->velocity.y += this->dirY * this->acceleration * dt;

					if (abs(this->velocity.x) > this->speed)
						this->velocity.x = this->dirX * this->speed;

					if (abs(this->velocity.y) > this->speed)
						this->velocity.y = this->dirY * this->speed;

					this->text.move(this->velocity * dt);
				}
				else
				{
					//move the tag
					this->text.move(this->dirX * this->speed * dt, this->dirY * this->speed * dt);
				}

				if (fadeValue > 0 && text.getFillColor().a >= this->fadeValue)
				{
					this->text.setFillColor
					(
						sf::Color(
							this->text.getFillColor().r,
							this->text.getFillColor().g,
							this->text.getFillColor().b,
							this->text.getFillColor().a - this->fadeValue
						)
					);
				}

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

	void addTextTag(const unsigned tag_type, const float pos_x,const float pos_y, const std::string str, const std::string prefix, const std::string postfix);
	void addTextTag(const unsigned tag_type, const float pos_x, const float pos_y, const int i, const std::string prefix, const std::string postfix);
	void addTextTag(const unsigned tag_type, const float pos_x, const float pos_y, const float f, const std::string prefix, const std::string postfix);

	void update(const float& dt);
	void render(sf::RenderTarget& target);
};

