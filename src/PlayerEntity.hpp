#pragma once

#include <SFML/Graphics/RectangleShape.hpp>

class PlayerEntity
{
public:
    PlayerEntity(bool main_player, const float& width, const float& length);

	virtual void handle_move() = 0;

	inline sf::RectangleShape get_rect() const { return _rect; }

protected:
	bool _main_player;
	float _width;
	float _length;
	
	sf::Vector2f _size;
	sf::RectangleShape _rect;

	size_t _window_y_size{ 1080u };
	size_t _window_x_size{ 1920u };
};

PlayerEntity::PlayerEntity(bool main_player, const float& width, const float& length)
    : _main_player{ main_player }, _width{ width }, _length{ length }, _size(_width, _length), _rect(_size)
{
    float x_pos_from_side = 200.f;

    float centered_y_pos = 0.5f * (_window_y_size - _length);
    float x_pos = _main_player ? x_pos_from_side : _window_x_size - x_pos_from_side - _width;

    _rect.setPosition(sf::Vector2f(x_pos, centered_y_pos));
}