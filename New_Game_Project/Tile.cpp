#include "Tile.h"

Tile::Tile()
{
	this->collision = false;
	this->type = 0;
}

Tile::Tile(unsigned grid_x, unsigned grid_y, float gridSizeF, const sf::Texture& texture, const sf::IntRect& texture_rect,
	bool collision, short type)
{
	this->shape.setSize(sf::Vector2f(gridSizeF, gridSizeF));
	this->shape.setFillColor(sf::Color::White);
	//this->shape.setOutlineThickness(1.f);
	//this->shape.setOutlineColor(sf::Color::Black);
	this->shape.setPosition(static_cast<float>(grid_x * gridSizeF), static_cast<float>(grid_y * gridSizeF));
	this->shape.setTexture(&texture);
	this->shape.setTextureRect(texture_rect);

	this->collision = false;
	this->type = type;
}

Tile::~Tile()
{

}


const std::string Tile::getAsSting() const
{
	std::stringstream ss;

	ss << this->shape.getTextureRect().left << " " << this->shape.getTextureRect().top << " " << this->collision << " " << this->type;

	return ss.str();
}

//Functions
void Tile::update()
{

}

void Tile::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}
