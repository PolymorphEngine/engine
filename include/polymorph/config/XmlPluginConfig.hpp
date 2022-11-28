/*
** EPITECH PROJECT, 2020
** XmlPluginConfig.hpp
** File description:
** header for XmlPluginConfig.c
*/


#pragma once


#include "XmlPropertyManager.hpp"

namespace polymorph::engine::config
{
    class XmlPluginConfig : public XmlPropertyManager
    {

////////////////////// CONSTRUCTORS/DESTRUCTORS /////////////////////////
        public:
            XmlPluginConfig(std::shared_ptr<myxmlpp::Doc> &doc, debug::Logger& logger);

//////////////////////--------------------------/////////////////////////



///////////////////////////// PROPERTIES ////////////////////////////////
        public:


        private:
            std::string _type;

//////////////////////--------------------------/////////////////////////



/////////////////////////////// METHODS /////////////////////////////////
        public:
            std::string getType();


        private:

//////////////////////--------------------------/////////////////////////

    };

} // config
