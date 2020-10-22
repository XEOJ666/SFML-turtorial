#include "Collider.h"
#include<iostream>

Collider::Collider(sf::RectangleShape& body) :
body(body)
{
}

bool Collider::CheckCollision(Collider& other, float push)
{   
    sf::Vector2f otherPosition = other.GetPosition();
    sf::Vector2f otherHalfSize = other.GetHalfSize();
    sf::Vector2f thisPosition  = GetPosition();
    sf::Vector2f thisrHalfSize = GetHalfSize();

    float deltaX = otherPosition.x - thisPosition.x;
    float deltaY = otherPosition.y - thisPosition.y;    
    float intersectX = abs(deltaX) - (otherHalfSize.x + thisrHalfSize.x);
    float intersectY = abs(deltaY) - (otherHalfSize.y + thisrHalfSize.y);

    if (intersectX < 0.0f && intersectY < 0.0f)
    {
        push = std::min(std::max(push, 0.0f), 0.5f);

        if (intersectX > intersectY)
        {
            if (deltaX > 0.0f)
            {
                Move(intersectX * (1.0f - push), 0.0f);
                other.Move(-intersectX * push, 0.0f);
            }
            else
            {
                Move(-intersectX * (1.0f - push), 0.0f);
                other.Move(intersectX * push, 0.0f);
            }
            std::cout << "Collision >> Praaaawiid" << std::endl;
        }
        else
        {
            if (deltaY > 0.0f)
            {
                Move(0.0f, intersectY * (1.0f - push));
                other.Move(0.0f, -intersectY * push);
            }
            else
            {
                Move(0.0f, -intersectY * (1.0f - push));
                other.Move(0.0f, intersectY * push);
            }
            std::cout << "Collision >> Biig Pomd" << std::endl;
        }
        return true;
    }
    return false;
}
