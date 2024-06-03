#pragma once


#ifndef GAME_ELEMENTS_H
#define GAME_ELEMENTS_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
namespace GameElements
{
	
	class Bonus;

	class Square :public sf::RectangleShape
	{
	private:
		Bonus* _bns;
		float _size;
	public:
		Square(float const size);
		float GetSize() const;
		~Square();
		Bonus* GetBonus();
		void SetBonus(Bonus* bns);
		std::vector<sf::Vector2i> ReleaseBonus(std::vector<std::vector<Square>>& GameField, sf::Vector2i& ToPos, sf::Vector2i& FromPos);
	};

	class Bonus
	{
		friend std::vector<sf::Vector2i> Square::ReleaseBonus(std::vector<std::vector<Square>>& GameField, sf::Vector2i& ToPos, sf::Vector2i& FromPos);
		private:
		virtual std::vector<sf::Vector2i> ReleaseBonus(std::vector<std::vector<Square>>& GameField, sf::Vector2i& ToPos, sf::Vector2i& FromPos) = 0;
	};

	class Bomb : public Bonus
	{
		friend std::vector<sf::Vector2i> Square::ReleaseBonus(std::vector<std::vector<Square>>& GameField, sf::Vector2i& ToPos, sf::Vector2i& FromPos);
	private:
		std::vector<sf::Vector2i> ReleaseBonus(std::vector<std::vector<Square>>& GameField, sf::Vector2i& ToPos, sf::Vector2i& FromPos);
	};

	class ReDrawer : public Bonus
	{
		friend std::vector<sf::Vector2i> Square::ReleaseBonus(std::vector<std::vector<Square>>& GameField, sf::Vector2i& ToPos, sf::Vector2i& FromPos);
	private:
		std::vector<sf::Vector2i> ReleaseBonus(std::vector<std::vector<Square>>& GameField, sf::Vector2i& ToPos, sf::Vector2i& FromPos);
	};


	
}
#endif // !GAME_ELEMENTS_H

