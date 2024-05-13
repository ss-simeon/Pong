#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "Config.h"
#include "Ball.h"
#include "Player.h"

sf::String construct_window_title();
void set_up_dividing_lane(std::vector<sf::RectangleShape>& d_lane, const sf::RenderWindow& window);

int main()
{
    sf::RenderWindow window = sf::RenderWindow{ { 1920u, 1080u }, construct_window_title()};
    window.setVerticalSyncEnabled(true);

    Player player = Player(true, 50.f, 250.f);
    Player enemy = Player(false, 50.f, 250.f);
    Ball ball = Ball();
    
    std::vector<sf::RectangleShape> dividing_lane(28u);
    set_up_dividing_lane(dividing_lane, window);

    while (window.isOpen())
    {
        for (sf::Event event = sf::Event{}; window.pollEvent(event);)
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                
                default:
                    break;
            }
        }

        window.clear();

        window.draw(player.get_rect());
        window.draw(enemy.get_rect());
        window.draw(ball.get_rect());

        player.handle_move();

        ball.move();
        ball.notify_of_player_positions(player.get_rect(), enemy.get_rect()); 

        ball.check_round_win();

        for (auto& dividing_rect : dividing_lane)
        {
            window.draw(dividing_rect);
        }

        window.display();
    }
}

sf::String construct_window_title()
{
    sf::String window_bar_title = sf::String("Ping Pong: Version ");
    window_bar_title += std::to_string(PingPong_VERSION_MAJOR);
    window_bar_title += ".";
    window_bar_title += std::to_string(PingPong_VERSION_MINOR);
    return window_bar_title;
}

void set_up_dividing_lane(std::vector<sf::RectangleShape>& d_lane, const sf::RenderWindow& window)
{
    float r_length = 20.f;
    float r_width = 20.f;
    sf::Vector2f r_size = sf::Vector2f(r_width, r_length);

    float total_length = d_lane.size() * r_length;
    float ideal_spacing = (window.getSize().y - total_length) / (d_lane.size() + 1);
    float centered_x_pos = 0.5f * (window.getSize().x - r_width);

    for (size_t i = 0; i < d_lane.size(); ++i)
    {
        d_lane[i].setSize(r_size);
        float y_pos = (i == 0) ? ideal_spacing : d_lane[i-1].getPosition().y + ideal_spacing + r_length;
        d_lane[i].setPosition(centered_x_pos, y_pos);
    }
}