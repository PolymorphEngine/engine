/*
** EPITECH PROJECT, 2020
** Circle.hpp
** File description:
** header for Circle.c
*/

#include "polymorph/types/vector/Vector2.hpp"

#pragma once

namespace polymorph::engine
{

    class Rect;

    class Circle : public api::ASerializableObject {

////////////////////// CONSTRUCTORS/DESTRUCTORS /////////////////////////

    public:
        /**
         * @brief Construct a new Circle object with the given center and radius
         * @param center The center of the circle
         * @param radius The radius of the circle
         */
        Circle(const Vector2 &center, float radius);


        /**
         * @brief Construct a new Circle object from another circle
         */
        Circle(const Circle &circle);

        /**
         * @brief Construct a new Circle object with the given center and radius
         * @param x The x coordinate of the center of the circle
         * @param y The y coordinate of the center of the circle
         * @param radius The radius of the circle
         */
        Circle(float x, float y, float radius);

        /**
         * @brief Construct a new Circle object with 0,0 as center and 0 as radius
         */
        Circle();

        /**
         * @brief Create a new Circle with the given xml node
         * @param component The component that will store the Circle
         * @param node The xml node to parse to retrieve values from
         */
        Circle(safe_ptr<AComponent> component, std::shared_ptr<myxmlpp::Node> node);

        /**
         * @brief Create a new Rect with the given xml node
         * @param config The config that will store the Rect
         * @param node The xml node to parse to retrieve values from
         */
        Circle(safe_ptr<api::APluginConfig> config, std::shared_ptr<myxmlpp::Node> node);

        ~Circle() override = default;


//////////////////////--------------------------/////////////////////////



///////////////////////////// PROPERTIES ////////////////////////////////
    public:
        /**
         * @property Mandatory property to check if the object is a builtin type
         */
        static inline bool builtin_type = true;

        /**
         * @property Center of the circle
         */
        Vector2 center;

        /**
         * @property Radius of the circle
         */
        float radius;


    private:


//////////////////////--------------------------/////////////////////////



/////////////////////////////// METHODS /////////////////////////////////
    public:

        /**
         * @brief Check if the given circles intersect
         * @param circle1 The first circle to check
         * @param circle2 The second circle to check
         * @return true if the circles intersect, false otherwise
         */
        static bool intersect(const Circle &circle1, const Circle &circle2);

        /**
         * @brief Check if the given circle and the given center/radius intersect
         * @param circle The circle to check
         * @param center The center of the circle to check
         * @param radius The radius of the circle to check
         * @return true if the circles intersect, false otherwise
         */
        static bool intersect(const Circle &circle, const Vector2 &center,
                              float radius);

        /**
         * @brief Check if the given vector and radius intersect the circle
         * @param center The center of the circle to check
         * @param radius The radius associated with the center
         * @param circle The vector to check
         * @return true if the circle and the vector intersect, false otherwise
         */
        static bool intersect(const Vector2 &center, float radius,
                              const Circle &circle);

        /**
         * @brief Check if two given vector and associated radius intersect
         * @param center1 The center of the first circle to check
         * @param radius1 The radius associated with the first center
         * @param center2 The center of the second circle to check
         * @param radius2 The radius associated with the second center
         * @return true if the circles intersect, false otherwise
         */
        static bool intersect(const Vector2 &center1, float radius1,
                              const Vector2 &center2, float radius2);

        /**
         * @brief Check if the given circle and the given rect intersect
         * @param rect The rect to check
         * @param circle The circle to check
         * @return true if the circle and the rect intersect, false otherwise
         */
        static bool intersect(const Rect &rect, const Circle &circle);

        /**
         * @brief Check if the given position and size intersect the circle
         * @param position The position of the object to check
         * @param size The size of the object to check
         * @param circle The circle to check
         * @return true if the circle and the rect intersect, false otherwise
         */
        static bool intersect(const Vector2 &position, const Vector2 &size,
                              const Circle &circle);

        /**
         * @brief Check if the given position and size intersect the circle and it's radius
         * @param position The position of the object to check
         * @param size The size of the object to check
         * @param center The center of the circle to check
         * @param radius The radius of the circle to check
         * @return true if the circle and the rect intersect, false otherwise
         */
        static bool intersect(const Vector2 &position, const Vector2 &size,
                              const Vector2 &center, float radius);

        /**
         * @brief Check if the given rect and the given circle intersect
         * @param rect The rect to check
         * @param center The center of the circle to check
         * @param radius The radius of the circle to check
         * @return true if the circle and the rect intersect, false otherwise
         */
        static bool
        intersect(const Rect &rect, const Vector2 &center, float radius);

        /**
         * @brief Check if the given circle and the given rect intersect
         * @param circle The circle to check
         * @param rect The rect to check
         * @return true if the circle and the rect intersect, false otherwise
         */
        static bool intersect(const Circle &circle, const Rect &rect);

        /**
         * @brief Check if the given circle and the given rect intersect
         * @param circle The circle to check
         * @param position The equivalent of x and y properties of rect
         * @param size The equivalent of width and height properties of rect
         * @return true if the circle and the rect intersect, false otherwise
         */
        static bool intersect(const Circle &circle, const Vector2 &position,
                              const Vector2 &size);

        /**
         * @brief Check if the given circle and the given rect intersect
         * @param center The center of the circle to check
         * @param radius The radius of the circle to check
         * @param position The equivalent of x and y properties of rect
         * @param size The equivalent of width and height properties of rect
         * @return true if the circle and the rect intersect, false otherwise
         */
        static bool intersect(const Vector2 &center, float radius,
                              const Vector2 &position, const Vector2 &size);

        /**
         * @brief Check if the given circle and the given rect intersect
         * @param center The center of the circle to check
         * @param radius The radius of the circle to check
         * @param rect The rect to check
         * @return true if the circle and the rect intersect, false otherwise
         */
        static bool intersect(const Vector2 &center, float radius, const Rect &rect);

        void build() override;

        void saveAll() override;


    private:


//////////////////////--------------------------/////////////////////////

    };
} // polymorph::engine
