/*
** EPITECH PROJECT, 2020
** MissingPropertyException.hpp
** File description:
** header for MissingPropertyException.c
*/


#pragma once

#include "polymorph/debug/exception/ConfigurationException.hpp"

namespace polymorph::engine::debug
{

    class MissingPropertyException final : public ConfigurationException
    {

////////////////////// CONSTRUCTORS/DESTRUCTORS /////////////////////////
        public:
            MissingPropertyException(std::string entity, std::string component, std::string property, std::string object = "", Logger::severity level = Logger::MAJOR);
            
            MissingPropertyException(std::string object, std::string property, Logger::severity level = Logger::MAJOR);

            ~MissingPropertyException() final = default;

//////////////////////--------------------------/////////////////////////



///////////////////////////// PROPERTIES ////////////////////////////////
        public:


        private:

//////////////////////--------------------------/////////////////////////



/////////////////////////////// METHODS /////////////////////////////////
        public:


        private:

//////////////////////--------------------------/////////////////////////

    };
}