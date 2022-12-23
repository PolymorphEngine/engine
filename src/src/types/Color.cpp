/*
** EPITECH PROJECT, 2022
** Color.cpp
** File description:
** Color.cpp
*/

#include "polymorph/engine/types/Color.hpp"

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
    int rInt;
    int gInt;
    int bInt;
    int aInt;
    _setProperty("r", rInt);
    _setProperty("g", gInt);
    _setProperty("b", bInt);
    _setProperty("a", aInt);
    r = static_cast<unsigned char>(rInt);
    g = static_cast<unsigned char>(gInt);
    b = static_cast<unsigned char>(bInt);
    a = static_cast<unsigned char>(aInt);
}

void polymorph::engine::Color::saveAll()
{
    int rInt = static_cast<int>(r);
    int gInt = static_cast<int>(g);
    int bInt = static_cast<int>(b);
    int aInt = static_cast<int>(a);

    saveProperty("r", rInt);
    saveProperty("g", gInt);
    saveProperty("b", bInt);
    saveProperty("a", aInt);
}

bool polymorph::engine::Color::operator==(const polymorph::engine::Color &other) const
{
    return r == other.r && g == other.g && b == other.b && a == other.a;
}

bool polymorph::engine::Color::operator!=(const polymorph::engine::Color &other) const
{
    return !(*this == other);
}

polymorph::engine::Color
polymorph::engine::Color::operator+(const polymorph::engine::Color &other) const
{
    return Color(r + other.r, g + other.g, b + other.b, a + other.a);
}

polymorph::engine::Color
polymorph::engine::Color::operator-(const polymorph::engine::Color &other) const
{
    return Color(r - other.r, g - other.g, b - other.b, a - other.a);
}
