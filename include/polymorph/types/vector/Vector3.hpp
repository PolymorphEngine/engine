/*
** ${PROJECT}, 2022
** Vector.hpp by 0xMemoryGrinder
** File description:
** Vector.hpp
*/


#pragma once

#include "polymorph/api/scripting/ASerializableObject.hpp"

namespace polymorph::engine
{
    class Vector2;

    /**
     * @class Vector3 A simple clas to store 3D coordinates, move or any relation between two floats
     */
    class Vector3 : public api::ASerializableObject
    {

////////////////////// CONSTRUCTORS/DESTRUCTORS /////////////////////////

        public:
            /**
             * @brief Construct a new Vector3 object with the given floats
             * @param x The x value
             * @param y The y value
             */
            Vector3(float x, float y);

            /**
             * @brief Construct a new Vector3 object with the given floats
             * @param x The x value
             * @param y The y value
             * @param z The z value
             */
            Vector3(float x, float y, float z);

            /**
             * @brief Construct a new Vector3 object with the given Vector2
             * @param copy The Vector2 to copy
             */
            Vector3(const Vector2& other);

            /**
             * @brief Construct a new Vector3 object with the given Vector3
             * @param other The Vector3 to copy
             */
            Vector3(const Vector3& other) = default;

            /**
             * @brief Construct a new Vector3 by moving the given Vector3 (std::move)
             * @param other The Vector3 to move
             */
            Vector3(Vector3&& other) noexcept = default;

            Vector3 &operator=(const Vector3 &other) = default;

            /**
             * @brief Construct a new Vector3 with 0 as default value for x, y and z
             */
            Vector3();

            /**
             * @brief Create a new Vector3 with the given xml node
             * @param component The component that will store the Vector3
             * @param node The xml node to parse to retrieve values from
             */
            Vector3(safe_ptr<AComponent> component, std::shared_ptr<myxmlpp::Node> node);

            /**
             * @brief Create a new Vector3 with the given xml node
             * @param config The config that will store the Vector3
             * @param node The xml node to parse to retrieve values from
             */
            Vector3(safe_ptr<api::APluginConfig> config, std::shared_ptr<myxmlpp::Node> node);


            /**
             * @brief Destroy the Vector3 object
             */
            ~Vector3() override = default;


//////////////////////--------------------------/////////////////////////



///////////////////////////// PROPERTIES ////////////////////////////////
        public:
            /**
             * @property Mandatory property to check if the object is a builtin type
             */
            static inline bool builtin_type = true;

            /**
             * @property The x value
             */
            float x;

            /**
             * @property The y value
             */
            float y;

            /**
             * @property The z value
             */
            float z;

            /**
             * @property A simple vector with default values (0, 0) to use anywhere for computations
             */
            static Vector3 zero;


//////////////////////--------------------------/////////////////////////



/////////////////////////////// METHODS /////////////////////////////////
        public:
            /**
             * @brief Add the given Vector3 to this Vector3
             * @param other The Vector3 to add
             * @return A new Vector3 with the result of the addition
             */
            Vector3 operator+(const Vector3 &other) const;

            /**
             * @brief Add the given Vector3 to this Vector3
             * @param other The Vector3 to add
             * @return A reference to this Vector3
             */
            Vector3 &operator+=(const Vector3 &other);

            /**
             * @brief Subtract the given Vector3 to this Vector3
             * @param other The Vector3 to subtract
             * @return A new Vector3 with the result of the subtraction
             */
            Vector3 operator-(const Vector3 &other) const;

            /**
             * @brief Subtract the given Vector3 to this Vector3
             * @param other The Vector3 to subtract
             * @return A reference to this Vector3
             */
            Vector3 &operator-=(const Vector3 &other);

            /**
             * @brief Divide this Vector3 by the given Vector3
             * @param other The Vector3 to divide by
             * @return A new Vector3 with the result of the division
             */
            Vector3 operator/(const Vector3 &other) const;

