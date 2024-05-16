#pragma once

#include <filesystem>
#include <string>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

class PongGraphics
{
public:
	PongGraphics(const float& window_x, const float& window_y);

    inline const std::vector<sf::RectangleShape> get_dividing_lane() const { return m_dividing_lane; };
    void handle_show_hide_fps_counter();

    void set_text_string(const std::string& fps);
    inline void set_font(const sf::Font& font) { m_fps_font = font; }

    inline bool get_fps_show() const { return m_fps_show; }
    inline sf::Text get_text() const { return m_fps_text; }

private:
    // Dividing Lane
    float m_window_x;
    float m_window_y;
    std::vector<sf::RectangleShape> m_dividing_lane;

    void set_up_dividing_lane();

    // FPS Counter Graphic
    sf::Text m_fps_text;
    sf::Font m_fps_font;
    bool m_fps_show;

    void set_up_fps_text();
};

PongGraphics::PongGraphics(const float& window_x, const float& window_y)
    : m_window_x{ window_x }, m_window_y{ window_y }, m_dividing_lane(28u), m_fps_text(), m_fps_font(), m_fps_show{ false }
{
    set_up_dividing_lane();
    set_up_fps_text();
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

void PongGraphics::set_up_fps_text()
{
    m_fps_text.setFont(m_fps_font);
    m_fps_text.setCharacterSize(24u);
    m_fps_text.setFillColor(sf::Color::Red);
    m_fps_text.setPosition(sf::Vector2f(50.f, 50.f));
}

void PongGraphics::set_text_string(const std::string& fps)
{
    m_fps_text.setString(fps);
}

void PongGraphics::handle_show_hide_fps_counter()
{
    m_fps_show = !m_fps_show;
}