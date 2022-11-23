/*
** EPITECH PROJECT, 2020
** SceneNotFoundException.hpp
** File description:
** header for SceneNotFoundException.c
*/


#pragma once

#include "polymorph/debug/exception/ExceptionLogger.hpp"

namespace polymorph::engine::debug
{
    class SceneNotFoundException : public ExceptionLogger
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