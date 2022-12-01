/*
** EPITECH PROJECT, 2020
** Color.hpp
** File description:
** header for Color.c
*/


#pragma once

#include "polymorph/api/scripting/ASerializableObject.hpp"

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
        Color(Color &&other) noexcept = default;

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
        static inline bool builtin_type = true;

        unsigned char r;
        unsigned char g;
        unsigned char b;
        unsigned char a;


    private:


        //////////////////////--------------------------/////////////////////////



        /////////////////////////////// METHODS /////////////////////////////////
    public:
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