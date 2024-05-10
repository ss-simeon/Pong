#include <SFML/Graphics.hpp>

#include <SFML/System/String.hpp>

#include "Config.h"

sf::String construct_window_title();

int main()
{
    sf::RenderWindow window = sf::RenderWindow{ { 1920u, 1080u }, construct_window_title()};
    window.setVerticalSyncEnabled(true);

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