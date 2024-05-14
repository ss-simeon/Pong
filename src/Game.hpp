#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "PongGraphics.hpp"
#include "PongUtils.hpp"
#include "Player.hpp"
#include "Ball.hpp"

class Game
{
public:
    Game();

	void run();

private:
	void process_events();
	void update();
	void render();

	sf::RenderWindow m_window;

    PongUtils m_pong_utils;
    PongGraphics m_pong_graphics;
	Player m_player_one;
	Player m_player_two;
	Ball m_ball;
};

Game::Game()
	: m_pong_graphics(1920u, 1080u), m_pong_utils(), 
    m_window(sf::VideoMode(1920u, 1080u), m_pong_utils.construct_window_title()),
    m_player_one(true, 50.f, 250.f), m_player_two(false, 50.f, 250.f), m_ball()
{
	m_window.setVerticalSyncEnabled(true);
}

void Game::run()
{
    while (m_window.isOpen())
    {
        process_events();
        update();
        render();
    }
}

void Game::process_events()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            m_window.close();
        }
    }

    m_player_one.handle_move();
    m_ball.move();    
}

void Game::update()
{
    m_ball.notify_of_player_positions(m_player_one.get_rect(), m_player_two.get_rect());
    m_ball.check_round_win();
}

void Game::render()
{
    m_window.clear();

    m_window.draw(m_player_one.get_rect());
    m_window.draw(m_player_two.get_rect());
    m_window.draw(m_ball.get_rect());

    for (auto& dividing_rect : m_pong_graphics.get_dividing_lane())
    {
        m_window.draw(dividing_rect);
    }

    m_window.display();
}