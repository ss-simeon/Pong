#pragma once

#include "Config.h"

class PongUtils
{
public:
	PongUtils() {}

    sf::String construct_window_title();
private:
};

sf::String PongUtils::construct_window_title()
{
    sf::String window_bar_title = sf::String("Ping Pong: Version ");
    window_bar_title += std::to_string(PingPong_VERSION_MAJOR);
    window_bar_title += ".";
    window_bar_title += std::to_string(PingPong_VERSION_MINOR);
    return window_bar_title;
}