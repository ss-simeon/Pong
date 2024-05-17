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

Ball::Ball()
	: _player_rect(), _enemy_rect(), _velocity(-3.f, 0.f), _width{ 20.f }, _length{ 20.f }, _size(_width, _length), _rect(_size)
{
	// ball should start in the player's arena hence the 50 offset
	float arena_offset = 50.f;
	float x_pos = 0.5f * (_window_x_size - _length) - arena_offset;
	float y_pos = 0.5f * (_window_y_size - _width);

	sf::Vector2f ball_position = sf::Vector2f(x_pos, y_pos);
	_rect.setPosition(ball_position);
}

void Ball::move()
{
	_rect.move(_velocity);

	float player_pos_x = _player_rect.getPosition().x;
	float player_pos_y = _player_rect.getPosition().y;
	float player_size_x = _player_rect.getSize().x;
	float player_size_y = _player_rect.getSize().y;

	float enemy_pos_x = _enemy_rect.getPosition().x;
	float enemy_pos_y = _enemy_rect.getPosition().y;
	float enemy_size_x = _enemy_rect.getSize().x;
	float enemy_size_y = _enemy_rect.getSize().y;

	check_collision_with_player(player_pos_x, player_pos_y, player_size_x, player_size_y);
	check_collision_with_enemy(enemy_pos_x, enemy_pos_y, enemy_size_x, enemy_size_y);
	check_collision_with_window();
}

void Ball::notify_of_player_positions(const sf::RectangleShape& player, const sf::RectangleShape& enemy)
{
	_player_rect = player;
	_enemy_rect = enemy;
}

void Ball::check_collision_with_player(float player_pos_x, float player_pos_y, float player_size_x, float player_size_y)
{
	float ball_pos_x = _rect.getPosition().x;
	float ball_pos_y = _rect.getPosition().y;

	if (ball_pos_x <= (player_pos_x + player_size_x)
		&& ball_pos_y + _length >= player_pos_y
		&& ball_pos_y <= player_pos_y + player_size_y)
	{
		_velocity.x = 6.f;
		_velocity.y = determine_hit_back_angle(player_pos_y, player_size_y);
	}
}

void Ball::check_collision_with_enemy(float enemy_pos_x, float enemy_pos_y, float enemy_size_x, float enemy_size_y)
{
	float ball_pos_x = _rect.getPosition().x;
	float ball_pos_y = _rect.getPosition().y;

	if ((ball_pos_x + _width) >= enemy_pos_x
		&& ball_pos_y + _length >= enemy_pos_y
		&& ball_pos_y <= enemy_pos_y + enemy_size_y)
	{
		_velocity.x = -6.f;
		_velocity.y = determine_hit_back_angle(enemy_pos_y, enemy_size_y);
	}
}

float Ball::determine_hit_back_angle(float paddle_y_pos, float paddle_length)
{
	float hit_back_vector_y = 0.f;
	float ball_pos_y = _rect.getPosition().y;

	float seg_length = paddle_length / 3;

	if (ball_pos_y <= (paddle_y_pos + seg_length))
	{
		hit_back_vector_y = -2.f;
	}

	if (ball_pos_y >= (paddle_y_pos + 2 * seg_length))
	{
		hit_back_vector_y = 2.f;
	}

	return hit_back_vector_y;
}

void Ball::check_collision_with_window()
{
	float ball_pos_y = _rect.getPosition().y;
	float ball_size_y = _rect.getSize().y;

	if (ball_pos_y <= 0 || (ball_pos_y + ball_size_y) >= _window_y_size)
	{
		_velocity.y *= -1;
	}
}

void Ball::check_round_win()
{
	float ball_pos_x = _rect.getPosition().x;
	float ball_size_x = _rect.getSize().x;

	if (ball_pos_x <= 0 || (ball_pos_x + ball_size_x) >= _window_x_size)
	{
		_velocity.y = 0.f;
		_velocity.x *= -1;

		float arena_offset = -50.f;

		if (ball_pos_x >= (_window_x_size / 2.f))
		{
			arena_offset = 50.f;
		}

		float x_pos = 0.5f * (_window_x_size - _length) - arena_offset;
		float y_pos = 0.5f * (_window_y_size - _width);

		_rect.setPosition(x_pos, y_pos);
	}
}