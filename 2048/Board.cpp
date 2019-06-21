#include "Board.h"



Board::Board()
{
	//Set up grid
	grid = std::vector<std::vector<Tile*>>(4, std::vector<Tile*>(4, nullptr));
	//Setting up board and background
	setSize({ 770, 770 });
	setFillColor(sf::Color::Color(0x645B5Bff));
	sf::Vector2f pos(10, 10);
	int ind;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			sf::RectangleShape r;
			r.setFillColor(sf::Color::Color(0xB5AFAFff));
			r.setPosition(pos);
			r.setSize({ 180,180 });
			pos.x += 190;
			back_rects.push_back(r);
		}
		pos.x = 10;
		pos.y += 190;
	}
	//Start with one tile generated
	gen_tile();
}

Board::~Board()
{
	for (auto i : grid)
		for (auto j : i) delete j;
}

void Board::gen_tile()
{
	//Find all empty squares, pick one at random from them
	std::vector<int> rows;
	std::vector<int> cols;
	for (int i = 0; i < grid.size(); i++)
	{
		for (int j = 0; j < grid.size(); j++)
		{
			if (grid[j][i] == nullptr)
			{
				cols.push_back(j);
				rows.push_back(i);
			}
		}
	}
	if (rows.size() == 0)
	{
		game_over = true;
		return;
	}
	//One of ten tiles should spawn as 4, rest as 2.
	int val = rand() % 10;
	if (val != 4) val = 2;

	Tile* t = new Tile(val);
	int index = rand() % rows.size();

	//Set position
	grid[cols[index]][rows[index]] = t;
	t->setPosition((cols[index]+1) * 10 + (cols[index]) * 180, (rows[index]+1) * 10 + rows[index] * 180);
	t->text.setPosition({ 
		grid[cols[index]][rows[index]]->getPosition().x + grid[cols[index]][rows[index]]->size / 2, 
		grid[cols[index]][rows[index]]->getPosition().y + grid[cols[index]][rows[index]]->size / 2 });
}

bool Board::move_left()
{
	int curr;
	bool moved = false;
	
	for (int row = 0; row < grid.size(); row++)
	{
		sf::Vector2i already_merged(-1, -1);
		for (int col = 1; col < grid.size(); col++)
		{
			
			if (grid[col][row] == nullptr) continue;
			curr = col;
			for (int to_col = col - 1; to_col >= 0; to_col--)
			{
				if (grid[to_col][row] != nullptr && 
					(grid[to_col][row]->value != grid[curr][row]->value ||
					already_merged == sf::Vector2i(to_col, row))) break;
				
				if (grid[to_col][row] == nullptr) { grid[to_col][row] = grid[curr][row]; }
				else
				{
					grid[to_col][row]->value += grid[curr][row]->value;
					grid[to_col][row]->update_text_and_color();
					points += 2 * grid[curr][row]->value;
					moved = true;
					grid[curr][row] = nullptr;
					already_merged = { to_col, row };
					break;	
				}
				moved = true;
				grid[curr][row] = nullptr;
				curr--;
			}
		}
	}
	return moved;
}

bool Board::move_right()
{
	int curr;
	bool moved = false;
	for (int row = 0; row < grid.size(); row++)
	{
		sf::Vector2i already_merged(-1, -1);
		for (int col = grid.size() - 2; col >=0; col--)
		{
			if (grid[col][row] == nullptr) continue;
			curr = col;
			for (int to_col = col + 1; to_col < grid.size(); to_col++)
			{
				if (grid[to_col][row] != nullptr && 
					(grid[to_col][row]->value != grid[curr][row]->value
						|| already_merged == sf::Vector2i(to_col, row))) break;

				if (grid[to_col][row] == nullptr) { grid[to_col][row] = grid[curr][row]; }
				else
				{
					grid[to_col][row]->value += grid[curr][row]->value;
					grid[to_col][row]->update_text_and_color();
					points += 2 * grid[curr][row]->value;
					moved = true;
					grid[curr][row] = nullptr;
					already_merged = { to_col, row };
					break;
				}
				moved = true;
				grid[curr][row] = nullptr;
				curr++;
			}
		}
	}
	return moved;
}

