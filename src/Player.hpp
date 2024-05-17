#pragma once

#include "PlayerEntity.hpp"

#include <SFML/Window/Keyboard.hpp>

class Player : public PlayerEntity
{
public:
	Player(bool main_player, const float& width, const float& length)
		: PlayerEntity(main_player, width, length) {}

	void handle_move() override;

private:
};

void Player::handle_move()
{
    constexpr float max_velocity = 20.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        if (_rect.getPosition().y >= 0)
        {
            _rect.move(sf::Vector2(0.f, -3.f));
        }

    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        if (_rect.getPosition().y <= _window_y_size - _length)
        {
            _rect.move(sf::Vector2(0.f, 3.f));
        }
    }
}