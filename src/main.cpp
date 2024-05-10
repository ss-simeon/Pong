#include <SFML/Graphics.hpp>

#include <string>
#include <sstream>

#include "Config.h"

int main()
{
    std::ostringstream oss;
    oss << "CMakeSFMLProject: " << CMakeSFMLProject_VERSION_MAJOR << " " << CMakeSFMLProject_VERSION_MINOR;
    std::string var = oss.str();

    sf::RenderWindow window = sf::RenderWindow{ { 1920u, 1080u }, var };
    window.setFramerateLimit(144);

    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear();
        window.display();
    }
}