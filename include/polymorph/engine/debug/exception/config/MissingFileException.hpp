/*
** EPITECH PROJECT, 2020
** MissingFileException.hpp
** File description:
** header for MissingFileException.c
*/


#pragma once

#include "polymorph/engine/debug/exception/ConfigurationException.hpp"

namespace polymorph::engine::debug
{

    class MissingFileException final : public ConfigurationException
    {

////////////////////// CONSTRUCTORS/DESTRUCTORS /////////////////////////
        public:
                explicit MissingFileException(std::string file, Logger::severity level = Logger::MAJOR);

                ~MissingFileException() final = default;

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