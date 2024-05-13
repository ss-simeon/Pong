#pragma once

#include <SFML/Graphics/RectangleShape.hpp>

class Ball
{
public:
	Ball();

	void move();
	void notify_of_player_positions(const sf::RectangleShape& player, const sf::RectangleShape& enemy);
	void check_round_win();

	inline sf::RectangleShape get_rect() const { return _rect; }

private:
	float determine_hit_back_angle(float paddle_y_pos, float paddle_length);	
	void check_collision_with_player(float player_pos_x, float player_pos_y, float player_size_x, float player_size_y);
	void check_collision_with_enemy(float enemy_pos_x, float enemy_pos_y, float enemy_size_x, float enemy_size_y);
	void check_collision_with_window();

	sf::RectangleShape _player_rect;
	sf::RectangleShape _enemy_rect;

	sf::Vector2f _velocity;
	float _width;
	float _length;

	sf::Vector2f _size;
	sf::RectangleShape _rect;

	size_t _window_y_size{ 1080u };
	size_t _window_x_size{ 1920u };
};