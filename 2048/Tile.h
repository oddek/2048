#pragma once
#include <vector>
#include <iostream>
#include <SFML\Graphics.hpp>
#include <math.h>

class Tile : public sf::RectangleShape
{
public:
	Tile(int _value);
	~Tile();

	int value;
	sf::Text text;
	int size = 180;

	static sf::Font font;
	static std::vector<unsigned int> color_hex;

	void update_text_and_color();
};