/*
** EPITECH PROJECT, 2020
** Rect.hpp
** File description:
** header for Rect.c
*/

#pragma once

#include "polymorph/types/vector/Vector2.hpp"

namespace polymorph::engine
{
    class Circle;

    class Rect : public api::ASerializableObject
    {

////////////////////// CONSTRUCTORS/DESTRUCTORS /////////////////////////

    public:
        /**
         * @brief Construct a new Rect object with the given position and size
         * @param x The x position of the rect
         * @param y The y position of the rect
         * @param width The width of the rect
         * @param height The height of the rect
         */
        Rect(float x, float y, float w, float h)
                : x(x), y(y), width(w), height(h)
        {};

        /**
         * @brief Construct a new Rect object with 0,0 as position and 0 as size
         */
        Rect()
                : x(0), y(0), width(0), height(0)
        {};

        /**
         * @brief Construct a new Rect object with the given position and size
         * @param position The position of the rect
         * @param w The width of the rect
         * @param h The height of the rect
         */
        Rect(Vector2 &position, float w, float h)
                : x(position.x), y(position.y), width(w), height(h)
        {};

        /**
         * @brief Construct a new Rect object with the given position and size
         * @param position The position of the rect
         * @param size The size of the rect
         */
        Rect(Vector2 &position, Vector2 &size)
                : x(position.x), y(position.y), width(size.x),
                  height(size.y)
        {};

        /**
         * @brief Construct a new Rect object with the given position and size
         * @param x The x position of the rect
         * @param y The y position of the rect
         * @param size The size of the rect
         */
        Rect(float x, float y, Vector2 &size)
                : x(x), y(y), width(size.x), height(size.y)
        {};

        ~Rect() override = default;

        /**
         * @brief Create a new Rect with the given xml node
         * @param component The component that will store the Rect
         * @param node The xml node to parse to retrieve values from
         */
        Rect(const Rect &copy) = default;

        /**
         * @brief Create a new Rect with the given xml node
         * @param component The component that will store the Rect
         * @param node The xml node to parse to retrieve values from
         */
        Rect(safe_ptr<AComponent> component, std::shared_ptr<myxmlpp::Node> node);

        /**
         * @brief Create a new Rect with the given xml node
         * @param config The config that will store the Rect
         * @param node The xml node to parse to retrieve values from
         */
        Rect(safe_ptr<api::APluginConfig> config, std::shared_ptr<myxmlpp::Node> node);


//////////////////////--------------------------/////////////////////////



///////////////////////////// PROPERTIES ////////////////////////////////
    public:
        /**
         * @property Mandatory property to check if the object is a builtin type
         */
        static inline bool builtin_type = true;

        /**
         * @property x The x position of the rect
         */
        float x;

        /**
         * @property y The y position of the rect
         */
        float y;

        /**
         * @property width The width of the rect
         */
        float width;

        /**
         * @property height The height of the rect
         */
        float height;

        /**
         * @property A simple Rect with 0,0 as position and 0 as size for computations
         */
        static Rect zero;


    private:


//////////////////////--------------------------/////////////////////////



/////////////////////////////// METHODS /////////////////////////////////
    public:
        /**
         * @brief Check if the rect intersects with another rect
         * @param rect1 The rect to check intersection with
         * @param rect2 The rect to check intersection with
         * @return true if the rect intersects with the given rect, false otherwise
         */
        static bool intersect(const Rect &rect1, const Rect &rect2);

        /**
         * @brief Check if a rect at the given position and size intersects with another rect
         * @param position The position of the rect to check intersection with
         * @param size The size of the rect to check intersection with
         * @param rect The rect to check intersection with
         * @return true if the rect intersects with the given rect, false otherwise
         */
        static bool intersect(const Vector2 &position, const Vector2 &size,
                              const Rect &rect);

        /**
         * @brief Check if a rect at the given position and size intersects with another rect
         * @param rect The rect to check intersection with
         * @param position The position of the rect to check intersection with
         * @param size The size of the rect to check intersection with
         * @return true if the rect intersects with the given rect, false otherwise
         */
        static bool intersect(const Rect &rect, const Vector2 &position,
                              const Vector2 &size);

        /**
         * @brief Check if a rect at the given position and size intersects with another rect
         * at the given position and size
         * @param position1 The position of the rect to check intersection with
         * @param size1 The size of the rect to check intersection with
         * @param position2 The position of the rect to check intersection with
         * @param size2 The size of the rect to check intersection with
         * @return true if the rect intersects with the given rect, false otherwise
         */
        static bool
        intersect(const Vector2 &position1, const Vector2 &size1,
                  const Vector2 &position2, const Vector2 &size2);

        /**
         * @brief Check if the rect intersects with a given circle
         * @param rect The rect to check intersection with
         * @param circle The circle to check intersection with
         * @return true if the rect intersects with the given circle, false otherwise
         */
        static bool intersect(const Rect &rect, const Circle &circle);

        static bool intersect(const Vector2 &position, const Vector2 &size,
                              const Circle &circle);

        static bool intersect(const Vector2 &position, const Vector2 &size,
                              const Vector2 &center, float radius);

        static bool
        intersect(const Rect &rect, const Vector2 &center, float radius);

        static bool intersect(const Circle &circle, const Rect &rect);

        static bool intersect(const Circle &circle, const Vector2 &position,
                              const Vector2 &size);

        static bool intersect(const Vector2 &center, float radius,
                              const Vector2 &position, const Vector2 &size);

        static bool
        intersect(const Vector2 &center, float radius, const Rect &rect);

        bool contains(Vector2 &point) const;

        void build() override;

        void saveAll() override;


    private:


//////////////////////--------------------------/////////////////////////

    };

}