#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>



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
	


	class Square:public sf::RectangleShape
	{
	private:
		Bonus* _bns;
		float _size;
	public:
		Square(float const size);
		float GetSize() const;
		~Square();
	}
	;
}