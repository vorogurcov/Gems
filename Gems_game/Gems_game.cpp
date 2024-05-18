#include "GameElements.h"
#include "GameFunctions.h"

namespace ge = GameElements;

int main()
{
    srand(time(0));
    sf::RenderWindow window(sf::VideoMode(800, 800), "Gems");
    bool isChanged = false;



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

            }

        }
        window.clear(sf::Color::Black);

        std::vector<std::vector<ge::Square>> GameField = ge::GenerateGameField();

        ge::DrawGameField(window,GameField);

        
        window.display();
    }

    return 0;
}