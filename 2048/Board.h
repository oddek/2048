#pragma once
#include "Tile.h"
class Board : public sf::RectangleShape
{
public:
	Board();
	~Board();
	int points = 0;
	bool game_over = false;
	std::vector<std::vector<Tile*>> grid;
	std::vector<sf::RectangleShape> back_rects;

	void gen_tile();
	bool move_left();
	bool move_right();
	bool move_up();
	bool move_down();
	void update_pixel_positions(sf::RenderWindow& window);
};

