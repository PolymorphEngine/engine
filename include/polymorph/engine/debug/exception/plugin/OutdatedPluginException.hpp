/*
** EPITECH PROJECT, 2020
** OutdatedPluginException.hpp
** File description:
** header for OutdatedPluginException.c
*/


#pragma once

#include "polymorph/engine/debug/exception/PluginException.hpp"

namespace polymorph::engine::debug
{
    class OutdatedPluginException : public PluginException
    {

////////////////////// CONSTRUCTORS/DESTRUCTORS /////////////////////////
        public:
            explicit OutdatedPluginException(std::string plugin);

            ~OutdatedPluginException() final = default;

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