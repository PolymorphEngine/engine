/*
** EPITECH PROJECT, 2022
** Vector3.cpp
** File description:
** Vector3.cpp
*/

#include "Vector3.hpp"
#include "Vector2.hpp"

polymorph::engine::Vector3::Vector3(float x, float y) : x(x), y(y), z(0)
{}

polymorph::engine::Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z)
{}

polymorph::engine::Vector3::Vector3(const polymorph::engine::Vector2 &other) : x(other.x), y(other.y), z(0)
{}

polymorph::engine::Vector3::Vector3() : x(0), y(0), z(0)
{}

polymorph::engine::Vector3::Vector3(polymorph::engine::safe_ptr<polymorph::engine::AComponent> component,
                                    std::shared_ptr<myxmlpp::Node> node) : ASerializableObject(component, node)
{
    build();
}

polymorph::engine::Vector3::Vector3(polymorph::engine::safe_ptr<polymorph::engine::api::APluginConfig> config,
                                    std::shared_ptr<myxmlpp::Node> node) : ASerializableObject(config, node)
{
    build();
}

polymorph::engine::Vector3 polymorph::engine::Vector3::operator+(const polymorph::engine::Vector3 &other) const
{
    return {x + other.x, y + other.y, z + other.z};
}

polymorph::engine::Vector3 &polymorph::engine::Vector3::operator+=(const polymorph::engine::Vector3 &other)
{
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

polymorph::engine::Vector3 polymorph::engine::Vector3::operator-(const polymorph::engine::Vector3 &other) const
{
    return {x - other.x, y - other.y, z - other.z};
}

polymorph::engine::Vector3 &polymorph::engine::Vector3::operator-=(const polymorph::engine::Vector3 &other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

polymorph::engine::Vector3 polymorph::engine::Vector3::operator/(const polymorph::engine::Vector3 &other) const
{
    return {x / other.x, y / other.y, z / other.z};
}

polymorph::engine::Vector3 &polymorph::engine::Vector3::operator/=(const polymorph::engine::Vector3 &other)
{
    x /= other.x;
    y /= other.y;
    z /= other.z;
    return *this;
}

polymorph::engine::Vector3 polymorph::engine::Vector3::operator*(const polymorph::engine::Vector3 &other) const
{
    return {x * other.x, y * other.y, z * other.z};
}

polymorph::engine::Vector3 &polymorph::engine::Vector3::operator*=(const polymorph::engine::Vector3 &other)
{
    x *= other.x;
    y *= other.y;
    z *= other.z;
    return *this;
}

bool polymorph::engine::Vector3::operator==(const polymorph::engine::Vector3 &other) const
{
    return x == other.x && y == other.y && z == other.z;
}

bool polymorph::engine::Vector3::operator!=(const polymorph::engine::Vector3 &other) const
{
    return x != other.x || y != other.y || z != other.z;
}

polymorph::engine::Vector3 polymorph::engine::Vector3::operator+(const polymorph::engine::Vector2 &other) const
{
    return {x + other.x, y + other.y, z};
}

polymorph::engine::Vector3 &polymorph::engine::Vector3::operator+=(const polymorph::engine::Vector2 &other)
{
    x += other.x;
    y += other.y;
    return *this;
}

polymorph::engine::Vector3 polymorph::engine::Vector3::operator-(const polymorph::engine::Vector2 &other) const
{
    return {x - other.x, y - other.y, z};
}

polymorph::engine::Vector3 &polymorph::engine::Vector3::operator-=(const polymorph::engine::Vector2 &other)
{
    x -= other.x;
    y -= other.y;
    return *this;
}

polymorph::engine::Vector3 polymorph::engine::Vector3::operator/(const polymorph::engine::Vector2 &other) const
{
    return {x / other.x, y / other.y, z};
}

polymorph::engine::Vector3 &polymorph::engine::Vector3::operator/=(const polymorph::engine::Vector2 &other)
{
    x /= other.x;
    y /= other.y;
    return *this;
}

polymorph::engine::Vector3 polymorph::engine::Vector3::operator*(const polymorph::engine::Vector2 &other) const
{
    return {x * other.x, y * other.y, z};
}

polymorph::engine::Vector3 &polymorph::engine::Vector3::operator*=(const polymorph::engine::Vector2 &other)
{
    x *= other.x;
    y *= other.y;
    return *this;
}

polymorph::engine::Vector3 &polymorph::engine::Vector3::operator=(const polymorph::engine::Vector2 &other)
{
    x = other.x;
    y = other.y;
    z = 0;
    return *this;
}

bool polymorph::engine::Vector3::operator==(const polymorph::engine::Vector2 &other) const
{
    return x == other.x && y == other.y;
}

bool polymorph::engine::Vector3::operator!=(const polymorph::engine::Vector2 &other) const
{
    return x != other.x || y != other.y;
}

polymorph::engine::Vector3 polymorph::engine::Vector3::operator+(float value) const
{
    return {x + value, y + value, z + value};
}

polymorph::engine::Vector3 &polymorph::engine::Vector3::operator+=(float value)
{
    x += value;
    y += value;
    z += value;
    return *this;
}

polymorph::engine::Vector3 polymorph::engine::Vector3::operator-(float value) const
{
    return {x - value, y - value, z - value};
}

polymorph::engine::Vector3 &polymorph::engine::Vector3::operator-=(float value)
{
    x -= value;
    y -= value;
    z -= value;
    return *this;
}

polymorph::engine::Vector3 polymorph::engine::Vector3::operator/(float value) const
{
    return {x / value, y / value, z / value};
}

polymorph::engine::Vector3 &polymorph::engine::Vector3::operator/=(float value)
{
    x /= value;
    y /= value;
    z /= value;
    return *this;
}

polymorph::engine::Vector3 polymorph::engine::Vector3::operator*(float value) const
{
    return {x * value, y * value, z * value};
}

polymorph::engine::Vector3 &polymorph::engine::Vector3::operator*=(float value)
{
    x *= value;
    y *= value;
    z *= value;
    return *this;
}

polymorph::engine::Vector3 polymorph::engine::Vector3::delta(const polymorph::engine::Vector3 &other) const
{
    return other - *this;
}

float polymorph::engine::Vector3::distance(const polymorph::engine::Vector3 &b) const
{
    return sqrt(pow(b.x - x, 2) + pow(b.y - y, 2) + pow(b.z - z, 2));
}

polymorph::engine::Vector3 polymorph::engine::Vector3::delta(const polymorph::engine::Vector2 &other) const
{
    return {other.x - x, other.y - y, z};
}

float polymorph::engine::Vector3::distance(const polymorph::engine::Vector2 &b) const
{
    return sqrt(pow(b.x - x, 2) + pow(b.y - y, 2));
}

polymorph::engine::Vector3 polymorph::engine::Vector3::delta(float x, float y, float z) const
{
    return {x - this->x, y - this->y, z - this->z};
}

float polymorph::engine::Vector3::distance(float x, float y)
{
    return sqrt(pow(x - this->x, 2) + pow(y - this->y, 2));
}

float polymorph::engine::Vector3::distance(float x, float y, float z)
{
    return sqrt(pow(x - this->x, 2) + pow(y - this->y, 2) + pow(z - this->z, 2));
}

polymorph::engine::Vector3 polymorph::engine::Vector3::reverse() const
{
    return {-x, -y, -z};
}

polymorph::engine::Vector3 &polymorph::engine::Vector3::reverse()
{
    x = -x;
    y = -y;
    z = -z;
    return *this;
}

polymorph::engine::Vector3
polymorph::engine::Vector3::lerp(const polymorph::engine::Vector3 &destination, float factor) const
{
    return *this + (destination - *this) * factor;
}

polymorph::engine::Vector3
polymorph::engine::Vector3::lerp(const polymorph::engine::Vector2 &destination, float factor) const
{
    return *this + (destination - *this) * factor;
}

void polymorph::engine::Vector3::build()
{
    _setProperty("x", x);
    _setProperty("y", y);
    _setProperty("z", z);
}

void polymorph::engine::Vector3::saveAll()
{
    _setProperty("x", x);
    _setProperty("y", y);
    _setProperty("z", z);
}
