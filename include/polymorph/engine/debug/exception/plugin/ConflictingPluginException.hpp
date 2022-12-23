/*
** EPITECH PROJECT, 2020
** ConflictingPluginException.hpp
** File description:
** header for ConflictingPluginException.c
*/


#pragma once
#include "polymorph/engine/debug/exception/PluginException.hpp"

namespace polymorph::engine::debug
{
    class ConflictingPluginException : public PluginException
    {

////////////////////// CONSTRUCTORS/DESTRUCTORS /////////////////////////
        public:
            ConflictingPluginException(std::string plugin);

            ~ConflictingPluginException() final = default;

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