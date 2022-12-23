/*
** EPITECH PROJECT, 2020
** EmptySceneException.hpp
** File description:
** header for EmptySceneException.c
*/


#pragma once

#include "polymorph/engine/debug/exception/ConfigurationException.hpp"

namespace polymorph::engine::debug
{
    class EmptySceneException final : public ConfigurationException
    {

////////////////////// CONSTRUCTORS/DESTRUCTORS /////////////////////////
        public:
            EmptySceneException(std::string name, bool isFirst = false);

            ~EmptySceneException() final = default;

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