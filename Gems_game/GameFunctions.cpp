#include "GameFunctions.h"
#include "GameElements.h"

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
                elements[i].push_back(*new Square(SquareSize));
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

    bool isClickedOnSquare(int const click_x, int const click_y)
    {
        int integer_x = click_x / 80;
        int integer_y = click_y / 80;

        int delta_x = click_x - integer_x * 80;
        int delta_y = click_y - integer_y * 80;
        if (delta_x <= SquareSize && delta_y <= SquareSize)
            return true;
        else
            return false;
    }

    void swap_colors(Square& s1, Square& s2)
    {
        sf::Color color = s2.getFillColor();
        s2.setFillColor(s1.getFillColor());
        s1.setFillColor(color);
    }

    bool isNear(int const First_x, int const First_y, int const Second_x, int const Second_y)
    {
        int delta_x = First_x - Second_x;
        int delta_y = First_y - Second_y;
        if ((fabs(delta_x) == 1 || fabs(delta_y) == 1) && ((fabs(delta_x) + fabs(delta_y)) == 1))
            return true;
        else
            return false;
    }

    bool isEqual(int const First_x, int const First_y, int const Second_x, int const Second_y)
    {
        return (First_x == Second_x) && (First_y == Second_y) ? true : false;
    }

    

    void ReplaceSquares(sf::RenderWindow& window,std::vector<std::vector<Square>>& GameField, int const FirstSquareX, int const FirstSquareY)
    {
        bool wasClicked = true;
        while (wasClicked)
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
                else if (event.type == sf::Event::MouseButtonPressed)
                {
                    if (isClickedOnSquare(event.mouseButton.x, event.mouseButton.y))
                    {
                        int SecondSquareX = event.mouseButton.x / 80;
                        int SecondSquareY = event.mouseButton.y / 80;

                        if (isNear(FirstSquareX, FirstSquareY, SecondSquareX, SecondSquareY))
                        {
                            swap_colors(GameField[FirstSquareX][FirstSquareY], GameField[SecondSquareX][SecondSquareY]);
                            wasClicked = false;
                        }
                        else if (isEqual(FirstSquareX, FirstSquareY, SecondSquareX, SecondSquareY))
                            wasClicked = false;
                        else
                            wasClicked = true;
                    }

                }
            }
        }
    }
}