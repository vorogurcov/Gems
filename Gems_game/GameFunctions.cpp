#include "GameFunctions.h"
#include "GameElements.h"

const int GameFieldSize = 8;

namespace GameElements
{
    class Square;

    std::vector<std::vector<Square>> GenerateGameField()
    {
        std::vector<std::vector<Square>> elements(8);

        for (size_t i = 0; i < GameFieldSize; i++)
        {
            for (size_t j = 0; j < GameFieldSize; j++)
            {
                elements[i].push_back(*new Square(50));
                elements[i][j].setFillColor(GetRandomColor());
                elements[i][j].setPosition(i * 80, j * 80);
            }
        }
        return elements;
    }

    sf::Color GetRandomColor()
    {
        int num = rand() % 5;
        switch (num)
        {
        case 1:
            return sf::Color::Cyan;
            break;
        case 2:
            return sf::Color::Red;
            break;
        case 3:
            return sf::Color::Blue;
            break;
        case 4:
            return sf::Color::White;
            break;
        default:
            return sf::Color::Green;
            break;
        }
    }

    void DrawGameField(sf::RenderWindow& window, std::vector<std::vector<Square>> const& elements)
    {
        for (size_t i = 0; i < GameFieldSize; i++)
            for (size_t j = 0; j < GameFieldSize; j++)
                window.draw(elements[i][j]);
    }


}