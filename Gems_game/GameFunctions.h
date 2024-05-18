#pragma once

#ifndef GAME_FUNCTIONS_H
#include <SFML/Graphics.hpp>



namespace GameElements
{
	class Square;
	const int GameFieldSize = 8;
	const int SquareSize = 50;


	bool isClickedOnSquare(int const click_x, int const click_y);
	sf::Color GetRandomColor();
	std::vector<std::vector<Square>> GenerateGameField();
	void DrawGameField(sf::RenderWindow& window, std::vector<std::vector<Square>> const& elements);
	void ReplaceSquares(sf::RenderWindow& window,std::vector<std::vector<Square>>& GameField, int const FirstSquareX, int const FirstSquareY);
	bool isEqual(int const First_x, int const First_y, int const Second_x, int const Second_y);
	bool isNear(int const First_x, int const First_y, int const Second_x, int const Second_y);
	void swap_colors(Square& s1, Square& s2);
}


#define GAME_FUNCTIONS_H



#endif // !GAME_FUNCTIONS_H
