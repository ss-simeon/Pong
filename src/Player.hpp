#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Keyboard.hpp>

class Player
{
public:
	Player(bool main_player, const float& width, const float& length);

	void handle_move();

	inline sf::RectangleShape get_rect() const { return _rect; }

private:
	bool _main_player;
	float _width;
	float _length;
	
	sf::Vector2f _size;
	sf::RectangleShape _rect;

	size_t _window_y_size{ 1080u };
	size_t _window_x_size{ 1920u };
};

Player::Player(bool main_player, const float& width, const float& length)
    : _main_player{ main_player }, _width{ width }, _length{ length }, _size(_width, _length), _rect(_size)
{
    float x_pos_from_side = 200.f;

    float centered_y_pos = 0.5f * (_window_y_size - _length);
    float x_pos = _main_player ? x_pos_from_side : _window_x_size - x_pos_from_side - _width;

    _rect.setPosition(sf::Vector2f(x_pos, centered_y_pos));
}

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