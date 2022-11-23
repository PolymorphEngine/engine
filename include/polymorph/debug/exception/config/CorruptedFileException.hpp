/*
** EPITECH PROJECT, 2020
** CorruptedFileException.hpp
** File description:
** header for CorruptedFileException.c
*/


#pragma once

#include "polymorph/debug/exception/ConfigurationException.hpp"

namespace polymorph::engine::debug
{

    class CorruptedFileException final : public ConfigurationException
    {

////////////////////// CONSTRUCTORS/DESTRUCTORS /////////////////////////
        public:
            CorruptedFileException(std::string file, Logger::severity level = Logger::MAJOR);

            ~CorruptedFileException() final = default;

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