#pragma once

#ifndef GAME_FUNCTIONS_H
#include <SFML/Graphics.hpp>



namespace GameElements
{
	class Square;

	sf::Color GetRandomColor();
	std::vector<std::vector<Square>> GenerateGameField();
	void DrawGameField(sf::RenderWindow& window, std::vector<std::vector<Square>> const& elements);
}


#define GAME_FUNCTIONS_H



#endif // !GAME_FUNCTIONS_H
