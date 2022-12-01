/*
** EPITECH PROJECT, 2022
** Color.cpp
** File description:
** Color.cpp
*/

#include "polymorph/types/Color.hpp"

polymorph::engine::Color::Color()
{
    this->r = 0;
    this->g = 0;
    this->b = 0;
    this->a = 0;
}

polymorph::engine::Color::Color(unsigned int r, unsigned int g, unsigned int b, unsigned int a)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

polymorph::engine::Color::Color(
        polymorph::engine::safe_ptr<polymorph::engine::AComponent> component,
        std::shared_ptr<myxmlpp::Node> node) : ASerializableObject(component, node)
{
    build();
}

polymorph::engine::Color::Color(
        polymorph::engine::safe_ptr<polymorph::engine::api::APluginConfig> config,
        std::shared_ptr<myxmlpp::Node> node) : ASerializableObject(config, node)
{
    build();
}

void
polymorph::engine::Color::setColor(unsigned int r, unsigned int g, unsigned int b, unsigned int a)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

void polymorph::engine::Color::build()
{
    _setProperty("r", r);
    _setProperty("g", g);
    _setProperty("b", b);
    _setProperty("a", a);
}

void polymorph::engine::Color::saveAll()
{
    saveProperty("r", r);
    saveProperty("g", g);
    saveProperty("b", b);
    saveProperty("a", a);
}

bool polymorph::engine::Color::operator==(const polymorph::engine::Color &other) const {
    return r == other.r && g == other.g && b == other.b && a == other.a;
}

bool polymorph::engine::Color::operator!=(const polymorph::engine::Color &other) const {
    return !(*this == other);
}

polymorph::engine::Color
polymorph::engine::Color::operator+(const polymorph::engine::Color &other) const {
    return Color(r + other.r, g + other.g, b + other.b, a + other.a);
}

polymorph::engine::Color
polymorph::engine::Color::operator-(const polymorph::engine::Color &other) const {
    return Color(r - other.r, g - other.g, b - other.b, a - other.a);
}
