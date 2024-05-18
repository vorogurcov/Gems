#pragma once


#ifndef GAME_ELEMENTS_H
#define GAME_ELEMENTS_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
namespace GameElements
{
	class Bonus
	{
	public:
		virtual void ReleaseBonus();
	};

	class Bomb : public Bonus
	{
	public:
		void ReleaseBonus();
	};

	class ReDrawer : public Bonus
	{
	public:
		void ReleaseBonus();
	};



	class Square :public sf::RectangleShape
	{
	private:
		Bonus* _bns;
		float _size;
	public:
		Square(float const size);
		float GetSize() const;
		~Square();
	};
}
#endif // !GAME_ELEMENTS_H

