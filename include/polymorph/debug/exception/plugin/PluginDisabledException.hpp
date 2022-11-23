/*
** EPITECH PROJECT, 2020
** PluginDisabledException.hpp
** File description:
** header for PluginDisabledException.c
*/


#pragma once

#include "polymorph/debug/exception/PluginException.hpp"

namespace polymorph::engine::debug
{
    class PluginDisabledException : public PluginException
    {

////////////////////// CONSTRUCTORS/DESTRUCTORS /////////////////////////
        public:
            explicit PluginDisabledException(std::string plugin, std::string objectType = "", Logger::severity level = Logger::severity::MAJOR);

            ~PluginDisabledException() final = default;

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