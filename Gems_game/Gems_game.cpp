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
        std::vector<sf::Vector2i> DeletedSquares;
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
                    if (GameField[SquareX][SquareY].getFillColor() != sf::Color::Black)
                    {
                        DeletedSquares = ReplaceAndDeleteSquares(window, GameField, SquareX, SquareY);
                        
                        std::sort(DeletedSquares.begin(), DeletedSquares.end(), ge::compareByY);

                        isChanged = true;
                    }
                   
                }

            }

        }

        if (isChanged == true)
        {
            window.clear(sf::Color::Black);

            ge::DrawGameField(window, GameField);
            
            window.display();
            sf::Time tm(sf::seconds(1));
            sf::sleep(tm);

            isChanged = false;

            if (DeletedSquares.size() != 0)
            {
                FillDeletedSquares(DeletedSquares,GameField);
                isChanged = true;
            }
        }


    }

    return 0;
}