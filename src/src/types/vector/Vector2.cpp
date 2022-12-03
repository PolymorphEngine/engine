/*
** ${PROJECT}, 2022
** Vector.cpp by 0xMemoryGrinder
** File description:
** Vector.cpp
*/


#include "Vector2.hpp"
#include "Vector3.hpp"

polymorph::engine::Vector2::Vector2(float x, float y) : x(x), y(y)
{}

polymorph::engine::Vector2::Vector2() : x(0), y(0)
{}

polymorph::engine::Vector2::Vector2(const polymorph::engine::Vector3 &other) : x(other.x), y(other.y)
{}

polymorph::engine::Vector2::Vector2(polymorph::engine::safe_ptr<polymorph::engine::AComponent> component,
                                    std::shared_ptr<myxmlpp::Node> node) : ASerializableObject(component, node)
{
    build();
}

polymorph::engine::Vector2::Vector2(polymorph::engine::safe_ptr<polymorph::engine::api::APluginConfig> config,
                                    std::shared_ptr<myxmlpp::Node> node) : ASerializableObject(config, node)
{
    build();
}

polymorph::engine::Vector2 polymorph::engine::Vector2::operator+(const polymorph::engine::Vector2 &other) const
{
    return {x + other.x, y + other.y};
}

polymorph::engine::Vector2 &polymorph::engine::Vector2::operator+=(const polymorph::engine::Vector2 &other)
{
    x += other.x;
    y += other.y;
    return *this;
}

polymorph::engine::Vector2 polymorph::engine::Vector2::operator-(const polymorph::engine::Vector2 &other) const
{
    return {x - other.x, y - other.y};
}

polymorph::engine::Vector2 &polymorph::engine::Vector2::operator-=(const polymorph::engine::Vector2 &other)
{
    x -= other.x;
    y -= other.y;
    return *this;
}

polymorph::engine::Vector2 polymorph::engine::Vector2::operator/(const polymorph::engine::Vector2 &other) const
{
    return {x / other.x, y / other.y};
}

polymorph::engine::Vector2 &polymorph::engine::Vector2::operator/=(const polymorph::engine::Vector2 &other)
{
    x /= other.x;
    y /= other.y;
    return *this;
}

polymorph::engine::Vector2 polymorph::engine::Vector2::operator*(const polymorph::engine::Vector2 &other) const
{
    return {x * other.x, y * other.y};
}

polymorph::engine::Vector2 &polymorph::engine::Vector2::operator*=(const polymorph::engine::Vector2 &other)
{
    x *= other.x;
    y *= other.y;
    return *this;
}

bool polymorph::engine::Vector2::operator==(const polymorph::engine::Vector2 &other) const
{
    return x == other.x && y == other.y;
}

bool polymorph::engine::Vector2::operator!=(const polymorph::engine::Vector2 &other) const
{
    return x != other.x || y != other.y;
}

polymorph::engine::Vector2 polymorph::engine::Vector2::operator+(const polymorph::engine::Vector3 &other) const
{
    return {x + other.x, y + other.y};
}

polymorph::engine::Vector2 &polymorph::engine::Vector2::operator+=(const polymorph::engine::Vector3 &other)
{
    x += other.x;
    y += other.y;
    return *this;
}

polymorph::engine::Vector2 polymorph::engine::Vector2::operator-(const polymorph::engine::Vector3 &other) const
{
    return {x - other.x, y - other.y};
}

polymorph::engine::Vector2 &polymorph::engine::Vector2::operator-=(const polymorph::engine::Vector3 &other)
{
    x -= other.x;
    y -= other.y;
    return *this;
}

polymorph::engine::Vector2 polymorph::engine::Vector2::operator/(const polymorph::engine::Vector3 &other) const
{
    return {x / other.x, y / other.y};
}

polymorph::engine::Vector2 &polymorph::engine::Vector2::operator/=(const polymorph::engine::Vector3 &other)
{
    x /= other.x;
    y /= other.y;
    return *this;
}

