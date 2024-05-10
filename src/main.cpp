#include <SFML/Graphics.hpp>

#include <SFML/System/String.hpp>

#include "Config.h"

sf::String construct_window_title();
void set_up_rectangles(sf::RectangleShape& r_one, sf::RectangleShape& r_two, const sf::RenderWindow& window);
void set_up_dividing_lane(std::vector<sf::RectangleShape>& d_lane, const sf::RenderWindow& window);

int main()
{
    sf::RenderWindow window = sf::RenderWindow{ { 1920u, 1080u }, construct_window_title()};
    window.setVerticalSyncEnabled(true);

    sf::RectangleShape r_left;
    sf::RectangleShape r_right;
    std::vector<sf::RectangleShape> dividing_lane(28u);

    set_up_rectangles(r_left, r_right, window);
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

        window.draw(r_left);
        window.draw(r_right);

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

void set_up_rectangles(sf::RectangleShape& r_one, sf::RectangleShape& r_two, const sf::RenderWindow& window)
{
    float r_length = 250.f;
    float r_width = 50.f;
    sf::Vector2 r_size = sf::Vector2(r_width, r_length);

    float centered_y_pos = 0.5f * (window.getSize().y - r_length);
    float x_pos_one = 200;
    float x_pos_two = window.getSize().x - x_pos_one - r_width;

    r_one.setSize(r_size);
    r_two.setSize(r_size);

    r_one.setPosition(sf::Vector2f(x_pos_one, centered_y_pos));
    r_two.setPosition(sf::Vector2f(x_pos_two, centered_y_pos));
}

void set_up_dividing_lane(std::vector<sf::RectangleShape>& d_lane, const sf::RenderWindow& window)
{
    float r_length = 20.f;
    float r_width = 20.f;
    sf::Vector2 r_size = sf::Vector2(r_width, r_length);

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