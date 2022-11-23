/*
** EPITECH PROJECT, 2020
** CorruptedPluginException.hpp
** File description:
** header for CorruptedPluginException.c
*/


#pragma once

#include "polymorph/debug/exception/PluginException.hpp"

namespace polymorph::engine::debug
{
    class CorruptedPluginException : public PluginException
    {

////////////////////// CONSTRUCTORS/DESTRUCTORS /////////////////////////
        public:
            CorruptedPluginException(std::string plugin);

            ~CorruptedPluginException() final = default;

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