            /**
             * @brief Divide this Vector3 by the given Vector3
             * @param other The Vector3 to divide by
             * @return A reference to this Vector3
             */
            Vector3 &operator/=(const Vector3 &other);

            /**
             * @brief Multiply this Vector3 by the given Vector3
             * @param other The Vector3 to multiply by
             * @return A new Vector3 with the result of the multiplication
             */
            Vector3 operator*(const Vector3 &other) const;

            /**
             * @brief Multiply this Vector3 by the given Vector3
             * @param other The Vector3 to multiply by
             * @return A reference to this Vector3
             */
            Vector3 &operator*=(const Vector3 &other);

            /**
             * @brief Compare this Vector3 with the given Vector3
             * @param other The Vector3 to compare with
             * @return true if the two Vector3 are equal, false otherwise
             */
            bool operator==(const Vector3 &other) const;

            /**
             * @brief Compare this Vector3 with the given Vector3
             * @param other The Vector3 to compare with
             * @return true if the two Vector3 are not equal, false otherwise
             */
            bool operator!=(const Vector3 &other) const;

            /**
             * @brief Add this vector to the given vector2 by using its x and y values
             * @param other The Vector2 to add
             * @return A new Vector3 with the result of the addition
             */
            Vector3 operator+(const Vector2 &other) const;

            /**
             * @brief Add this vector to the given vector2 by using its x and y values
             * @param other The Vector2 to add
             * @return A reference to this Vector3
             */
            Vector3 &operator+=(const Vector2 &other);

            /**
             * @brief Subtract this vector to the given vector2 by using its x and y values
             * @param other The Vector2 to subtract
             * @return A new Vector3 with the result of the subtraction
             */
            Vector3 operator-(const Vector2 &other) const;

            /**
             * @brief Subtract this vector to the given vector2 by using its x and y values
             * @param other The Vector2 to subtract
             * @return A reference to this Vector3
             */
            Vector3 &operator-=(const Vector2 &other);

            /**
             * @brief Divide this Vector3 by the given Vector2 by using its x and y values
             * @param other The Vector3 to divide by
             * @return A new Vector3 with the result of the division
             */
            Vector3 operator/(const Vector2 &other) const;

            /**
             * @brief Divide this Vector3 by the given Vector2 by using its x and y values
             * @param other The Vector3 to divide by
             * @return A reference to this Vector3
             */
            Vector3 &operator/=(const Vector2 &other);

            /**
             * @brief Multiply this Vector3 by the given Vector2 by using its x and y values
             * @param other The Vector3 to multiply by
             * @return A new Vector3 with the result of the multiplication
             */
            Vector3 operator*(const Vector2 &other) const;

            /**
             * @brief Multiply this Vector3 by the given Vector2 by using its x and y values
             * @param other The Vector2 to multiply by
             * @return A reference to this Vector3
             */
            Vector3 &operator*=(const Vector2 &other);

            /**
             * @brief Assign the given Vector2 x and y values to this Vector3
             * @param other The Vector2 to assign
             * @return A reference to this Vector3
             */
            Vector3 &operator=(const Vector2 &other);

            /**
             * @brief Compare this Vector3 with the given Vector2 by using its x and y values
             * @param other The Vector2 to compare with
             * @return true if the two Vectors are equal, false otherwise
             */
            bool operator==(const Vector2 &other) const;

            /**
             * @brief Compare this Vector3 with the given Vector2 by using its x and y values
             * @param other The Vector2 to compare with
             * @return true if the two Vectors are not equal, false otherwise
             */
            bool operator!=(const Vector2 &other) const;

            /**
             * @brief Add the float to the x and y values to this Vector3
             * @param value The float to add
             * @return A new Vector3 with the result of the addition
             */
            Vector3 operator+(float value) const;

            /**
             * @brief Add the float to the x and y values of this Vector3
             * @param value The float to add
             * @return A reference to this Vector3
             */
            Vector3 &operator+=(float value);

