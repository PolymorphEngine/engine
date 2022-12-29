/*
** EPITECH PROJECT, 2020
** Color.hpp
** File description:
** header for Color.c
*/


#pragma once

#include "polymorph/engine/api/scripting/ASerializableObject.hpp"

namespace polymorph::engine
{
    class Color : public api::ASerializableObject
{

        ////////////////////// CONSTRUCTORS/DESTRUCTORS /////////////////////////

    public:
        Color();
        ~Color() override = default;

        explicit Color(unsigned int r, unsigned int g, unsigned int b, unsigned int a = 255);
        Color(const Color &other) = default;

        /**
         * @brief Create a new Color with the given xml node
         * @param component The component that will store the Color
         * @param node The xml node to parse to retrieve values from
         */
        Color(safe_ptr<AComponent> component, std::shared_ptr<myxmlpp::Node> node);

        /**
         * @brief Create a new Color with the given xml node
         * @param config The config that will store the Color
         * @param node The xml node to parse to retrieve values from
         */
        Color(safe_ptr<api::APluginConfig> config, std::shared_ptr<myxmlpp::Node> node);

        //////////////////////--------------------------/////////////////////////



        ///////////////////////////// PROPERTIES ////////////////////////////////
    public:
        /**
         * @property Mandatory property to check if the object is a builtin type
         */
        static inline bool builtin_type = true;

        /**
         * @property r The red component of the color
         */
        unsigned char r;

        /**
         * @property g The green component of the color
         */
        unsigned char g;

        /**
         * @property b The blue component of the color
         */
        unsigned char b;

        /**
         * @property a The alpha component of the color
         */
        unsigned char a;


    private:


        //////////////////////--------------------------/////////////////////////



        /////////////////////////////// METHODS /////////////////////////////////
    public:
        /**
         * @brief Set the color to the given values
         * @param r The red value
         * @param g The green value
         * @param b The blue value
         * @param a The alpha value
         */
        void setColor(unsigned int r, unsigned int g, unsigned int b, unsigned int a = 255);

        void build() override;
        void saveAll() override;

        bool operator==(const Color &other) const;
        bool operator!=(const Color &other) const;
        Color operator+(const Color &other) const;
        Color operator-(const Color &other) const;


    private:


        //////////////////////--------------------------/////////////////////////

    };
}