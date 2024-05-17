#pragma once


#include <iostream>
#include "PlayerEntity.hpp"

#include <SFML/Window/Keyboard.hpp>

class Enemy : public PlayerEntity
{
public:
    Enemy(bool main_player, const float& width, const float& length)
        : PlayerEntity(main_player, width, length) {}

    void notify_of_ball_position(const sf::RectangleShape& ball_rect);
    void handle_move() override;

private:
    float m_target_y{ 0.f };
};

void Enemy::notify_of_ball_position(const sf::RectangleShape& ball_rect)
{
    m_target_y = ball_rect.getPosition().y;
}

void Enemy::handle_move()
{
    if (_rect.getPosition().y >= 0 && _rect.getPosition().y <= 1080 - _length)
    {
        float ball_mid_y = m_target_y + 10.f;       
        float paddle_mid_y = _rect.getPosition().y + (_length * 0.5);

        if (ball_mid_y >= paddle_mid_y)
        {
            _rect.move(0.f, 2.f);
        }
        else
        {
            _rect.move(0.f, -2.f);
        }
    }
    else
    {
        float y_value = _rect.getPosition().y;
        
        if (y_value <= 0)
        {
            _rect.setPosition(_rect.getPosition().x, 0);
        }
        else if (y_value >= 1080 - _length)
        {
            _rect.setPosition(_rect.getPosition().x, 1080 - _length);
        }
    }
}