bool Board::move_up()
{
	int curr;
	bool moved = false;
	for (int col = 0; col < grid.size(); col++)
	{
		sf::Vector2i already_merged(-1, -1);
		for (int row = 1; row < grid.size(); row++)
		{
			if (grid[col][row] == nullptr) continue;
			curr = row;
			for (int to_row = row - 1; to_row >= 0; to_row--)
			{
				if (grid[col][to_row] != nullptr && 
					(grid[col][to_row]->value != grid[col][curr]->value ||
						already_merged == sf::Vector2i(col, to_row))) break;

				if (grid[col][to_row] == nullptr) { grid[col][to_row] = grid[col][curr]; }
				else
				{
					grid[col][to_row]->value += grid[col][curr]->value;
					grid[col][to_row]->update_text_and_color();
					points += 2 * grid[col][curr]->value;

					moved = true;
					grid[col][curr] = nullptr;
					already_merged = { col, to_row };
					break;
				}
				moved = true;
				grid[col][curr] = nullptr;
				curr--;
			}
		}
	}
	return moved;
}

bool Board::move_down()
{
	int curr;
	bool moved = false;
	for (int col = 0; col < grid.size(); col++)
	{
		sf::Vector2i already_merged(-1, -1);
		for (int row = grid.size()-2; row >=0; row--)
		{
			if (grid[col][row] == nullptr) continue;
			curr = row;
			for (int to_row = row + 1; to_row < grid.size(); to_row++)
			{
				if (grid[col][to_row] != nullptr && 
					(grid[col][to_row]->value != grid[col][curr]->value ||
						already_merged == sf::Vector2i(col, to_row))) break;

				if (grid[col][to_row] == nullptr) { grid[col][to_row] = grid[col][curr]; }
				else
				{
					grid[col][to_row]->value += grid[col][curr]->value;
					grid[col][to_row]->update_text_and_color();
					points += 2 * grid[col][curr]->value;
					moved = true;
					grid[col][curr] = nullptr;
					already_merged = { col, to_row };
					break;
				}
				moved = true;
				grid[col][curr] = nullptr;
				curr++;
			}
		}
	}
	return moved;
}

void Board::update_pixel_positions(sf::RenderWindow& window)
{
	sf::Vector2f pos(10, 10);
	for (int row = 0; row < grid.size(); row++)
	{
		for (int col = 0; col < grid[row].size(); col++)
		{
			if (grid[col][row] != nullptr)
			{
				int dx = (pos.x - grid[col][row]->getPosition().x) / 10;
				int dy = (pos.y - grid[col][row]->getPosition().y) / 10;
				//Everything here is just to give the feel of movement
				//Could probably be solved in a better way
				for (int i = 0; i < 10; i++)
				{
					if (grid[col][row]->getPosition().x != pos.x)
					{
						
						grid[col][row]->setPosition(grid[col][row]->getPosition().x + dx, grid[col][row]->getPosition().y);
					}
					else grid[col][row]->setPosition(grid[col][row]->getPosition().x, grid[col][row]->getPosition().y + dy);
					
					grid[col][row]->update_text_and_color();

					window.clear();
					window.draw(*this);
					for (auto i : back_rects) window.draw(i);
					for (auto i : grid)
						for (auto j : i)
							if (j != nullptr)
							{
								window.draw(*j);
								window.draw(j->text);
							}
					window.display();
				}
				grid[col][row]->setPosition(pos);
				grid[col][row]->update_text_and_color();
			}
			pos.x += 190;
		}
		pos.x = 10;
		pos.y += 190;
	}
}