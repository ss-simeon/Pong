#pragma once

#include <SFML/Graphics/RectangleShape.hpp>

class PongGraphics
{
public:
	PongGraphics(const float& window_x, const float& window_y);

    inline const std::vector<sf::RectangleShape> get_dividing_lane() const { return m_dividing_lane; };

private:
    float m_window_x;
    float m_window_y;
    std::vector<sf::RectangleShape> m_dividing_lane;

    void set_up_dividing_lane();
};

PongGraphics::PongGraphics(const float& window_x, const float& window_y)
    : m_window_x{ window_x }, m_window_y{ window_y }, m_dividing_lane(28u)
{
    set_up_dividing_lane();
}

void PongGraphics::set_up_dividing_lane()
{
    sf::Vector2f r_size = sf::Vector2f(20.f, 20.f);

    float total_length = m_dividing_lane.size() * r_size.y;
    float ideal_spacing = (m_window_y - total_length) / (m_dividing_lane.size() + 1);
    float centered_x_pos = 0.5f * (m_window_x - r_size.x);

    for (size_t i = 0; i < m_dividing_lane.size(); ++i)
    {
        m_dividing_lane[i].setSize(r_size);
        float y_pos = (i == 0) ? ideal_spacing : m_dividing_lane[i - 1].getPosition().y + ideal_spacing + r_size.y;
        m_dividing_lane[i].setPosition(centered_x_pos, y_pos);
    }
}