#include "GameElements.h"

namespace GameElements
{
	void Bonus::ReleaseBonus()
	{

	}

	void Bomb::ReleaseBonus()
	{

	}

	void ReDrawer::ReleaseBonus()
	{

	}

	Square::Square(float const size) : RectangleShape(*new sf::Vector2f(size, size)), _size(size), _bns(NULL)
	{};

	Square::~Square()
	{
		delete _bns;
	}
	float Square::GetSize() const
	{
		return _size;
	};
}