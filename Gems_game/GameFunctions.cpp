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

    void swap_bonuses(Square& s1, Square& s2)
    {
        Bonus* temp = s1.GetBonus();
        s1.SetBonus(s2.GetBonus());
        s2.SetBonus(temp);
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

    std::vector<sf::Vector2i> DeleteCompletely( std::vector<std::vector<Square>>& GameField, int const FirstSquareX, int const FirstSquareY)
    {
        std::vector<sf::Vector2i> vec;
        int size = 0;
        do
        {
            size = vec.size();
            FindSquaresToDelete(vec, GameField, FirstSquareX, FirstSquareY);
        } while (vec.size() != size);

        DeleteSquares(GameField, vec);
        return vec;
    }

    std::vector<sf::Vector2i> ReplaceAndDeleteSquares(sf::RenderWindow& window,std::vector<std::vector<Square>>& GameField, int const FirstSquareX, int const FirstSquareY)
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

                        if (GameField[SecondSquareX][SecondSquareY].getFillColor() == sf::Color::Black)
                            return *new std::vector<sf::Vector2i>(0);

                        if (isNear(FirstSquareX, FirstSquareY, SecondSquareX, SecondSquareY))
                        {
                            sf::Vector2i pos1(FirstSquareX,FirstSquareY), pos2(SecondSquareX,SecondSquareY);
                            SwapSquares(GameField, pos1, pos2);
                            std::vector<sf::Vector2i> vec1, vec2;
                            if(GameField[FirstSquareX][FirstSquareY].getFillColor() != sf::Color::Black)
                                vec1 = DeleteCompletely(GameField, FirstSquareX, FirstSquareY);
                            if (GameField[SecondSquareX][SecondSquareY].getFillColor() != sf::Color::Black)
                                vec2 = DeleteCompletely(GameField, SecondSquareX, SecondSquareY);

                            vec1.insert(vec1.end(), vec2.begin(), vec2.end());
                            wasClicked = false;
                            
                            return vec1;
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

    void clear(std::vector<sf::Vector2i>& q)
    {
        std::vector<sf::Vector2i> empty;
        std::swap(q, empty);
    }

    bool isInVector(std::vector<sf::Vector2i>& q, sf::Vector2i& vec)
    {
        std::vector<sf::Vector2i> tempvec(q);
        int size = q.size();
        for (size_t i = 0; i < size; i++)
        {
            if (tempvec.front() == vec)
                return true;
            tempvec.erase(tempvec.begin());
        }
        return false;
    }

    void FindSquaresToDelete(std::vector<sf::Vector2i>& DeletedSquares, std::vector<std::vector<Square>>& GameField, int SquareX, int SquareY)
    {
        int CurSize = DeletedSquares.size();

        std::vector<sf::Vector2i> tempq(DeletedSquares);

        for (size_t j = 0; CurSize == 0 ? j <= CurSize : j < CurSize; j++)
        {
            if (CurSize == 0)
                ;
            else
            {
                sf::Vector2i vec = tempq.front();
                tempq.erase(tempq.begin());
                SquareX = vec.x;
                SquareY = vec.y;
            }

            for (int i = SquareY; i < GameFieldSize; i++)
            {
                sf::Vector2i* indexes = new sf::Vector2i(SquareX, i);
                if (GameField[SquareX][i].getFillColor() == GameField[SquareX][SquareY].getFillColor() &&
                    !isInVector(DeletedSquares, *indexes))
                    DeletedSquares.push_back(*indexes);
                else if (GameField[SquareX][i].getFillColor() == GameField[SquareX][SquareY].getFillColor())
                    ;
                else
                    break;
            }

            for (int i = SquareY; i >= 0; i--)
            {
                sf::Vector2i* indexes = new sf::Vector2i(SquareX, i);
                if (GameField[SquareX][i].getFillColor() == GameField[SquareX][SquareY].getFillColor()
                    && !isInVector(DeletedSquares, *indexes))
                    DeletedSquares.push_back(*indexes);
                else if (GameField[SquareX][i].getFillColor() == GameField[SquareX][SquareY].getFillColor())
                    ;
                else
                    break;
            }

            int RowDeletedElemCount = DeletedSquares.size() - CurSize;
            if (RowDeletedElemCount < 3 && CurSize == 0)
                clear(DeletedSquares), RowDeletedElemCount = 0;
            /*else if (RowDeletedElemCount < 3 && CurSize != 0)
                ;*/
            else
                RowDeletedElemCount = DeletedSquares.size();

            for (int i = SquareX; i < GameFieldSize; i++)
            {
                sf::Vector2i* indexes = new sf::Vector2i(i, SquareY);
                if (GameField[i][SquareY].getFillColor() == GameField[SquareX][SquareY].getFillColor() &&
                    !isInVector(DeletedSquares, *indexes))
                    DeletedSquares.push_back(*indexes);
                else if (GameField[i][SquareY].getFillColor() == GameField[SquareX][SquareY].getFillColor())
                    ;
                else
                    break;
            }

            for (int i = SquareX; i >= 0; i--)
            {
                sf::Vector2i* indexes = new sf::Vector2i(i, SquareY);
                if (GameField[i][SquareY].getFillColor() == GameField[SquareX][SquareY].getFillColor() &&
                    !isInVector(DeletedSquares, *indexes))
                    DeletedSquares.push_back(*indexes);
                else if (GameField[i][SquareY].getFillColor() == GameField[SquareX][SquareY].getFillColor())
                    ;
                else
                    break;
            }
            int ColDeletedElemCount = DeletedSquares.size() - RowDeletedElemCount;
            if (ColDeletedElemCount < 3 && CurSize == 0)
            {
                for (size_t i = 0; i < ColDeletedElemCount; i++)
                {
                    DeletedSquares.pop_back();
                }
            }
        }
    }

    void DeleteSquares(std::vector<std::vector<Square>>& GameField, std::vector<sf::Vector2i>& SqToDelete)
    {
        int size = SqToDelete.size();
        std::vector<sf::Vector2i> tempq(SqToDelete);
        for (size_t i = 0; i < size; i++)
        {
            sf::Vector2i vec = tempq.front();
            tempq.erase(tempq.begin());
            DestroySquare(GameField,vec);
        }
        
    }


    bool compareByY(sf::Vector2i const& a, sf::Vector2i const& b) {
        return a.y > b.y;
    }


    void FillDeletedSquares(std::vector<sf::Vector2i>& vec, std::vector<std::vector<Square>>& GameField)
    {
        for (auto it = vec.begin(); it != vec.end();)
        {
            auto& el = *it;

            for (int i = el.y; i >= 0; i--)
            {
                if (i < 0)
                    break;
                else if (GameField[el.x][i].getFillColor() != sf::Color::Black)
                {
                    
                 
                    sf::Vector2i CurPoint(el.x, el.y);
                    sf::Vector2i NewPoint(el.x, i);
                    SwapSquares(GameField,CurPoint, NewPoint);
                    vec.insert(std::lower_bound(vec.begin(), vec.end(), NewPoint, compareByY), NewPoint);
                    break;
                }

            }
            it = vec.erase(vec.begin());
        }
    }


    void DestroySquare(std::vector<std::vector<Square>>& GameField,sf::Vector2i& pos)
    {
        GameField[pos.x][pos.y].setFillColor(sf::Color::Black);
        GameField[pos.x][pos.y].SetBonus(NULL);
    }

    void SwapSquares(std::vector<std::vector<Square>>& GameField, sf::Vector2i& pos1, sf::Vector2i& pos2)
    {
        swap_colors(GameField[pos1.x][pos1.y], GameField[pos2.x][pos2.y]);
        swap_bonuses(GameField[pos1.x][pos1.y], GameField[pos2.x][pos2.y]);
    }
}