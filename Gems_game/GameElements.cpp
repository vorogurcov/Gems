#include "GameElements.h"
#include "GameFunctions.h"

namespace GameElements
{
	std::vector<sf::Vector2i> Bonus::ReleaseBonus(std::vector<std::vector<Square>>& GameField, sf::Vector2i& ToPos, sf::Vector2i& FromPos)
	{
		//NO BONUS
		return* new std::vector<sf::Vector2i>;
	}

	std::vector<sf::Vector2i> Bomb::ReleaseBonus(std::vector<std::vector<Square>>& GameField, sf::Vector2i& ToPos,sf::Vector2i& FromPos)
	{
		std::vector<sf::Vector2i> DeletedSquares;
		DestroySquare(GameField, ToPos);
		DeletedSquares.push_back(ToPos);
		for (size_t i = 0; i < 4; i++)
		{
			sf::Vector2i toBeDeletedPos;
			do {
				toBeDeletedPos.x = rand() % 8;
				toBeDeletedPos.y = rand() % 8;
			}
			while (GameField[toBeDeletedPos.x][toBeDeletedPos.y].getFillColor() == sf::Color::Black);
				
			DestroySquare(GameField, toBeDeletedPos);
			DeletedSquares.push_back(toBeDeletedPos);
		}
		delete GameField[ToPos.x][ToPos.y].GetBonus();
		return DeletedSquares;
	}

	

	std::vector<sf::Vector2i> ReDrawer::ReleaseBonus(std::vector<std::vector<Square>>& GameField, sf::Vector2i& ToPos, sf::Vector2i& FromPos)
	{
		
		sf::Color lastColor = GameField[FromPos.x][FromPos.y].getFillColor();
		if (lastColor == sf::Color::Black)
			return *new std::vector<sf::Vector2i>;

		for (size_t i = 0; i < 2; i++)
		{
			sf::Vector2i toBeReDrawedPos(rand() % 2 + 2, rand() % 2 + 2);
			bool canBeGenerated = false;
			int tempx = ToPos.x, tempy = ToPos.y;
			while (!canBeGenerated)
			{
				tempx = ToPos.x;
				tempy = ToPos.y;
				
				int var = rand() % 4;
				switch (var)
				{
				case 0:
					tempx += toBeReDrawedPos.x;
					tempy += toBeReDrawedPos.y;
					canBeGenerated = (tempx  < GameFieldSize && tempy < GameFieldSize);
					break;
				case 1:
					tempx += toBeReDrawedPos.x;
					tempy -= toBeReDrawedPos.y;
					canBeGenerated = (tempx < GameFieldSize && tempy >= 0);
					break;
				case 2:
					tempx -= toBeReDrawedPos.x;
					tempy += toBeReDrawedPos.y;
					canBeGenerated = (tempx >=0 && tempy < GameFieldSize);
					break;
				case 3:
					tempx -= toBeReDrawedPos.x;
					tempy -= toBeReDrawedPos.y;
					canBeGenerated = (tempx >= 0 && tempy >= 0);
					break;

				if (canBeGenerated == true && (GameField[tempx][tempy].getFillColor() == sf::Color::Black))
					canBeGenerated = false;
				}

				
			}

			GameField[tempx][tempy].setFillColor(lastColor);
			
		}
		delete GameField[ToPos.x][ToPos.y].GetBonus();
		return *new std::vector<sf::Vector2i>;
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

	void Square::SetBonus(Bonus* bns)
	{
		_bns = bns;
	}

	std::vector<sf::Vector2i> Square::ReleaseBonus(std::vector<std::vector<Square>>& GameField,sf::Vector2i& ToPos,sf::Vector2i& FromPos)
	{
		return (*_bns).ReleaseBonus(GameField,ToPos,FromPos);
	};

	Bonus* Square::GetBonus()
	{
		return _bns;
	};
	
}