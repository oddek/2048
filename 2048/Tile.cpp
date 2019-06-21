#include "Tile.h"

sf::Font Tile::font;
std::vector<unsigned int> Tile::color_hex;

Tile::Tile(int _value) : value(_value)
{
	color_hex = { 0xe6194bff, 0x3cb44bff, 0xffe119ff, 0x4363d8ff, 0xf58231ff, 0x911eb4ff, 0x46f0f0ff, 0xf032e6ff, 0xbcf60cff, 0xfabebeff, 0x008080ff, 0xe6beffff, 0x9a6324ff, 0xfffac8ff, 0x800000ff, 0xaaffc3ff, 0x808000ff, 0xffd8b1ff, 0x000075ff, 0x808080ff};
	font.loadFromFile("fonts/SummitLight-Display.ttf");
	setSize( sf::Vector2f(size, size) );
	setFillColor(sf::Color::Color(color_hex[log2(value) - 1]));
	
	text.setCharacterSize(40);
	text.setString(std::to_string(value));
	text.setFillColor(sf::Color::Color::Black);
	text.setFont(font);
	text.setStyle(sf::Text::Bold);

	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);

	text.setPosition({ getPosition().x + size / 2, getPosition().y + size / 2 });
}


Tile::~Tile()
{
}


void Tile::update_text_and_color()
{
	text.setString(std::to_string(value));
	setFillColor(sf::Color::Color(color_hex[log2(value) - 1]));
	//Center text
	sf::FloatRect rectBounds = getGlobalBounds();
	sf::FloatRect textBounds = text.getGlobalBounds();

	text.setPosition(
		rectBounds.left + (rectBounds.width / 2) - (textBounds.width / 2),
		rectBounds.top + (rectBounds.height / 2) - (textBounds.height / 2));
}

