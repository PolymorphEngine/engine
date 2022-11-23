/*
** EPITECH PROJECT, 2020
** MissingObjectException.hpp
** File description:
** header for MissingObjectException.c
*/


#pragma once


#include "polymorph/debug/exception/PluginException.hpp"

namespace polymorph::engine::debug
{
    class MissingObjectException : public PluginException
    {

////////////////////// CONSTRUCTORS/DESTRUCTORS /////////////////////////
        public:
            MissingObjectException(std::string objectType, Logger::severity level = Logger::severity::MAJOR);

            ~MissingObjectException() final = default;

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