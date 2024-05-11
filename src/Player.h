#pragma once

#include <SFML/Graphics/RectangleShape.hpp>

class Player
{
public:
	Player(bool main_player, const float& width, const float& length);

	void Player::handle_move();

	inline sf::RectangleShape getRect() const { return _rect; }

private:
	bool _main_player;
	float _width;
	float _length;

	float _acceleration{ 0.f };
	float _velocity{ 0.f };
	
	sf::Vector2f _size;
	sf::RectangleShape _rect;

	size_t _window_y_size{ 1080u };
	size_t _window_x_size{ 1920u };
};