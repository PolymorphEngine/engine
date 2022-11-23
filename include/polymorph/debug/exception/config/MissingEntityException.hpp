/*
** EPITECH PROJECT, 2020
** MissingEntityException.hpp
** File description:
** header for MissingEntityException.c
*/


#pragma once

#include "polymorph/debug/exception/ConfigurationException.hpp"

namespace polymorph::engine::debug
{
    class MissingEntityException final : public ConfigurationException
    {
        public:

////////////////////// CONSTRUCTORS/DESTRUCTORS /////////////////////////
        public:
            explicit MissingEntityException(std::string entity, Logger::severity level = Logger::MAJOR);

            ~MissingEntityException() final = default;

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