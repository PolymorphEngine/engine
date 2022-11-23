/*
** EPITECH PROJECT, 2020
** SceneNotFoundException.hpp
** File description:
** header for SceneNotFoundException.c
*/


#pragma once

#include "polymorph/debug/exception/CoreException.hpp"

namespace polymorph::engine::debug
{
    class SceneNotFoundException : public CoreException
    {

////////////////////// CONSTRUCTORS/DESTRUCTORS /////////////////////////
        public:
            SceneNotFoundException(std::string name, Logger::severity level = Logger::MAJOR);

            ~SceneNotFoundException() override = default;

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