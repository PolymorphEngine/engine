/*
** EPITECH PROJECT, 2020
** PluginNotFoundException.hpp
** File description:
** header for PluginNotFoundException.c
*/


#pragma once

#include "polymorph/debug/exception/PluginException.hpp"

namespace polymorph::engine::debug
{
    class PluginNotFoundException : public PluginException
    {

////////////////////// CONSTRUCTORS/DESTRUCTORS /////////////////////////
        public:
            PluginNotFoundException(std::string objectType);

            ~PluginNotFoundException() final = default;

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