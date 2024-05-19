#include "GameElements.h"
#include "GameFunctions.h"

namespace ge = GameElements;


int main()
{
    srand(time(0));
    
    bool isChanged = true;

    std::vector<std::vector<ge::Square>> GameField = ge::GenerateGameField();;

    sf::RenderWindow window(sf::VideoMode(800, 800), "Gems", sf::Style::Close);

    while (window.isOpen())
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
                if (ge::isClickedOnSquare(event.mouseButton.x, event.mouseButton.y))
                {
                    int SquareX = event.mouseButton.x / 80;
                    int SquareY = event.mouseButton.y / 80;
                    ReplaceSquares(window,GameField, SquareX, SquareY);

                    std::vector<sf::Vector2i> vec;
                    int size = 0;
                    do
                    {
                        size = vec.size();
                        FindSquaresToDelete(vec, GameField, SquareX, SquareY);
                    } while (vec.size() != size);

                    DeleteSquares(GameField,vec);
                    isChanged = true;
                }

            }

        }

        if (isChanged == true)
        {
            window.clear(sf::Color::Black);

            ge::DrawGameField(window, GameField);
           
            window.display();

            isChanged = false;
        }


    }

    return 0;
}