            /**
             * @brief Subtract the float to the x and y values to this Vector3
             * @param value The float to subtract
             * @return A new Vector3 with the result of the subtraction
             */
            Vector3 operator-(float value) const;

            /**
             * @brief Subtract the float to the x and y values of this Vector3
             * @param value The float to subtract
             * @return A reference to this Vector3
             */
            Vector3 &operator-=(float value);

            /**
             * @brief Divide the x and y values of this Vector3 by the given float
             * @param value The float to divide by
             * @return A new Vector3 with the result of the division
             */
            Vector3 operator/(float value) const;

            /**
             * @brief Divide the x and y values of this Vector3 by the given float
             * @param value The float to divide by
             * @return A reference to this Vector3
             */
            Vector3 &operator/=(float value);

            /**
             * @brief Multiply the x and y values of this Vector3 by the given float
             * @param value The float to multiply by
             * @return A new Vector3 with the result of the multiplication
             */
            Vector3 operator*(float value) const;

            /**
             * @brief Multiply the x and y values of this Vector3 by the given float
             * @param value The float to multiply by
             * @return A reference to this Vector3
             */
            Vector3 &operator*=(float value);

            /**
             * @brief Compute the subtraction of this Vector3 from the given Vector3
             * @param other The Vector3 to subtract from
             * @return A new Vector3 with the result of the subtraction
             */
            Vector3 delta(const Vector3 &other) const;

            /**
             * @brief Compute the distance between this Vector3 and the given Vector3 considering them as points
             * @param other The Vector3 (other point) to compute the distance to
             * @return The distance between the two Vector3 (points)
             */
            float distance(const Vector3 &b) const;

            /**
             * @brief Compute the subtraction of this Vector3 from the given Vector2 using its x and y values
             * @param other The Vector2 to subtract from
             * @return A new Vector3 with the result of the subtraction
             */
            Vector3 delta(const Vector2 &other) const;

            /**
             * @brief Compute the distance between this Vector3 and the given Vector2 considering them as points
             * @param other The Vector2 (other point with x and y) to compute the distance to
             * @return The distance between the two Vectors (points)
             */
            float distance(const Vector2 &b) const;

            /**
             * @brief same thing as distance but with a destructured vector
             * @param x The x value of the virtual other Vector3
             * @param y The y value of the virtual other Vector3
             *
             * @return The distance between the two Vectors
             */
            Vector3 delta(float x, float y, float z) const;

            /**
             * @brief same thing as distance but with a destructured vector
             * @param x The x value of the virtual other Vector3
             * @param y The y value of the virtual other Vector3
             * @return The distance between the two Vectors (points)
             */
            float distance(float x, float y);

            /**
             * @brief same thing as distance but with a destructured Vector3
             * @param x The x value of the virtual other Vector3
             * @param y The y value of the virtual other Vector3
             * @param z The z value of the virtual other Vector3
             * @return The distance between the two Vectors (points)
             */
            float distance(float x, float y, float z);

            /**
             * @brief negate each value of this Vector3
             * @return A new Vector3 with the negated values
             */
            Vector3 reverse() const;

            /**
             * @brief negate each value of this Vector3
             * @return A reference to this Vector3
             */
            Vector3 &reverse();

            /**
             * @brief Compute the lerp of each member of this Vector3 with the given Vector3 and the given factor
             * @param destination The Vector3 to lerp with
             * @param factor The factor to lerp with
             * @return A new Vector3 with the result of the lerp
             */
            Vector3 lerp(const Vector3 &destination, float factor) const;

            /**
             * @brief Compute the lerp of each member of this Vector2 with the given Vector3 and the given factor
             * @param destination The Vector2 to lerp with
             * @param factor The factor to lerp with
             * @return A reference to this Vector3
             */
            Vector3 lerp(const Vector2 &destination, float factor) const;

            void build() override;

            void saveAll() override;


//////////////////////--------------------------/////////////////////////

    };
}
