/*
** EPITECH PROJECT, 2020
** MissingValueException.hpp
** File description:
** header for MissingValueException.c
*/


#pragma once

#include "polymorph/debug/exception/ConfigurationException.hpp"

namespace polymorph::engine::debug
{
    class MissingValueException final : public ConfigurationException
    {
////////////////////// CONSTRUCTORS/DESTRUCTORS /////////////////////////
        public:
            MissingValueException(std::string entity, std::string component,
                                  std::string property, std::string object = "",
                                  Logger::severity level = Logger::MAJOR);

            MissingValueException(std::string object, std::string property,
                                  Logger::severity level = Logger::MAJOR);

            ~MissingValueException() final = default;

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
