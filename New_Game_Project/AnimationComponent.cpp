#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet)
	:sprite(sprite),textureSheet(texture_sheet), lastAnimation(NULL)
{

}

AnimationComponent::~AnimationComponent()
{
	for (auto& i : this->animations)
	{
		delete i.second; 
	}
}

//Functions

void AnimationComponent::addAnimation(
	const std::string key,
	float animation_timer,
	int start_frames_x, int start_frames_y, int frames_x, int frames_y, int width, int height)
{
	this->animations[key] = new Animation(
		this->sprite, this->textureSheet,
		animation_timer,
		start_frames_x, start_frames_y, frames_x, frames_y, width, height);
}


void AnimationComponent::play(const std::string key, const float& dt)
{
	if (this->lastAnimation != this->animations[key])
	{
		if (this->lastAnimation == NULL)
			this->lastAnimation = this->animations[key];
		else
		{
			this->lastAnimation->reset();
			this->lastAnimation = this->animations[key];
		}
	}

	this->animations[key]->play(dt);
}

void AnimationComponent::play(const std::string key, const float& dt, const float& modifier, const float& modifier_max)
{
	if (this->lastAnimation != this->animations[key])
	{
		if (this->lastAnimation == NULL)
			this->lastAnimation = this->animations[key];
		else
		{
			this->lastAnimation->reset();
			this->lastAnimation = this->animations[key];
		}
	}

	this->animations[key]->play(dt, abs(modifier / modifier_max));
}