polymorph::engine::Vector2 polymorph::engine::Vector2::operator*(const polymorph::engine::Vector3 &other) const
{
    return {x * other.x, y * other.y};
}

polymorph::engine::Vector2 &polymorph::engine::Vector2::operator*=(const polymorph::engine::Vector3 &other)
{
    x *= other.x;
    y *= other.y;
    return *this;
}

polymorph::engine::Vector2 &polymorph::engine::Vector2::operator=(const polymorph::engine::Vector3 &other)
{
    x = other.x;
    y = other.y;
    return *this;
}

bool polymorph::engine::Vector2::operator==(const polymorph::engine::Vector3 &other) const
{
    return x == other.x && y == other.y;
}

bool polymorph::engine::Vector2::operator!=(const polymorph::engine::Vector3 &other) const
{
    return x != other.x || y != other.y;
}

polymorph::engine::Vector2 polymorph::engine::Vector2::operator+(float value) const
{
    return {x + value, y + value};
}

polymorph::engine::Vector2 &polymorph::engine::Vector2::operator+=(float value)
{
    x += value;
    y += value;
    return *this;
}

polymorph::engine::Vector2 polymorph::engine::Vector2::operator-(float value) const
{
    return {x - value, y - value};
}

polymorph::engine::Vector2 &polymorph::engine::Vector2::operator-=(float value)
{
    x -= value;
    y -= value;
    return *this;
}

polymorph::engine::Vector2 polymorph::engine::Vector2::operator/(float value) const
{
    return {x / value, y / value};
}

polymorph::engine::Vector2 &polymorph::engine::Vector2::operator/=(float value)
{
    x /= value;
    y /= value;
    return *this;
}

polymorph::engine::Vector2 polymorph::engine::Vector2::operator*(float value) const
{
    return {x * value, y * value};
}

polymorph::engine::Vector2 &polymorph::engine::Vector2::operator*=(float value)
{
    x *= value;
    y *= value;
    return *this;
}

polymorph::engine::Vector2 polymorph::engine::Vector2::delta(const polymorph::engine::Vector2 &other) const
{
    return other - *this;
}

float polymorph::engine::Vector2::distance(const polymorph::engine::Vector2 &b) const
{
    return static_cast<float>(sqrt(pow(b.x - x, 2) + pow(b.y - y, 2)));
}

polymorph::engine::Vector2 polymorph::engine::Vector2::delta(const polymorph::engine::Vector3 &other) const
{
    return other - *this;
}

float polymorph::engine::Vector2::distance(const polymorph::engine::Vector3 &b) const
{
    return static_cast<float>(sqrt(pow(b.x - x, 2) + pow(b.y - y, 2)));
}

polymorph::engine::Vector2 polymorph::engine::Vector2::delta(float x, float y) const
{
    return {x - this->x, y - this->y};
}

float polymorph::engine::Vector2::distance(float x, float y)
{
    return static_cast<float>(sqrt(pow(x - this->x, 2) + pow(y - this->y, 2)));
}

float polymorph::engine::Vector2::distance(float x, float y, float z)
{
    return static_cast<float>(sqrt(pow(x - this->x, 2) + pow(y - this->y, 2)));
}

polymorph::engine::Vector2 polymorph::engine::Vector2::reverse() const
{
    return {-x, -y};
}

polymorph::engine::Vector2 &polymorph::engine::Vector2::reverse()
{
    x = -x;
    y = -y;
    return *this;
}

polymorph::engine::Vector2
polymorph::engine::Vector2::lerp(const polymorph::engine::Vector3 &destination, float factor) const
{
    return { std::lerp(x, destination.x, factor), std::lerp(y, destination.y, factor) };
}

polymorph::engine::Vector2
polymorph::engine::Vector2::lerp(const polymorph::engine::Vector2 &destination, float factor) const
{
    return { std::lerp(x, destination.x, factor), std::lerp(y, destination.y, factor) };
}

void polymorph::engine::Vector2::build()
{
    _setProperty("x", x);
    _setProperty("y", y);
}

void polymorph::engine::Vector2::saveAll()
{
    saveProperty("x", x);
    saveProperty("y", y);
}
