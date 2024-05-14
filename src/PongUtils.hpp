#pragma once

#include <queue>
#include <optional>

#include <SFML/System/Clock.hpp>

#include "Config.h"

class PongUtils
{
public:
    PongUtils() : m_clock(), m_fps_queue() {}

    sf::String construct_window_title();
    std::optional<size_t> update_fps();
private:
    // FPS Counter
    sf::Clock m_clock;
    std::queue<size_t> m_fps_queue;
};

sf::String PongUtils::construct_window_title()
{
    sf::String window_bar_title = sf::String("Ping Pong: Version ");
    window_bar_title += std::to_string(PingPong_VERSION_MAJOR);
    window_bar_title += ".";
    window_bar_title += std::to_string(PingPong_VERSION_MINOR);
    return window_bar_title;
}

std::optional<size_t> PongUtils::update_fps()
{
    size_t avg_fps = 0u;

    float current_time = m_clock.restart().asSeconds();
    float fps = 1u / (current_time);
    m_fps_queue.push(fps);

    if (m_fps_queue.size() == 20)
    {
        float total_fps = 0.f;
        for (; !m_fps_queue.empty(); m_fps_queue.pop())
        {
            total_fps += m_fps_queue.front();
        }

        avg_fps = total_fps / 20;
        return avg_fps;
    }

    return std::nullopt;
}