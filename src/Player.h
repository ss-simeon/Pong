#pragma once

#include <SFML/Graphics/RectangleShape.hpp>

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