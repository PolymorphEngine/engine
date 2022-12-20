/*
** EPITECH PROJECT, 2020
** MissingComponentTypeException.hpp
** File description:
** header for MissingComponentTypeException.c
*/


#pragma once

#include "polymorph/engine/debug/exception/ConfigurationException.hpp"

namespace polymorph::engine::debug
{
    class MissingComponentTypeException final : public ConfigurationException
    {

////////////////////// CONSTRUCTORS/DESTRUCTORS /////////////////////////
        public:
            MissingComponentTypeException(
                    std::string entity);

            ~MissingComponentTypeException() final = default;

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