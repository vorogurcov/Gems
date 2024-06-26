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
	std::vector<sf::Vector2i> ReplaceAndDeleteSquares(sf::RenderWindow& window,std::vector<std::vector<Square>>& GameField, int const FirstSquareX, int const FirstSquareY);
	bool isEqual(int const First_x, int const First_y, int const Second_x, int const Second_y);
	bool isNear(int const First_x, int const First_y, int const Second_x, int const Second_y);
	void swap_colors(Square& s1, Square& s2);
	void clear(std::vector<sf::Vector2i>& q);
	bool isInVector(std::vector<sf::Vector2i>& q, sf::Vector2i& vec);
	void FindSquaresToDelete(std::vector<sf::Vector2i>& DeletedSquares, std::vector<std::vector<Square>>& GameField, int SquareX, int SquareY);
	void DeleteSquares(std::vector<std::vector<Square>>& GameField, std::vector<sf::Vector2i>& SqToDelete);
	bool compareByY(sf::Vector2i const& a, sf::Vector2i const& b);
	void FillDeletedSquares(std::vector<sf::Vector2i>& vec, std::vector<std::vector<Square>>& GameField);
	void DestroySquare(std::vector<std::vector<Square>>& GameField, sf::Vector2i& pos);
	void SwapSquares(std::vector<std::vector<Square>>& GameField, sf::Vector2i& pos1, sf::Vector2i& pos2);
	void swap_bonuses(Square& s1, Square& s2);
	std::vector<sf::Vector2i> ReleaseAllBonuses(std::vector<std::vector<Square>>& GameField, std::vector<std::pair<sf::Vector2i, sf::Vector2i>>& FromToPairs);
	std::vector<std::pair<sf::Vector2i, sf::Vector2i>> RandomlyGenerateBonus(std::vector<std::vector<Square>>& GameField, std::vector<sf::Vector2i>& DeletedSquares);
	bool isInVector(std::vector<std::pair<sf::Vector2i, sf::Vector2i>>& vec, sf::Vector2i& v);
}


#define GAME_FUNCTIONS_H



#endif // !GAME_FUNCTIONS_H
