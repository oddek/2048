#include <SFML/Graphics.hpp>
#include <Windows.h>
#include "Board.h"



//TODO:
//Poeng, nytt spill knapp

int main()
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	srand(time(0));
	sf::RenderWindow window(sf::VideoMode(770, 770), "2048");
	Board board;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				return 0;
			}
			if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Left:
					if (board.move_left())
					{
						board.update_pixel_positions(window);
						board.gen_tile();
					}
					break;
				case sf::Keyboard::Right:
					if (board.move_right())
					{
						board.update_pixel_positions(window);
						board.gen_tile();
					}
					break;
				case sf::Keyboard::Up:
					if (board.move_up())
					{
						board.update_pixel_positions(window);
						board.gen_tile();
					}
					break;
				case sf::Keyboard::Down:
					if (board.move_down())
					{
						board.update_pixel_positions(window);
						board.gen_tile();
					}
					break;

				}
				std::cout << "Points: " << board.points << std::endl;

			}
		}
		window.clear();
		window.draw(board);
		for (auto i : board.back_rects) window.draw(i);
		for (auto i : board.grid)
			for (auto j : i) 
				if (j != nullptr)
				{
					window.draw(*j);
					window.draw(j->text);
				}
		window.display();
	}
	return 0;
}